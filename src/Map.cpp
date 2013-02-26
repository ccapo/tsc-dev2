#include "Main.hpp"

void Map::GenerateMap(int caveType)
{
	static const int dx[NBLOCK] = {-1, 0, +1, -1, 0, +1, -1, 0, +1};
	static const int dy[NBLOCK] = {-1, -1, -1, 0, 0, 0, +1, +1, +1};

	for(int x = 0; x < width; x++)
	{
		AddWall(x, 0, true);
		AddWall(x, height - 1, true);
	}

	for(int y = 1; y < height - 1; y++)
	{
		AddWall(0, y, true);
		AddWall(width - 1, y, true);
	}

	switch( caveType )
	{
		case Engine::CAVETYPE_01:
		{
			for(int i = 0; i < NBLOCK; i++)
			{
				AddWall(width/2 + dx[i], height/3 + dy[i], false);
				AddWall(width/2 + dx[i], 2*height/3 + dy[i], false);
				AddWall(width/3 + dx[i], height/2 + dy[i], false);
				AddWall(2*width/3 + dx[i], height/2 + dy[i], false);
			}

			//nTraps = 6;
			GetTrapChances(caveType);
			for(int i = 0; i < nTraps; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddTrap(x, y);
			}

			//nItems = 16;
			GetItemChances(caveType);
			for(int i = 0; i < nItems; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddItem(x, y);
			}

			//nCreatures = 3;
			GetCreatureChances(caveType);
			for(int i = 0; i < nCreatures; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddCreature(x, y);
			}
			break;
		}
		case Engine::CAVETYPE_02:
		{
			for(int i = 0; i < 50; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddWall(x, y, false);
			}

			//nTraps = 6;
			GetTrapChances(caveType);
			for(int i = 0; i < nTraps; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddTrap(x, y);
			}

			//nItems = 16;
			GetItemChances(caveType);
			for(int i = 0; i < nItems; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddItem(x, y);
			}

			//nCreatures = 2;
			GetCreatureChances(caveType);
			for(int i = 0; i < nCreatures; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddCreature(x, y);
			}
			break;
		}
		case Engine::CAVETYPE_03:
		{
			for(int i = 0; i < 25; i++)
			{
				int x = rng->getInt(3, width - 4);
				int y = rng->getInt(3, height - 4);
				while( IsObstructed(x, y) )
				{
					x = rng->getInt(3, width - 4);
					y = rng->getInt(3, height - 4);
				}
				for(int j = 0; j < NBLOCK; j++) AddWall(x + dx[j], y + dy[j], false);
			}

			//nTraps = 6;
			GetTrapChances(caveType);
			for(int i = 0; i < nTraps; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddTrap(x, y);
			}

			//nItems = 16;
			GetItemChances(caveType);
			for(int i = 0; i < nItems; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddItem(x, y);
			}

			//nCreatures = 5;
			GetCreatureChances(caveType);
			for(int i = 0; i < nCreatures; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddCreature(x, y);
			}
			break;
		}
		case Engine::CAVETYPE_04:
		{
			for(int i = 0; i < 25; i++)
			{
				int x = rng->getInt(3, width - 4);
				int y = rng->getInt(3, height - 4);
				while( IsObstructed(x, y) )
				{
					x = rng->getInt(3, width - 4);
					y = rng->getInt(3, height - 4);
				}
				for(int j = 0; j < NBLOCK; j++) AddWall(x + dx[j], y + dy[j], false);
			}

			//nTraps = 6;
			GetTrapChances(caveType);
			for(int i = 0; i < nTraps; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddTrap(x, y);
			}

			//nItems = 16;
			GetItemChances(caveType);
			for(int i = 0; i < nItems; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddItem(x, y);
			}

			//nCreatures = 5;
			GetCreatureChances(caveType);
			for(int i = 0; i < nCreatures; i++)
			{
				int x = rng->getInt(1, width - 2);
				int y = rng->getInt(1, height - 2);
				while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
				{
					x = rng->getInt(1, width - 2);
					y = rng->getInt(1, height - 2);
				}
				AddCreature(x, y);
			}
			break;
		}
		// World Map
		default:
		{
			// Add Boss
			int x = rng->getInt(width/2 - 1, width/2 + 1);
			int y = rng->getInt(height/2 - 1, height/2 + 1);
			while( IsObstructed(x, y) || CellType(x, y) == Feature::TRAP )
			{
				x = rng->getInt(width/2 - 1, width/2 + 1);
				y = rng->getInt(height/2 - 1, height/2 + 1);
			}
			AddBoss(x, y);
			break;
		}
	}
}

