#include "Main.hpp"

bool PlayerAI::Update(Object *owner)
{
	static float elapsed = 1.0f/50.0f;
	int dx = 0, dy = 0;

	// Check if player is dead
	if( owner->entity && owner->entity->IsDead() ) return false;

	// Add Conditions From Worn or Wielded Items
	owner->entity->addConditions(owner);

	// Reset Player Stats
	owner->entity->stats = owner->entity->base_stats;

	// Update and Apply Conditions
	owner->entity->updateConditions(owner);

	// Increment displacement
	owner->entity->displacement += elapsed*static_cast<float>(owner->entity->stats.spd);

	if( owner->entity->displacement >= 1.0f )
	{
      	owner->entity->displacement = 0.0f;

		if( !owner->entity->hasCondition(Condition::CONFUSION) )
		{
			if( TCODConsole::isKeyPressed(TCODK_UP) )
			{
				dy = -1;
				owner->sym.set(CHAR_PLAYER_UP,0);
			}
			if( TCODConsole::isKeyPressed(TCODK_DOWN) )
			{
				dy = +1;
				owner->sym.set(CHAR_PLAYER_DOWN,0);
			}
			if( TCODConsole::isKeyPressed(TCODK_LEFT) )
			{
				dx = -1;
				owner->sym.set(CHAR_PLAYER_LEFT,0);
			}
			if( TCODConsole::isKeyPressed(TCODK_RIGHT) )
			{
				dx = +1;
				owner->sym.set(CHAR_PLAYER_RIGHT,0);
			}
		}
		else
		{
			bool moved = false;
			moved = moved || TCODConsole::isKeyPressed(TCODK_UP);
			moved = moved || TCODConsole::isKeyPressed(TCODK_DOWN);
			moved = moved || TCODConsole::isKeyPressed(TCODK_LEFT);
			moved = moved || TCODConsole::isKeyPressed(TCODK_RIGHT);
			if( moved )
			{
				dx = rng->getInt(-1, 1);
				dy = rng->getInt(-1, 1);
				owner->sym.set(rng->getInt(CHAR_PLAYER_RIGHT, CHAR_PLAYER_UP), 0);
			}
		}
	}

	Map *map = &engine->map[engine->mapID];
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			map->RevertCell(owner->x.get(i), owner->y.get(i));
			map->Activated(owner->x.get(i), owner->y.get(i), false);
		}
	}
	map->Action(owner, owner->x.get(0) + dx, owner->y.get(0) + dy);
	engine->mapID = static_cast<Engine::CaveTypes>(owner->entity->mapID);

	return true;
}

bool NpcAI::Update(Object *owner)
{
	MoveToTarget(owner);
	return true;
}

void NpcAI::MoveToTarget(Object *owner)
{
	Map *map = &engine->map[engine->mapID];

	if( owner->entity->ai->arrived )
	{
		owner->entity->ai->arrived = false;

		int OldxTarget = owner->x.get(0);
		int OldyTarget = owner->y.get(0);
		int xTarget = rng->getInt(1, map->width - 2);
		int yTarget = rng->getInt(1, map->height - 2);
		float distance = sqrtf((OldxTarget - xTarget)*(OldxTarget - xTarget) + (OldyTarget - yTarget)*(OldyTarget - yTarget));

		while( map->IsObstructed(xTarget, yTarget) || map->CellType(xTarget, yTarget) == Feature::TRAP || distance < 10.0f )
		{
			xTarget = rng->getInt(1, map->width - 2);
			yTarget = rng->getInt(1, map->height - 2);
			distance = sqrtf((OldxTarget - xTarget)*(OldxTarget - xTarget) + (OldyTarget - yTarget)*(OldyTarget - yTarget));
		}
		owner->entity->ai->xTarget = xTarget;
		owner->entity->ai->yTarget = yTarget;
	}

	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = owner->entity->ai->xTarget - ox;
	int dy = owner->entity->ai->yTarget - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);

	dx = (int)(round(dx/distance));
	dy = (int)(round(dy/distance));
	if( !map->IsObstructed(ox + dx, oy + dy) )
	{
		ox += dx;
		oy += dy;
	}
	else if( !map->IsObstructed(ox + stepdx, oy) )
	{
		ox += stepdx;
	}
	else if( !map->IsObstructed(ox, oy + stepdy) )
	{
		oy += stepdy;
	}

	dx = ox - owner->x.get(0);
	dy = oy - owner->y.get(0);
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			map->RevertCell(owner->x.get(i), owner->y.get(i));
			map->Activated(owner->x.get(i), owner->y.get(i), false);
		}
		map->Action(owner, ox, oy);
		for(int i = 0; i < owner->sym.size(); i++) map->SetNpc(owner->x.get(i), owner->y.get(i));
	}

	if( distance <= 1.0f ) owner->entity->ai->arrived = true;
}

