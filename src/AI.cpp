#include "Main.hpp"

PlayerAI::PlayerAI() {}

PlayerAI::~PlayerAI() {}

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

	//printf("Physical: %d %d %d %d %d\n", owner->entity->stats.hpmax, owner->entity->stats.ap, owner->entity->stats.dp, owner->entity->stats.str, owner->entity->stats.spd);
	//printf("Mental:   %d %d %d %d %d\n", owner->entity->stats.mpmax, owner->entity->stats.map, owner->entity->stats.mdp, owner->entity->stats.wil, owner->entity->stats.acu);

	// Increment displacement
	owner->entity->displacement += elapsed*static_cast<float>(owner->entity->stats.spd);

	if( owner->entity->displacement >= 1.0f )
	{
      	owner->entity->displacement = 0.0f;

		if( TCODConsole::isKeyPressed(TCODK_UP) )
		{
			dy = -1;
			owner->sym.set(CHAR_PLAYER_UP,0);
			UpdateConfused(owner, dx, dy);
		}
		if( TCODConsole::isKeyPressed(TCODK_DOWN) )
		{
			dy = +1;
			owner->sym.set(CHAR_PLAYER_DOWN,0);
			UpdateConfused(owner, dx, dy);
		}
		if( TCODConsole::isKeyPressed(TCODK_LEFT) )
		{
			dx = -1;
			owner->sym.set(CHAR_PLAYER_LEFT,0);
			UpdateConfused(owner, dx, dy);
		}
		if( TCODConsole::isKeyPressed(TCODK_RIGHT) )
		{
			dx = +1;
			owner->sym.set(CHAR_PLAYER_RIGHT,0);
			UpdateConfused(owner, dx, dy);
		}
	}

	Map *map = &engine->map[engine->mapID];
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			map->SetCell(owner->x.get(i), owner->y.get(i), owner->cell.get(i));
			map->SetFeatureActivated(owner->x.get(i), owner->y.get(i), false);
		}
	}
	map->Action(owner, owner->x.get(0) + dx, owner->y.get(0) + dy);
	engine->mapID = static_cast<Engine::CaveTypes>(owner->entity->mapID);
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			owner->cell.set(map->GetCell(owner->x.get(i), owner->y.get(i)), i);
		}
	}

	return true;
}

void PlayerAI::UpdateConfused(Object *owner, int &dx, int &dy)
{
	if( owner->entity->hasCondition(Condition::CON_CONFUSION) )
	{
		dx = rng->getInt(-1, 1);
		dy = rng->getInt(-1, 1);
		owner->sym = rng->getInt(CHAR_PLAYER_RIGHT, CHAR_PLAYER_UP);
	}
}

CreatureAI::CreatureAI() {}