void Map::Render()
{
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			TCODConsole::root->setCharBackground(x, y, Colour(x, y));
		}
	}
}

void Map::GetItemChances(int caveType)
{
	switch( caveType )
	{
		case Engine::CAVETYPE_01:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Object::CONSUMABLE,	30));
			object_chances.insert(pair<int, int>(Object::CONTAINER,		30));
			object_chances.insert(pair<int, int>(Object::ENTITY,		10));
			object_chances.insert(pair<int, int>(Object::WIELDABLE,		10));
			object_chances.insert(pair<int, int>(Object::WEARABLE,		10));
			object_chances.insert(pair<int, int>(Object::MISC,			10));
			break;
		}
		case Engine::CAVETYPE_02:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Object::CONSUMABLE,	30));
			object_chances.insert(pair<int, int>(Object::CONTAINER,		30));
			object_chances.insert(pair<int, int>(Object::ENTITY,		10));
			object_chances.insert(pair<int, int>(Object::WIELDABLE,		10));
			object_chances.insert(pair<int, int>(Object::WEARABLE,		10));
			object_chances.insert(pair<int, int>(Object::MISC,			10));
			break;
		}
		case Engine::CAVETYPE_03:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Object::CONSUMABLE,	30));
			object_chances.insert(pair<int, int>(Object::CONTAINER,		30));
			object_chances.insert(pair<int, int>(Object::ENTITY,		10));
			object_chances.insert(pair<int, int>(Object::WIELDABLE,		10));
			object_chances.insert(pair<int, int>(Object::WEARABLE,		10));
			object_chances.insert(pair<int, int>(Object::MISC,			10));
			break;
		}
		case Engine::CAVETYPE_04:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Object::CONSUMABLE,	30));
			object_chances.insert(pair<int, int>(Object::CONTAINER,		30));
			object_chances.insert(pair<int, int>(Object::ENTITY,		10));
			object_chances.insert(pair<int, int>(Object::WIELDABLE,		10));
			object_chances.insert(pair<int, int>(Object::WEARABLE,		10));
			object_chances.insert(pair<int, int>(Object::MISC,			10));
			break;
		}
		default: break;
	}
}

void Map::GetTrapChances(int caveType)
{
	switch( caveType )
	{
		case Engine::CAVETYPE_01:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Trap::INVISIBLEBARRIER,	75));
			object_chances.insert(pair<int, int>(Trap::DARKTUNNEL,			25));
			break;
		}
		case Engine::CAVETYPE_02:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Trap::INVISIBLEBARRIER,	75));
			object_chances.insert(pair<int, int>(Trap::DARKTUNNEL,			25));
			break;
		}
		case Engine::CAVETYPE_03:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Trap::INVISIBLEBARRIER,	75));
			object_chances.insert(pair<int, int>(Trap::DARKTUNNEL,			25));
			break;
		}
		case Engine::CAVETYPE_04:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Trap::INVISIBLEBARRIER,	75));
			object_chances.insert(pair<int, int>(Trap::DARKTUNNEL,			25));
			break;
		}
		default: break;
	}
}