bool CreatureAI::Update(Object *owner)
{
	static float elapsed = 1.0f/50.0f;

	if( owner->entity && owner->entity->IsDead() ) return false;

	// Add Conditions From Worn or Wielded Items
	owner->entity->addConditions(owner);

	// Reset Creature Stats
	owner->entity->stats = owner->entity->base_stats;

	// Update and Apply Conditions
	owner->entity->updateConditions(owner);

	// Increment displacement
	owner->entity->displacement += elapsed*static_cast<float>(owner->entity->stats.spd);

	if( owner->entity->displacement >= 1.0f )
	{
      	owner->entity->displacement = 0.0f;

		switch( type )
		{
			case SKITTISH:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target closest entity
					Object *target = ClosestEntity(owner);
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							RunAway(owner, target);
						}
						else
						{
							RandomWalk(owner);
						}
					}
					else
					{
						RandomWalk(owner);
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case REGULAR:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target Player Only
					Object *target = engine->player;
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							ChaseOrAttack(owner, target);
						}
						else
						{
							RandomWalk(owner);
						}
					}
					else
					{
						RandomWalk(owner);
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case AGGRESSIVE:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target closest entity
					Object *target = ClosestEntity(owner);
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							ChaseOrAttack(owner, target);
						}
						else
						{
							RandomWalk(owner);
						}
					}
					else
					{
						RandomWalk(owner);
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case PATROLLER:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target Player Only
					Object *target = engine->player;
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							ChaseOrAttack(owner, target);
						}
						else
						{
							MoveToTarget(owner);
						}
					}
					else
					{
						MoveToTarget(owner);
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case SPAWNER:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target Player Only
					Object *target = engine->player;
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							ChaseOrAttack(owner, target);
						}
						else
						{
							RandomWalk(owner);
						}
					}
					else
					{
						RandomWalk(owner);
					}
					// If number of subordinates is less than max, then spawn more
					//if( owner->entity->ai->nSubordinates < owner->entity->ai->nMaxSubordinates ) SpawnSubordinates(owner);
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case SEEKER:
			{
				// Target Player Only
				Object *target = engine->player;
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					ChaseOrAttack(owner, target);
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			default: break;
		}
	}

	return true;
}

Object *CreatureAI::ClosestEntity(Object *owner) const
{
	int imin = -1;
	float dmin = 9999.0f;
	Map *map = &engine->map[engine->mapID];

	// Search the object list first
	for(int i = map->objects.size() - 1; i >= 0; i--)
	{
		Object *object = map->objects.get(i);
		if( object != owner && object->entity && object->entity->type != Entity::INANIMATE && !object->entity->IsDead() )
		{
			float dx = owner->xc - object->xc, dy = owner->yc - object->yc, d = sqrtf(dx*dx + dy*dy);
			if( d < dmin )
			{
				dmin = d;
				imin = i;
			}
		}
	}

	// Search for the player
	float dx = owner->xc - engine->player->xc, dy = owner->yc - engine->player->yc, d = sqrtf(dx*dx + dy*dy);
	if( d < dmin )
	{
		dmin = d;
		imin = map->objects.size() + 1;
	}

	if( imin >= 0 )
	{
		Object *object;
		if( imin < map->objects.size() )
		{
			object = map->objects.get(imin);
		}
		else
		{
			object = engine->player;
		}
		return object;
	}
	else
	{
		return NULL;
	}
}

void CreatureAI::RunAway(Object *owner, Object *target)
{
	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = target->x.get(0) - ox;
	int dy = target->y.get(0) - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);
	Map *map = &engine->map[engine->mapID];

	owner->entity->ai->arrived = true;

				//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
	Stats stats = Stats(0, 0, 0, 0, 15, 0, 0, 0, 0, 0);
				//  Health(hp, mp, xpnext)
	Health health = Health(0, 0, 0);
	Condition *condition = new Condition(Condition::NONE, 0, -1, stats, health, NULL, NULL, NULL);
	owner->entity->conditions->addToBack(condition);

	if( distance > sqrt(2.0f) )
	{
		dx = (int)(round(dx/distance));
		dy = (int)(round(dy/distance));
		if( !map->IsObstructed(ox - dx, oy - dy) )
		{
			ox -= dx;
			oy -= dy;
		}
		else if( !map->IsObstructed(ox - stepdx, oy) )
		{
			ox -= stepdx;
		}
		else if( !map->IsObstructed(ox, oy - stepdy) )
		{
			oy -= stepdy;
		}
	}

	dx = ox - owner->x.get(0);
	dy = oy - owner->y.get(0);
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			map->RevertCell(owner->x.get(i), owner->y.get(i));
			map->Activated(owner->x.get(i), owner->y.get(i), false);
		}
		map->Action(owner, ox, oy);
		if( !owner->entity->IsDead() ) for(int i = 0; i < owner->sym.size(); i++) map->SetCreature(owner->x.get(i), owner->y.get(i));
	}

	if( distance <= sqrt(2.0f) ) owner->entity->Attack(owner, target);
}

