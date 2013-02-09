#include "Main.hpp"

bool Container::add(Object *owner, Object *object)
{
	// Inventory is full
	if( ( size > 0 && inventory.size() >= size ) || ( owner->entity && owner->entity->stats.str <= mass ) ) return false;

	mass += object->mass;
	inventory.push(object);
	return true;
}
	
void Container::remove(Object *object)
{
	mass -= object->mass;
	inventory.remove(object);
}

Consumable::Consumable(ConsumableType type): type(type)
{
	int ctype = type;
	if( ctype == MUSHROOM_UNKNOWN ) ctype = rng->getInt(MUSHROOM_HEALTH, MUSHROOM_CONFUSION);

	conditions = new Conditions();

	switch( ctype )
	{
		case POTION_ELIXIR:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(1000, 1000, 0);
			Condition *condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, "You Feel All Warm And Fuzzy Inside!", NULL);
			conditions->addToBack(condition);
			break;
		}
		case POTION_HEALTH:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(10, 0, 0);
			Condition *condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, "Physically, You Feel A Little Better", NULL);
			conditions->addToBack(condition);
			break;
		}
		case POTION_HEALTH_STRONG:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(50, 0, 0);
			Condition *condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, "Physically, You Feel A Lot Better!", NULL);
			conditions->addToBack(condition);
			break;
		}
		case POTION_MAGIC:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 5, 0);
			Condition *condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, "Mentally, You Feel A Little Sharper", NULL);
			conditions->addToBack(condition);
			break;
		}
		case POTION_MAGIC_STRONG:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 25, 0);
			Condition *condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, "Mentally, You Feel A Lot Sharper!", NULL);
			conditions->addToBack(condition);
			break;
		}
		case POTION_POISON_ANTIDOTE:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_POISON_ANTIDOTE, 0, -1, *stats, *health, NULL, "You Start To Feel Better", NULL);
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_HEALTH:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(5, 0, 0);
			Condition *condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, "Physically, You Feel A Little Better", NULL);
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_MAGIC:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 2, 0);
			Condition *condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, "Mentally, You Feel A Little Sharper", NULL);
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_POISON:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(-1, 0, 0);
			Condition *condition = new Condition(Condition::CON_POISON, 10*FPSMAX, FPSMAX, *stats, *health, "Poisoned", "You've Been Poisoned!", "You Start To Feel Better");
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_WEAKNESS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, -2, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_STR_MINUS, 10*FPSMAX, 0, *stats, *health, "Weakened", "You Start To Feel Weaker", "You Start To Feel Your Strength Returning");
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_SLUGGISHNESS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, -2, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_SPD_MINUS, 10*FPSMAX, 0, *stats, *health, "Sluggish", "You Begin To Feel A Bit Sluggish", "You Are Able To Move More Quickly");
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_FEEBLENESS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, -2, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_WIL_MINUS, 10*FPSMAX, 0, *stats, *health, "Feeble", "You Begin To Feel More Feeble", "You Don't Feel So Feeble Anymore");
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_INEPTNESS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, -2);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_ACU_MINUS, 10*FPSMAX, 0, *stats, *health, "Inept", "You Begin To Feel Somewhat Inept", "You Feel More Focused");
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_CONFUSION:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_CONFUSION, 10*FPSMAX, 0, *stats, *health, "Confused", "You Begin To Feel Very Confused", "You Feel A Lot Less Confused");
			conditions->addToBack(condition);
			break;
		}
		case MUSHROOM_PARALYSIS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, -1000, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_PARALYSIS, 10*FPSMAX, 0, *stats, *health, "Paralyzed", "You Cannot Move!", "You Can Move Again!");
			conditions->addToBack(condition);
			break;
		}
		case ENTRAILS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(-1, 0, 0);
			Condition *condition = new Condition(Condition::CON_POISON, 15*FPSMAX, FPSMAX, *stats, *health, "Poisoned", "I Don't Think That Was Such A Good Idea", "You Begin To Feel A Lot Less Queasy");
			conditions->addToBack(condition);
			break;
		}
		case ROCKS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_NONE, 0, -1, *stats, *health, NULL, "*CRUNCH* *CRUNCH* *CRUNCH* Hmmm ... Not Bad", NULL);
			conditions->addToBack(condition);
			break;
		}
		default: break;
	}
}

Wearable::Wearable(WearableType type): type(type), worn(false)
{
	conditions = new Conditions();

	switch( type )
	{
		case RING_HP_PLUS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(10, 0, 0);
			Condition *condition = new Condition(Condition::CON_HP_PLUS, -1, 0, *stats, *health, "HPMAX+", "Physically, You Feel A Lot Better!", NULL);
			conditions->addToBack(condition);
			break;
		}
		case RING_MP_PLUS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 10, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 10, 0);
			Condition *condition = new Condition(Condition::CON_MP_PLUS, -1, 0, *stats, *health, NULL, "Mentally, You Feel A Lot Better!", NULL);
			conditions->addToBack(condition);
			break;
		}
		case RING_STR_PLUS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 5, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_STR_PLUS, -1, 0, *stats, *health, NULL, "You Feel A Lot Stronger", NULL);
			conditions->addToBack(condition);
			break;
		}
		case RING_SPD_PLUS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 5, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_SPD_PLUS, -1, 0, *stats, *health, NULL, "You Start To Feel Faster", NULL);
			conditions->addToBack(condition);
			break;
		}
		case RING_WIL_PLUS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 5, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_WIL_PLUS, -1, 0, *stats, *health, NULL, "You Feel A Lot More Driven", NULL);
			conditions->addToBack(condition);
			break;
		}
		case RING_ACU_PLUS:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 5);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(0, 0, 0);
			Condition *condition = new Condition(Condition::CON_ACU_PLUS, -1, 0, *stats, *health, NULL, "Mentally, You Feel A Lot More Focused", NULL);
			conditions->addToBack(condition);
			break;
		}
		case RING_CURSED:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(-1, 0, 0);
			Condition *condition = new Condition(Condition::CON_POISON, -1, 5*FPSMAX, *stats, *health, "Poisoned", "The Ring Is Cursed!", "You Manage To Remove The Cursed Ring");
			conditions->addToBack(condition);
			break;
		}
		default: break;
	}
}

Wieldable::Wieldable(WieldableType type): type(type), wielded(false)
{
	conditions = new Conditions();

	switch( type )
	{
		case CURSED_SWORD:
		{
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats *stats = new Stats(0, 0, 0, -2, 0, 0, 0, 0, 0, 0);
						//  Health(hp, mp, xpnext)
			Health *health = new Health(-1, 0, 0);
			Condition *condition = new Condition(Condition::CON_POISON, -1, 5*FPSMAX, *stats, *health, "Poisoned", "The Sword Is Cursed!", "You Manage To Release The Cursed Sword");
			conditions->addToBack(condition);
			break;
		}
		default: break;
	}
}