void Map::GetCreatureChances(int caveType)
{
	switch( caveType )
	{
		case Engine::CAVETYPE_01:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(CreatureAI::SKITTISH,    5));
			object_chances.insert(pair<int, int>(CreatureAI::REGULAR,    30));
			object_chances.insert(pair<int, int>(CreatureAI::AGGRESSIVE, 20));
			object_chances.insert(pair<int, int>(CreatureAI::PATROLLER,  30));
			object_chances.insert(pair<int, int>(CreatureAI::CHARGER,     5));
			object_chances.insert(pair<int, int>(CreatureAI::SPAWNER,     5));
			object_chances.insert(pair<int, int>(CreatureAI::SEEKER,      5));
			break;
		}
		case Engine::CAVETYPE_02:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(CreatureAI::SKITTISH,   30));
			object_chances.insert(pair<int, int>(CreatureAI::REGULAR,    30));
			object_chances.insert(pair<int, int>(CreatureAI::AGGRESSIVE, 20));
			object_chances.insert(pair<int, int>(CreatureAI::PATROLLER,   5));
			object_chances.insert(pair<int, int>(CreatureAI::CHARGER,     5));
			object_chances.insert(pair<int, int>(CreatureAI::SPAWNER,     5));
			object_chances.insert(pair<int, int>(CreatureAI::SEEKER,      5));
			break;
		}
		case Engine::CAVETYPE_03:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(CreatureAI::SKITTISH,   30));
			object_chances.insert(pair<int, int>(CreatureAI::REGULAR,    30));
			object_chances.insert(pair<int, int>(CreatureAI::AGGRESSIVE, 20));
			object_chances.insert(pair<int, int>(CreatureAI::PATROLLER,   5));
			object_chances.insert(pair<int, int>(CreatureAI::CHARGER,     5));
			object_chances.insert(pair<int, int>(CreatureAI::SPAWNER,     5));
			object_chances.insert(pair<int, int>(CreatureAI::SEEKER,      5));
			break;
		}
		case Engine::CAVETYPE_04:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(CreatureAI::SKITTISH,   30));
			object_chances.insert(pair<int, int>(CreatureAI::REGULAR,    30));
			object_chances.insert(pair<int, int>(CreatureAI::AGGRESSIVE, 20));
			object_chances.insert(pair<int, int>(CreatureAI::PATROLLER,   5));
			object_chances.insert(pair<int, int>(CreatureAI::CHARGER,     5));
			object_chances.insert(pair<int, int>(CreatureAI::SPAWNER,     5));
			object_chances.insert(pair<int, int>(CreatureAI::SEEKER,      5));
			break;
		}
		default: break;
	}
}

void Map::AddWall(int x, int y, bool imprevious)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(' ');
	Object *wall = new Object(xlist, ylist, symlist, TCODColor::white, "A Wall", 2.0f, true);
	if( imprevious )
	{
					//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
		Stats stats = Stats(1, 0, 999, 0, 0, 0, 0, 0, 0, 0);
					//  Health(hp, mp, xpnext)
		Health health = Health(1, 0, 0);
		wall->entity = new Entity(Entity::INANIMATE, stats, health, CHAR_RUBBLE_PILE, TCODColor::white, "A Pile Of Rubble");
	}
	else
	{
					//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
		Stats stats = Stats(100, 0, 5, 0, 0, 0, 0, 0, 0, 0);
					//  Health(hp, mp, xpnext)
		Health health = Health(100, 0, -1);
		wall->entity = new Entity(Entity::INANIMATE, stats, health, CHAR_RUBBLE_PILE, TCODColor::white, "A Pile Of Rubble");
	}
	objects.push(wall);
	cells[x + y*width].feature = new Wall();
}

void Map::AddTunnelUp(int x, int y, int mapID, int xTo, int yTo)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_STAIRS_UP);
	Object *tunnel = new Object(xlist, ylist, symlist, TCODColor::white, "A Tunnel Up", 1000.0f, false);
	tunnel->traversable = new Traversable(mapID, xTo, yTo);
	objects.push(tunnel);
	SendToBack(tunnel);
}

void Map::AddTunnelDown(int x, int y, int mapID, int xTo, int yTo)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_STAIRS_DOWN);
	Object *tunnel = new Object(xlist, ylist, symlist, TCODColor::white, "A Tunnel Down", 1000.0f, false);
	tunnel->traversable = new Traversable(mapID, xTo, yTo);
	objects.push(tunnel);
	SendToBack(tunnel);
}

void Map::AddTunnelSurface(int x, int y, int mapID, int xTo, int yTo)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_STAIRS_UP);
	Object *tunnel = new Object(xlist, ylist, symlist, TCODColor::sepia, "A Tunnel To The Surface", 1000.0f, false);
	tunnel->traversable = new Traversable(mapID, xTo, yTo);
	objects.push(tunnel);
	SendToBack(tunnel);
}