void CreatureAI::RandomWalk(Object *owner)
{
	static const int dx[NBLOCK] = {-1,  0, +1, -1, 0, +1, -1,  0, +1};
	static const int dy[NBLOCK] = {-1, -1, -1,  0, 0,  0, +1, +1, +1};
	Map *map = &engine->map[engine->mapID];

	owner->entity->ai->arrived = true;

	int i = rng->getInt(0, NBLOCK - 1);
	owner->obstructs = false;
	bool obstructed = map->IsObstructed(owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
	for(int j = 1; j < owner->sym.size(); j++)
	{
		obstructed = obstructed || map->IsObstructed(owner->x.get(j) + dx[i], owner->y.get(j) + dy[i]);
	}
	while( obstructed )
	{
		i = rng->getInt(0, NBLOCK - 1);
		obstructed = map->IsObstructed(owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
		for(int j = 1; j < owner->sym.size(); j++)
		{
			obstructed = obstructed || map->IsObstructed(owner->x.get(j) + dx[i], owner->y.get(j) + dy[i]);
		}
	}
	owner->obstructs = true;

	if( dx[i] != 0 || dy[i] != 0 )
	{
		for(int j = 0; j < owner->sym.size(); j++)
		{
			map->RevertCell(owner->x.get(j), owner->y.get(j));
			map->Activated(owner->x.get(j), owner->y.get(j), false);
		}
		map->Action(owner, owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
		if( !owner->entity->IsDead() ) for(int j = 0; j < owner->sym.size(); j++) map->SetCreature(owner->x.get(j), owner->y.get(j));
	}
}

void CreatureAI::ChaseOrAttack(Object *owner, Object *target)
{
	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = target->x.get(0) - ox;
	int dy = target->y.get(0) - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);
	Map *map = &engine->map[engine->mapID];

	owner->entity->ai->arrived = true;

				//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
	Stats stats = Stats(0, 0, 0, 0, 25, 0, 0, 0, 0, 0);
				//  Health(hp, mp, xpnext)
	Health health = Health(0, 0, 0);
	Condition *condition = new Condition(Condition::NONE, 0, -1, stats, health, NULL, NULL, NULL);
	owner->entity->conditions->addToBack(condition);

	if( distance > sqrt(2.0f) )
	{
		dx = (int)(round(dx/distance));
		dy = (int)(round(dy/distance));
		if( !map->IsObstructed(ox + dx, oy + dy) )
		{
			ox += dx;
			oy += dy;
		}
		else if( !map->IsObstructed(ox + stepdx, oy) )
		{
			ox += stepdx;
		}
		else if( !map->IsObstructed(ox, oy + stepdy) )
		{
			oy += stepdy;
		}
	}

	dx = ox - owner->x.get(0);
	dy = oy - owner->y.get(0);
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			map->RevertCell(owner->x.get(i), owner->y.get(i));
			map->Activated(owner->x.get(i), owner->y.get(i), false);
		}
		map->Action(owner, ox, oy);
		if( !owner->entity->IsDead() ) for(int i = 0; i < owner->sym.size(); i++) map->SetCreature(owner->x.get(i), owner->y.get(i));
	}

	if( distance <= sqrt(2.0f) ) owner->entity->Attack(owner, target);
}

