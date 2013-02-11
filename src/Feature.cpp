#include "Main.hpp"

// Feature
Feature::Feature(): cellType(-1), trapType(-1), explored(false), activated(false)
{
	darkWall = TCODColor(0, 0, 100);
	darkGround = TCODColor(50, 50, 150);
	colour = darkGround;
}

// Floor Feature
Floor::Floor()
{
	cellType = FLOOR;
	colour = darkGround;
}

// Floor Feature: Movement
void Floor::Action(Object *owner, int x, int y)
{
	owner->xc = 0.0f; owner->yc = 0.0f;
	int x0 = owner->x.get(0), y0 = owner->y.get(0);
	for(int i = 0; i < owner->sym.size(); i++)
	{
		int dx = owner->x.get(i) - x0;
		int dy = owner->y.get(i) - y0;
		owner->x.set(x + dx,i);
		owner->y.set(y + dy,i);
		owner->xc += owner->x.get(i);
		owner->yc += owner->y.get(i);
	}
	owner->xc /= static_cast<float>(owner->sym.size());
	owner->yc /= static_cast<float>(owner->sym.size());

	if( owner == engine->player )
	{
		Map *map = &engine->map[engine->mapID];
		if( !activated )
		{
			activated = true;

			char buffer[CHARMAX] = "";
			bool first = true;
			int nobjects = 0;

			// Look for any objects on the floor
			for(int i = map->objects.size() - 1; i >= 0; i--)
			{
				Object *object = map->objects.get(i);
				for(int j = 0; j < object->sym.size(); j++)
				{
					if( object->x.get(j) == x && object->y.get(j) == y )
					{
						nobjects++;
						if( !first )
						{
							strcat(buffer, " And ");
						}
						else
						{
							first = false;
						}
						strcat(buffer, object->name);
					}
				}
			}
			if( nobjects > 0 ) engine->gui->MessageLog(TCODColor::lightGrey, "There's %s Here", buffer);
		}

		Object *tunnel = map->GetObject(x, y);
		if( tunnel && tunnel->traversable && engine->key.vk == TCODK_ENTER )
		{
			owner->entity->mapID = tunnel->traversable->mapID;
			owner->xc = 0.0f; owner->yc = 0.0f;
			int x0 = owner->x.get(0), y0 = owner->y.get(0);
			for(int i = 0; i < owner->sym.size(); i++)
			{
				int dx = owner->x.get(i) - x0;
				int dy = owner->y.get(i) - y0;
				owner->x.set(tunnel->traversable->xTo + dx,i);
				owner->y.set(tunnel->traversable->yTo + dy,i);
				owner->xc += owner->x.get(i);
				owner->yc += owner->y.get(i);
			}
			owner->xc /= static_cast<float>(owner->sym.size());
			owner->yc /= static_cast<float>(owner->sym.size());
			engine->key.vk = TCODK_NONE;
		}
	}
}

// Wall Feature
Wall::Wall()
{
	cellType = WALL;
	colour = darkWall;
}

// Wall Feature: Display bump message
void Wall::Action(Object *owner, int x, int y)
{
	if( owner == engine->player )
	{
		if( !activated )
		{
			activated = true;
			engine->gui->MessageLog(TCODColor::lightGrey, "You Bump Into A Wall");
		}
		else
		{
			Object *wall = engine->map[engine->mapID].GetEntity(x, y);
			if( wall ) owner->entity->Attack(owner, wall);
		}
	}
}

// Door Feature
Door::Door(): open(false)
{
	cellType = DOOR;
	colour = darkGround;
}

// Door Feature: Either open or move onto the cell
void Door::Action(Object *owner, int x, int y)
{
	if( open )
	{
		owner->xc = 0.0f; owner->yc = 0.0f;
		int x0 = owner->x.get(0), y0 = owner->y.get(0);
		for(int i = 0; i < owner->sym.size(); i++)
		{
			int dx = owner->x.get(i) - x0;
			int dy = owner->y.get(i) - y0;
			owner->x.set(x + dx,i);
			owner->y.set(x + dy,i);
			owner->xc += owner->x.get(i);
			owner->yc += owner->y.get(i);
		}
		owner->xc /= static_cast<float>(owner->sym.size());
		owner->yc /= static_cast<float>(owner->sym.size());
	}
	else
	{
		open = true;
		engine->gui->MessageLog(TCODColor::lightGrey, "You Open A Door");
	}
}