void Map::AddItem(int x, int y)
{
	int itemType = RandomChoice(object_chances);
	TCODList<int> xlist, ylist, symlist;
	switch( itemType )
	{
		// Consumable Item
		case Object::CONSUMABLE:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_MUSHROOM);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "A Mushroom", 0.05f, false);
			item->consumable = new Consumable(Consumable::MUSHROOM_UNKNOWN);
			objects.push(item);
			break;
		}
		// Container Item
		case Object::CONTAINER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_CHEST_CLOSED);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "A Small Wooden Chest", 2.0f, false);
			item->container = new Container(8);
			objects.push(item);
			break;
		}
		// Entity Item
		case Object::ENTITY:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_GOBLIN_PEON);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "An Orc", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(0, 0, 0);
			item->entity = new Entity(Entity::TROGLODYTE, stats, health, CHAR_RUBBLE_PILE, TCODColor::peach, "A Pile of Entrails");
			int size = item->sym.size();
			item->sym.clear();
			for(int i = 0; i < size; i++) item->sym.push(item->entity->corpseSym);
			item->colour = item->entity->corpseColour;	
			item->name = item->entity->corpseName;
			item->obstructs = false;
			objects.push(item);
			break;
		}
		// Wieldable Item
		case Object::WIELDABLE:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_SWORD_BASIC);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "A Bronze Sword", 1.0f, false);
			item->wieldable = new Wieldable(Wieldable::BRONZE_SWORD);
			objects.push(item);
			break;
		}
		// Wearable Item
		case Object::WEARABLE:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_ARMOUR_YELLOW);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "Leather Armour", 1.0f, false);
			item->wearable = new Wearable(Wearable::LEATHER_ARMOUR);
			objects.push(item);
			break;
		}
		// A Pile Of Rubble
		case Object::MISC:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_RUBBLE_PILE);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "A Pile Of Rubble", 2.0f, false);
			objects.push(item);
			break;
		}
		default: break;
	}
}

void Map::AddTrap(int x, int y)
{
	int trapType = RandomChoice(object_chances);
	SetTrap(x, y, trapType);
}

void Map::AddCreature(int x, int y)
{
	int creatureType = RandomChoice(object_chances);
	TCODList<int> xlist, ylist, symlist;
	switch( creatureType )
	{
		// Orc
		case CreatureAI::SKITTISH:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_GOBLIN_PEON);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Goblin", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(10, 4, 2, 5, 5, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(10, 0, -5);
			creature->entity = new Entity(Entity::TROGLODYTE, stats, health, CHAR_SKULL, TCODColor::white, "A Goblin Corpse");
			creature->container = new Container(10);
			creature->entity->ai = new CreatureAI(CreatureAI::SKITTISH);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		// Goblin
		case CreatureAI::REGULAR:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_ORC_PEON);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "An Orc", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(15, 5, 3, 5, 5, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(15, 0, -7);
			creature->entity = new Entity(Entity::TROGLODYTE, stats, health, CHAR_SKULL, TCODColor::white, "An Orc Corpse");
			creature->container = new Container(10);
			creature->entity->ai = new CreatureAI(CreatureAI::REGULAR);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		// Warg
		case CreatureAI::AGGRESSIVE:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_VERMIN_BROWN);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Warg", 0.75f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(20, 8, 3, 10, 8, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(20, 0, -10);
			creature->entity = new Entity(Entity::BEAST, stats, health, CHAR_SKULL, TCODColor::white, "A Warg Carcass");
			creature->container = new Container(10);
			creature->entity->ai = new CreatureAI(CreatureAI::AGGRESSIVE);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		// Troll
		case CreatureAI::PATROLLER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_ORGE_PEON_GREEN);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Troll", 1.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(30, 8, 4, 15, 4, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(30, 0, -15);
			creature->entity = new Entity(Entity::TROGLODYTE, stats, health, CHAR_SKULL, TCODColor::white, "A Troll Corpse");
			creature->container = new Container(10);
			creature->entity->ai = new CreatureAI(CreatureAI::PATROLLER);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		case CreatureAI::CHARGER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_ORGE_PEON_GREEN);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Troll", 1.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(30, 8, 4, 15, 4, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(30, 0, -15);
			creature->entity = new Entity(Entity::TROGLODYTE, stats, health, CHAR_SKULL, TCODColor::white, "A Troll Corpse");
			creature->container = new Container(10);
			creature->entity->ai = new CreatureAI(CreatureAI::CHARGER);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		// Demon
		case CreatureAI::SPAWNER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_DEMON_PEON);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Demon", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(30, 6, 5, 10, 6, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(30, 0, -15);
			creature->entity = new Entity(Entity::HUMANOID, stats, health, CHAR_SKULL, TCODColor::white, "A Demon Corpse");
			creature->container = new Container(10);
			creature->entity->ai = new CreatureAI(CreatureAI::SPAWNER);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		case CreatureAI::SEEKER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_DEMON_PEON);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Demon", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(30, 6, 5, 10, 6, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health health = Health(30, 0, -15);
			creature->entity = new Entity(Entity::HUMANOID, stats, health, CHAR_SKULL, TCODColor::white, "A Demon Corpse");
			creature->container = new Container(10);
			creature->entity->ai = new CreatureAI(CreatureAI::SEEKER);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		default: break;
	}
}