void CreatureAI::MoveToTarget(Object *owner)
{
	Map *map = &engine->map[engine->mapID];

	int ox = owner->x.get(0), oy = owner->y.get(0);
	ox = Clamp<int>(ox, 1, map->width - 2);
	oy = Clamp<int>(oy, 1, map->height - 2);
	owner->x.set(ox, 0);
	owner->y.set(oy, 0);

	if( owner->entity->ai->arrived )
	{
		owner->entity->ai->arrived = false;

		int direction = rng->getInt(1, 4);
		int xTarget, yTarget;
		switch( direction )
		{
			case 1:
			{	// Up
				xTarget = ox;
				yTarget = oy - 10;
				break;
			}
			case 2:
			{	// Down
				xTarget = ox;
				yTarget = oy + 10;
				break;
			}
			case 3:
			{	// Left
				xTarget = ox - 10;
				yTarget = oy;
				break;
			}
			case 4:
			{	// Right
				xTarget = ox + 10;
				yTarget = oy;
				break;
			}
			default: break;
		}
		xTarget = Clamp<int>(xTarget, 1, map->width - 2);
		yTarget = Clamp<int>(yTarget, 1, map->height - 2);
		owner->entity->ai->xTarget = xTarget;
		owner->entity->ai->yTarget = yTarget;
	}

	int dx = owner->entity->ai->xTarget - ox;
	int dy = owner->entity->ai->yTarget - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = MAX(1.0f, sqrtf(dx*dx + dy*dy));

	dx = (int)(round(dx/distance));
	dy = (int)(round(dy/distance));
	if( !map->IsObstructed(ox + dx, oy + dy) )
	{
		ox += dx;
		oy += dy;
	}
	else if( !map->IsObstructed(ox + stepdx, oy) )
	{
		ox += stepdx;
	}
	else if( !map->IsObstructed(ox, oy + stepdy) )
	{
		oy += stepdy;
	}
	else
	{
		owner->entity->ai->arrived = true;
	}

	dx = ox - owner->x.get(0);
	dy = oy - owner->y.get(0);
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			map->RevertCell(owner->x.get(i), owner->y.get(i));
			map->Activated(owner->x.get(i), owner->y.get(i), false);
		}
		map->Action(owner, ox, oy);
		for(int i = 0; i < owner->sym.size(); i++) map->SetCreature(owner->x.get(i), owner->y.get(i));
	}

	if( distance <= 1.0f ) owner->entity->ai->arrived = true;
}

bool BossAI::Update(Object *owner)
{
	static float elapsed = 1.0f/50.0f;

	if( owner->entity && owner->entity->IsDead() ) return false;

	// Add Conditions From Worn or Wielded Items
	owner->entity->addConditions(owner);

	// Reset Creature Stats
	owner->entity->stats = owner->entity->base_stats;

	// Update and Apply Conditions
	owner->entity->updateConditions(owner);

	// Increment displacement
	owner->entity->displacement += elapsed*static_cast<float>(owner->entity->stats.spd);

	if( owner->entity->displacement >= 1.0f )
	{
      	owner->entity->displacement = 0.0f;

		WalkPattern(owner);

		if( !engine->player->entity->IsDead() )
		{
			float dx = owner->xc - engine->player->xc, dy = owner->yc - engine->player->yc, d = sqrtf(dx*dx + dy*dy);
			if( d <= 1.5f*sqrt(2.0f) ) owner->entity->Attack(owner, engine->player);
		}
	}

	return true;
}

void BossAI::WalkPattern(Object *owner)
{
	static int x = owner->x.get(0), y = owner->y.get(0);
	Map *map = &engine->map[engine->mapID];

	// Increment along prescribed pattern list
	ListPattern(owner, x, y);

	for(int j = 0; j < owner->sym.size(); j++)
	{
		map->RevertCell(owner->x.get(j), owner->y.get(j));
		map->Activated(owner->x.get(j), owner->y.get(j), false);
	}
	map->Action(owner, x, y);
	if( !owner->entity->IsDead() ) for(int j = 0; j < owner->sym.size(); j++) map->SetCreature(owner->x.get(j), owner->y.get(j));
}

void BossAI::ListPattern(Object *owner, int &x, int &y)
{
	static bool second = false;
	static int patternCounter = 0, patternMax = 0;
	static int stepCounter = 0, stepMax = 0;
	Map *map = &engine->map[engine->mapID];

	patternMax = patternList.size();
	stepMax = patternData[patternCounter].size();

	int dx = patternData[patternCounter][stepCounter].x;
	int dy = patternData[patternCounter][stepCounter].y;

	owner->obstructs = false;
	bool obstructed = map->IsObstructed(owner->x.get(0) + dx, owner->y.get(0) + dy);
	for(int j = 1; j < owner->sym.size(); j++)
	{
		obstructed = obstructed || map->IsObstructed(owner->x.get(j) + dx, owner->y.get(j) + dy);
	}
	owner->obstructs = true;

	if( !obstructed )
	{
		x += dx;
		y += dy;
	}
	owner->entity->base_stats.spd += patternData[patternCounter][stepCounter].spd;

	stepCounter = (stepCounter + 1) % MAX(1, stepMax);
	if( stepCounter == 0 )
	{
		patternCounter = (patternCounter + 1) % MAX(1, patternMax);
		if( patternCounter == 0 )
		{
			if( second )
			{
				second = false;
				PatternEnsemble(rng->getInt(VERTICAL_PATTERN, NPATTERNTYPES - 1));
			}
			else
			{
				second = true;
			}
		}
	}
}