CreatureAI::~CreatureAI() {}

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

		if( !engine->player->entity->IsDead() )
		{
			int dx = owner->x.get(0) - engine->player->x.get(0), dy = owner->y.get(0) - engine->player->y.get(0);
			if( dx*dx + dy*dy < 100 && !owner->entity->hasCondition(Condition::CON_CONFUSION) )
			{
				ChaseOrAttack(owner, engine->player->x.get(0), engine->player->y.get(0));
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

	return true;
}

void CreatureAI::RandomWalk(Object *owner)
{
	static const int dx[NBLOCK] = {-1,  0, +1, -1, 0, +1, -1,  0, +1};
	static const int dy[NBLOCK] = {-1, -1, -1,  0, 0,  0, +1, +1, +1};
	Map *map = &engine->map[engine->mapID];

	int i = rng->getInt(0, NBLOCK - 1);
	owner->obstructs = false;
	bool obstructed = map->IsObstructed(owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
	if( owner->sym.size() > 1 )
	{
		for(int j = 1; j < owner->sym.size(); j++)
		{
			obstructed = obstructed || map->IsObstructed(owner->x.get(j) + dx[i], owner->y.get(j) + dy[i]);
		}
	}
	while( obstructed )
	{
		i = rng->getInt(0, NBLOCK - 1);
		obstructed = map->IsObstructed(owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
		if( owner->sym.size() > 1 )
		{
			for(int j = 1; j < owner->sym.size(); j++)
			{
				obstructed = obstructed || map->IsObstructed(owner->x.get(j) + dx[i], owner->y.get(j) + dy[i]);
			}
		}
	}
	owner->obstructs = true;

	if( dx[i] != 0 || dy[i] != 0 )
	{
		for(int j = 0; j < owner->sym.size(); j++)
		{
			map->SetCell(owner->x.get(j), owner->y.get(j), owner->cell.get(j));
			map->SetFeatureActivated(owner->x.get(j), owner->y.get(j), false);
		}
		map->Action(owner, owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
		if( !owner->entity->IsDead() )
		{
			for(int j = 0; j < owner->sym.size(); j++)
			{
				owner->cell.set(map->GetCell(owner->x.get(j), owner->y.get(j)), j);
				map->SetCreature(owner->x.get(j), owner->y.get(j));
			}
		}
	}
}

void CreatureAI::ChaseOrAttack(Object *owner, int targetx, int targety)
{
	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = targetx - ox;
	int dy = targety - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);
	Map *map = &engine->map[engine->mapID];

	if( distance > sqrt(2.0f) && distance <= 10.0f )
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
			map->SetCell(owner->x.get(i), owner->y.get(i), owner->cell.get(i));
			map->SetFeatureActivated(owner->x.get(i), owner->y.get(i), false);
		}
		map->Action(owner, ox, oy);
		if( !owner->entity->IsDead() )
		{
			for(int i = 0; i < owner->sym.size(); i++)
			{
				owner->cell.set(map->GetCell(owner->x.get(i), owner->y.get(i)), i);
				map->SetCreature(owner->x.get(i), owner->y.get(i));
			}
		}
	}

	if( distance <= sqrt(2.0f) ) owner->entity->Attack(owner, engine->player);
}

BossAI::BossAI() {}

BossAI::BossAI(int type)
{
	PatternCollections(type);
}

BossAI::~BossAI() {}

bool BossAI::Update(Object *owner)
{
	static bool first = false;
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

		if( !engine->player->entity->IsDead() )
		{
			int dx = owner->x.get(0) - engine->player->x.get(0), dy = owner->y.get(0) - engine->player->y.get(0);
			if( dx*dx + dy*dy < 100 && !owner->entity->hasCondition(Condition::CON_CONFUSION) )
			{
				first = true;
				ChaseOrAttack(owner, engine->player->x.get(0), engine->player->y.get(0));
			}
			else
			{
				if( first )
				{
					first = false;
					PatternCollections(rng->getInt(VERTICAL_PATTERN, NPATTERNTYPES - 1));
				}
				WalkPattern(owner);
			}
		}
		else
		{
			RandomWalk(owner);
		}
	}

	return true;
}

void BossAI::RandomWalk(Object *owner)
{
	static const int dx[NBLOCK] = {-1,  0, +1, -1, 0, +1, -1,  0, +1};
	static const int dy[NBLOCK] = {-1, -1, -1,  0, 0,  0, +1, +1, +1};
	Map *map = &engine->map[engine->mapID];

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
			map->SetCell(owner->x.get(j), owner->y.get(j), owner->cell.get(j));
			map->SetFeatureActivated(owner->x.get(j), owner->y.get(j), false);
		}
		map->Action(owner, owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
		if( !owner->entity->IsDead() )
		{
			for(int j = 0; j < owner->sym.size(); j++)
			{
				owner->cell.set(map->GetCell(owner->x.get(j), owner->y.get(j)), j);
				map->SetCreature(owner->x.get(j), owner->y.get(j));
			}
		}
	}
}