void Map::AddBoss(int x, int y)
{
	TCODList<int> xlist, ylist, symlist;

	xlist.push(x + 0); ylist.push(y + 0); symlist.push(CHAR_DEMONLORD_RED_UL);
	xlist.push(x + 1); ylist.push(y + 0); symlist.push(CHAR_DEMONLORD_RED_UR);
	xlist.push(x + 0); ylist.push(y + 1); symlist.push(CHAR_DEMONLORD_RED_LL);
	xlist.push(x + 1); ylist.push(y + 1); symlist.push(CHAR_DEMONLORD_RED_LR);

	Object *boss = new Object(xlist, ylist, symlist, TCODColor::white, "Red Demon Lord", 1000.0f, true);
	Stats stats = Stats(100, 10, 10, 10, 25, 100, 5, 5, 5, 5);
	Health health = Health(100, 100, -50);
	boss->entity = new Entity(Entity::BOSS, stats, health, CHAR_RUBBLE_PILE, TCODColor::peach, "A Pile of Entrails");
	boss->container = new Container(10);
	boss->entity->ai = new BossAI(rng->getInt(AI::VERTICAL_PATTERN, BossAI::NPATTERNTYPES - 1));
	objects.push(boss);
	for(int i = 0; i < boss->sym.size(); i++) SetCreature(boss->x.get(i), boss->y.get(i));
}

void Map::AddNpc(int x, int y)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_PERSON_MALE);
	Object *npc = new Object(xlist, ylist, symlist, TCODColor::white, "A Townsperson", 100.0f, true);
				//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
	Stats stats = Stats(1, 0, 0, 0, 5, 0, 0, 0, 0, 0);
				//  Health(hp, mp, xpnext)
	Health health = Health(1, 0, 0);
	npc->entity = new Entity(Entity::NPC, stats, health, CHAR_SKULL, TCODColor::white, "A Corpse");
	npc->entity->ai = new NpcAI();
	objects.push(npc);
	for(int i = 0; i < npc->sym.size(); i++) SetNpc(npc->x.get(i), npc->y.get(i));
}

int Map::RandomChoiceIndex(TCODList<int> chances)
{
	int chances_sum = 0;
	int running_sum = 0;
	int choice = 0;
	int dice = 1;

	for(int i = 0; i < chances.size(); i++) chances_sum += chances.get(i);
	dice = rng->getInt(1, chances_sum);
 
	// Go through all chances, keeping the sum so far
	for(int i = 0; i < chances.size(); i++)
	{
		running_sum += chances.get(i);

		// See if the dice landed in the part that corresponds to this choice
		if( dice <= running_sum )
		{
			break;
		}
		else
		{
			choice++;
		}
	}
	if(choice >= chances.size()) choice = chances.size() - 1;


	return choice;
}

int Map::RandomChoice(map<int, int> object_chances)
{
	TCODList<int> keys, chances;
	for(map<int, int>::iterator it = object_chances.begin(); it != object_chances.end(); it++)
	{
		keys.push(it->first);
		chances.push(it->second);
	}

	return keys.get(RandomChoiceIndex(chances));
}

void Map::SendToBack(Object *object)
{
	objects.remove(object);
	objects.insertBefore(object, 0);
}

bool Map::IsObstructed(int x, int y) const
{
	Object *object = GetObject(x, y);
	if( object )
	{
		return object->obstructs;
	}
	else
	{
		return false;
	}
}

Object *Map::GetObject(int x, int y) const
{
	for(int i = objects.size() - 1; i >= 0; i--)
	{
		Object *object = objects.get(i);
		for(int j = 0; j < object->sym.size(); j++)
		{
			if( object->x.get(j) == x && object->y.get(j) == y ) return object;
		}
	}
	return NULL;
}

Object *Map::GetEntity(int x, int y) const
{
	for(int i = objects.size() - 1; i >= 0; i--)
	{
		Object *object = objects.get(i);
		if( object->entity && !object->entity->IsDead() )
		{
			for(int j = 0; j < object->sym.size(); j++)
			{
				if( object->x.get(j) == x && object->y.get(j) == y ) return object;
			}
		}
	}
	return NULL;
}
