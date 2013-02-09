#ifndef CONDITION_HPP
#define CONDITION_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Stats.hpp"

class Condition
{
	public:
	enum ConditionType
	{
		CON_NONE,						// No Condition

		// Positive Stats Modification
		CON_HP_PLUS,					// Increased HP
		CON_MP_PLUS,					// Increased MP
		CON_STR_PLUS,					// Increased Strength
		CON_SPD_PLUS,					// Increased Speed
		CON_WIL_PLUS,					// Increased Willpower
		CON_ACU_PLUS,					// Increased Acuity

		// Abilities
		CON_FARSIGHTED,					// Increased Visual Perception
		CON_MASK_SCENT,					// Mask Scent from Creatures
		CON_LEVITATION,					// Float Above the Ground
		CON_CREATURE_SENSE,				// Sense Presence of Creatures
		CON_POISON_ANTIDOTE,			// Poison Antidote
		CON_IMMUNE_FIRE,				// Immune to Fire Magic
		CON_IMMUNE_WATER,				// Immune to Water Magic
		CON_IMMUNE_EARTH,				// Immune to Earth Magic
		CON_IMMUNE_WIND,				// Immune to Wind Magic

		// Negative Stats Modification
		CON_HP_MINUS,					// Decreased HP
		CON_MP_MINUS,					// Decreased MP
		CON_STR_MINUS,					// Decreased Strength
		CON_SPD_MINUS,					// Decreased Speed
		CON_WIL_MINUS,					// Decreased Willpower
		CON_ACU_MINUS,					// Decreased Acuity

		// Afflictions
		CON_NEARSIGHTED,				// Decreased Visual Perception
		CON_CONFUSION,					// Random Movement
		CON_PARALYSIS,					// Inability to Move or Attack
		CON_POISON,						// Decreases HP
		CON_BURDENED,					// Overloaded, Decreases all Stats
		CON_VULNERABLE_FIRE,			// Vulnerable to Fire Magic
		CON_VULNERABLE_WATER,			// Vulnerable to Water Magic
		CON_VULNERABLE_EARTH,			// Vulnerable to Earth Magic
		CON_VULNERABLE_WIND,			// Vulnerable to Wind Magic
		NCONS
	} type;								// Type of Condition

	bool first;							// First time condition is applied
	int duration;						// Duration of condtion (-1 = permanent, 0 = instantaneous)
	int interval;						// The frequency the condition is applied (-1 = once, 0 = every frame)
	int counter;						// Counter used to keep track of the frequency the condition is applied
	Stats stats;						// Stats for Condition
	Health health;						// Health for Condition
	const char *name;					// Name of Condition
	const char *msg_start;				// Message displayed when Condition starts
	const char *msg_stop;				// Message displayed when Condition stops

	Condition(ConditionType type, int duration, int interval, Stats stats, Health health, const char *name, const char *msg_start, const char *msg_stop): type(type), first(true), duration(duration), interval(interval), counter(0), stats(stats), health(health), name(name), msg_start(msg_start), msg_stop(msg_stop) {}
	~Condition(){}

	// Returns true if condition has finished
	inline bool Update()
	{
		// If the duration for this condition is zero, return true
		if( duration == 0 )
		{
			return true;
		}
		else
		{
			// Otherwise decrease duration
			if( duration > 0 ) duration--;
		}

		// If duration is positive or negative, then return false
		return false;
	}
};

class Conditions
{
	public:
	bool first;
	int size;							// Maximum number of Conditions. 0 = Unlimited
	TCODList<Condition *> inventory;	// Inventory of Conditions

	Conditions(): first(true), size(0) {}
	~Conditions(){ inventory.clearAndDelete(); }

	inline bool addToFront(Condition *condition)
	{
		// Inventory is full
		if( size > 0 && inventory.size() >= size ) return false;

		inventory.push(condition);
		return true;
	}
	inline bool addToBack(Condition *condition)
	{
		// Inventory is full
		if( size > 0 && inventory.size() >= size ) return false;

		inventory.insertBefore(condition, 0);
		return true;
	}
	inline void remove(Condition *condition){ inventory.remove(condition); }
};

#endif