void BossAI::WalkPattern(Object *owner)
{
	static int x = owner->x.get(0), y = owner->y.get(0);
	Map *map = &engine->map[engine->mapID];

	// Increment along prescribed pattern list
	ListPattern(owner, x, y);

	for(int j = 0; j < owner->sym.size(); j++)
	{
		map->SetCell(owner->x.get(j), owner->y.get(j), owner->cell.get(j));
		map->SetFeatureActivated(owner->x.get(j), owner->y.get(j), false);
	}
	map->Action(owner, x, y);
	if( !owner->entity->IsDead() )
	{
		for(int j = 0; j < owner->sym.size(); j++)
		{
			owner->cell.set(map->GetCell(owner->x.get(j), owner->y.get(j)), j);
			map->SetCreature(owner->x.get(j), owner->y.get(j));
		}
	}
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

	stepCounter = (stepCounter + 1) % stepMax;
	if( stepCounter == 0 )
	{
		patternCounter = (patternCounter + 1) % patternMax;
		if( patternCounter == 0 )
		{
			if( second )
			{
				second = false;
				PatternCollections(rng->getInt(VERTICAL_PATTERN, NPATTERNTYPES - 1));
			}
			else
			{
				second = true;
			}
		}
	}
}

void BossAI::ChaseOrAttack(Object *owner, int targetx, int targety)
{
	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = targetx - ox;
	int dy = targety - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);
	Map *map = &engine->map[engine->mapID];

	if( distance > sqrt(2.0f) && distance <= 10.0f )
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
			map->SetCell(owner->x.get(i), owner->y.get(i), owner->cell.get(i));
			map->SetFeatureActivated(owner->x.get(i), owner->y.get(i), false);
		}
		map->Action(owner, ox, oy);
		if( !owner->entity->IsDead() )
		{
			for(int i = 0; i < owner->sym.size(); i++)
			{
				owner->cell.set(map->GetCell(owner->x.get(i), owner->y.get(i)), i);
				map->SetCreature(owner->x.get(i), owner->y.get(i));
			}
		}
	}

	if( distance <= sqrt(2.0f) ) owner->entity->Attack(owner, engine->player);
}

NpcAI::NpcAI() {}

NpcAI::~NpcAI() {}

bool NpcAI::Update(Object *owner)
{
	static bool arrived = true;
	static int xTarget = 0, yTarget = 0;
	Map *map = &engine->map[engine->mapID];

	if( arrived )
	{
		arrived = false;
		xTarget = rng->getInt(1, map->width - 2);
		yTarget = rng->getInt(1, map->height - 2);
		while( map->IsObstructed(xTarget, yTarget) || map->CellType(xTarget, yTarget) == Feature::TRAP )
		{
			xTarget = rng->getInt(1, map->width - 2);
			yTarget = rng->getInt(1, map->height - 2);
		}
	}
	else
	{
		MoveToTarget(owner, xTarget, yTarget);
		for(int i = 0; i < owner->sym.size(); i++)
		{
			if(owner->x.get(i) == xTarget && owner->y.get(i) == yTarget) arrived = true;
		}
	}

	return true;
}

void NpcAI::MoveToTarget(Object *owner, int targetx, int targety)
{
	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = targetx - ox;
	int dy = targety - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);
	Map *map = &engine->map[engine->mapID];

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
			map->SetCell(owner->x.get(i), owner->y.get(i), owner->cell.get(i));
			map->SetFeatureActivated(owner->x.get(i), owner->y.get(i), false);
			map->Action(owner, owner->x.get(i) + dx, owner->y.get(i) + dy);
		}
		if( !owner->entity->IsDead() )
		{
			for(int i = 0; i < owner->sym.size(); i++)
			{
				owner->cell.set(map->GetCell(owner->x.get(i), owner->y.get(i)), i);
				map->SetNpc(owner->x.get(i), owner->y.get(i));
			}
		}
	}
}
