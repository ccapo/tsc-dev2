#include "Main.hpp"

void Entity::Attack(Object *owner, Object *target)
{
	TCODColor colour = TCODColor::lightGrey;
	if( owner == engine->player ) colour = TCODColor::blue;

	if( target->entity && !target->entity->IsDead() )
	{
		int damage = target->entity->TakeDamage(stats.ap + stats.str/2 + stats.spd/4);
		if( damage > 0 )
		{
			engine->gui->MessageLog(colour, "%s Attacks %s", owner->name, target->name);
			if( target->entity->IsDead() )
			{
				owner->entity->health.xp += target->entity->health.xp;
				Death(target);
			}
		}
		else
		{
			engine->gui->MessageLog(colour, "%s Attacks %s In Vain", owner->name, target->name);			
		}
	}
}

int Entity::TakeDamage(int amount)
{
	amount -= stats.dp + stats.str/2 + stats.spd/4;
	if( amount > 0 )
	{
		health.hp -= amount;
	}
	else
	{
		amount = 0;
	}
	return amount;
}

int Entity::Heal(int amount)
{
	health.hp += amount;
	if( health.hp > stats.hpmax )
	{
		amount -= health.hp - stats.hpmax;
		health.hp = stats.hpmax;
	}
	return amount;
}

void Entity::Death(Object *owner)
{
	Map *map = &engine->map[engine->mapID];

	// Determine Cell Type
	int celltype;
	for(int i = 0; i < owner->sym.size(); i++) celltype = map->CellType(owner->x.get(i), owner->y.get(i));

	// Send Notice to Message Log
	switch( celltype )
	{
		case Feature::WALL:
		{
			engine->gui->MessageLog(TCODColor::lightGrey, "The Wall Crumbles Away");
			break;
		}
		case Feature::DOOR:
		{
			engine->gui->MessageLog(TCODColor::lightGrey, "The Door Crumbles Away");
			break;
		}
		default:
		{
			engine->gui->MessageLog(TCODColor::red, "%s Died", owner->name);
			break;
		}
	}

	// Transform the Entity into a corpse!
	if( owner->entity->ai )
	{
		delete owner->entity->ai;
		owner->entity->ai = NULL;
	}

	for(int i = 0; i < owner->sym.size(); i++) owner->sym.set(owner->entity->corpseSym,i);
	owner->entity->health.hp = 0;
	owner->colour = owner->entity->corpseColour;	
	owner->name = owner->entity->corpseName;
	owner->obstructs = false;

	// Reset the Action for this Cell
	for(int i = 0; i < owner->sym.size(); i++)
	{
		map->RevertCell(owner->x.get(i), owner->y.get(i));
		map->Activated(owner->x.get(i), owner->y.get(i), false);
	}

	// Make sure corpses are drawn before living entities
	map->SendToBack(owner);
}

void Entity::updateConditions(Object *owner)
{
	for(int i = 0; i < owner->entity->conditions->inventory.size(); i++)
	{
		Condition *condition = owner->entity->conditions->inventory.get(i);
		//printf("%s\n", condition->name);
		
		// Apply Condition
		if( condition->first || condition->counter == condition->interval )
		{
			condition->first = false;
			condition->counter = 0;
			owner->entity->stats += condition->stats;
			owner->entity->health += condition->health;
			owner->entity->health.hp = Clamp<int>(owner->entity->health.hp, 0, owner->entity->stats.hpmax);
			owner->entity->health.mp = Clamp<int>(owner->entity->health.mp, 0, owner->entity->stats.mpmax);

			switch( condition->type )
			{
				case Condition::CON_MP_REGEN:
				{
					condition->health.mp = owner->entity->stats.acu;
					condition->interval = 10*FPSMAX - 5*owner->entity->stats.wil;
					break;
				}
				case Condition::CON_POISON_ANTIDOTE:
				{
					if( hasCondition(Condition::CON_POISON) )
					{
						Condition *con = getCondition(Condition::CON_POISON);
						owner->entity->conditions->remove(con);
						owner->colour = TCODColor::white;
					}
					break;
				}
				case Condition::CON_POISON:
				{
					owner->colour = TCODColor::green;
					break;
				}
				default: break;
			}
		}
		else
		{
			if( condition->interval > 0 ) condition->counter++;
		}

		// Update Condition
		bool finished = condition->Update();

		// Remove Condition if Finished
		if( finished )
		{
			if( condition->msg_stop && owner == engine->player ) engine->gui->MessageLog(TCODColor::green, "%s", condition->msg_stop);
			if( condition->type == Condition::CON_POISON ) owner->colour = TCODColor::white;
			owner->entity->conditions->remove(condition);
		}
	}
}

void Entity::addConditions(Object *owner)
{
	for(int i = 0; i < owner->container->inventory.size(); i++)
	{
		Object *object = owner->container->inventory.get(i);
		if( object->wearable && object->wearable->worn )
		{
			if( object->wearable->conditions->first && owner == engine->player )
			{
				object->wearable->conditions->first = false;
				engine->gui->MessageLog(TCODColor::lightGrey, "You Put On %s", object->name);
			}

			for(int j = 0; j < object->wearable->conditions->inventory.size(); j++)
			{
				Condition *condition = object->wearable->conditions->inventory.get(j);
				if( condition && condition->first )
				{
					if( owner == engine->player ) engine->gui->MessageLog(TCODColor::red, "%s", condition->msg_start);
					owner->entity->conditions->addToBack(condition);
				}
			}
		}
		if( object->wieldable && object->wieldable->wielded )
		{
			if( object->wieldable->conditions->first && owner == engine->player )
			{
				object->wieldable->conditions->first = false;
				engine->gui->MessageLog(TCODColor::lightGrey, "You Wield %s", object->name);
			}

			for(int j = 0; j < object->wieldable->conditions->inventory.size(); j++)
			{
				Condition *condition = object->wieldable->conditions->inventory.get(j);
				if( condition && condition->first )
				{
					if( owner == engine->player ) engine->gui->MessageLog(TCODColor::red, "%s", condition->msg_start);
					owner->entity->conditions->addToBack(condition);
				}
			}
		}
	}

	if( owner->container->mass >= owner->entity->stats.str )
	{
					//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
		Stats stats = Stats(0, -1, -1, 0, -2, 0, -1, -1, 0, 0);
					//  Health(hp, mp, xpnext)
		Health health = Health(0, 0, 0);
		Condition *condition;
		if( hasCondition(Condition::CON_BURDENED) )
		{
			condition = new Condition(Condition::CON_BURDENED, 0, -1, stats, health, "Burdened", NULL, NULL);
		}
		else
		{
			condition = new Condition(Condition::CON_BURDENED, 1, -1, stats, health, "Burdened", "You Feel Your Belongings Weighing You Down", NULL);
		}
		if( owner == engine->player && condition->msg_start ) engine->gui->MessageLog(TCODColor::red, "%s", condition->msg_start);
		owner->entity->conditions->addToBack(condition);
	}
}

bool Entity::hasCondition(Condition::ConditionType type) const
{
	return ( getCondition(type) != NULL );
}

Condition *Entity::getCondition(Condition::ConditionType type) const
{
	for(int i = 0; i < conditions->inventory.size(); i++)
	{
		Condition *condition = conditions->inventory.get(i);
		if( condition->type == type ) return condition;
	}
	return NULL;
}