// Trap Feature
Trap::Trap(int type, int mapID, int xTo, int yTo): mapID(mapID), xTo(xTo), yTo(yTo)
{
	cellType = TRAP;
	trapType = type;
	colour = darkGround;
	conditions = new Conditions();

	switch( trapType )
	{
		case INVISIBLEBARRIER:
		{
			flashColor = TCODColor::yellow;
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(0, 0, 0, 0, -1000, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_PARALYSIS, FPSMAX/2, 0, stats, health, NULL, "An Invisible Barrier Blocks Your Path", NULL);
			conditions->addToFront(condition);
			break;
		}
		case DARKTUNNEL:
		{
			flashColor = TCODColor::red;
							// Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, -1000, 0, 0, 0, 0, 0);
							//   Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_PARALYSIS, FPSMAX/2, 0, *stats, *health, NULL, "You Plummet Down A Dark Tunnel!", NULL);
			conditions->addToBack(condition);

					//  Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
					//   Health(hp, mp, xpnext)
			health = new Health(-2, 0, 0);
			condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, NULL, NULL);
			conditions->addToBack(condition);
			break;
		}
		default: break;
	}
}

// Trap Feature: Activate Trap
void Trap::Action(Object *owner, int x, int y)
{
	// Reset the trap conditions
	for(int i = 0; i < conditions->inventory.size(); i++)
	{
		Condition *condition = conditions->inventory.get(i);
		condition->first = true;
		condition->duration = FPSMAX/2;
	}

	if( trapType != INVISIBLEBARRIER )
	{
		owner->xc = 0.0f; owner->yc = 0.0f;
		int x0 = owner->x.get(0), y0 = owner->y.get(0);
		for(int i = 0; i < owner->sym.size(); i++)
		{
			int dx = owner->x.get(i) - x0;
			int dy = owner->y.get(i) - y0;
			owner->x.set(x + dx,i);
			owner->y.set(x + dy,i);
			owner->xc += owner->x.get(i);
			owner->yc += owner->y.get(i);
		}
		owner->xc /= static_cast<float>(owner->sym.size());
		owner->yc /= static_cast<float>(owner->sym.size());
	}

	if( !activated || trapType == INVISIBLEBARRIER )
	{
		if( trapType == DARKTUNNEL )
		{
			engine->map[engine->mapID].Activated(xTo, yTo, true);
			owner->entity->mapID = mapID;
			owner->xc = 0.0f; owner->yc = 0.0f;
			int x0 = owner->x.get(0), y0 = owner->y.get(0);
			for(int i = 0; i < owner->sym.size(); i++)
			{
				int dx = owner->x.get(i) - x0;
				int dy = owner->y.get(i) - y0;
				owner->x.set(xTo + dx,i);
				owner->y.set(xTo + dy,i);
				owner->xc += owner->x.get(i);
				owner->yc += owner->y.get(i);
			}
			owner->xc /= static_cast<float>(owner->sym.size());
			owner->yc /= static_cast<float>(owner->sym.size());
		}
		else
		{
			activated = true;
		}

		for(int i = 0; i < conditions->inventory.size(); i++)
		{
			Condition *condition = conditions->inventory.get(i);
			if( condition->msg_start && owner == engine->player ) engine->gui->MessageLog(TCODColor::green, "%s", condition->msg_start);
			owner->entity->conditions->addToBack(condition);
		}

		TCODConsole::root->setCharBackground(x, y, flashColor);
		TCODConsole::root->flush();

		if( owner->entity->IsDead() )
		{
			for(int i = 0; i < owner->sym.size(); i++) engine->map[engine->mapID].SetCreature(owner->x.get(i), owner->y.get(i));
			owner->entity->Death(owner);
		}
	}
}

// Creature Feature
Creature::Creature()
{
	cellType = CREATURE;
	colour = darkGround;
}

// Creature Feature: Attack!
void Creature::Action(Object *owner, int x, int y) 
{
	// Attack the creature in this cell
	Object *creature = engine->map[engine->mapID].GetEntity(x, y);
	if( creature && creature != owner ) owner->entity->Attack(owner, creature);
}

// Npc Feature
Npc::Npc()
{
	cellType = NPC;
	colour = darkGround;
}

// Npc Feature: Display Dialog
void Npc::Action(Object *owner, int x, int y)
{
	if(owner == engine->player) engine->gui->MessageLog(TCODColor::lightGrey, "You converse with the NPC");
}
