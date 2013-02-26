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
		NONE,						// No Condition

		// Positive Stats Modification
		HP_PLUS,					// Increased HP
		MP_PLUS,					// Increased MP
		HP_REGEN,					// HP Regenerate
		MP_REGEN,					// MP Regenerate
		STR_PLUS,					// Increased Strength
		SPD_PLUS,					// Increased Speed
		WIL_PLUS,					// Increased Willpower
		ACU_PLUS,					// Increased Acuity

		// Abilities
		FAR_SIGHTED,					// Increased Visual Perception
		MASK_SCENT,					// Mask Scent from Creatures
		LEVITATION,					// Float Above the Ground
		CREATURE_SENSE,				// Sense Presence of Creatures
		POISON_ANTIDOTE,			// Poison Antidote
		IMMUNE_FIRE,				// Immune to Fire Magic
		IMMUNE_WATER,				// Immune to Water Magic
		IMMUNE_EARTH,				// Immune to Earth Magic
		IMMUNE_WIND,				// Immune to Wind Magic

		// Negative Stats Modification
		HP_MINUS,					// Decreased HP
		MP_MINUS,					// Decreased MP
		STR_MINUS,					// Decreased Strength
		SPD_MINUS,					// Decreased Speed
		WIL_MINUS,					// Decreased Willpower
		ACU_MINUS,					// Decreased Acuity

		// Afflictions
		NEAR_SIGHTED,				// Decreased Visual Perception
		CONFUSION,					// Random Movement
		PARALYSIS,					// Inability to Move or Attack
		POISON,						// Decreases HP
		BURDENED,					// Overloaded, Decreases all Stats
		VULNERABLE_FIRE,			// Vulnerable to Fire Magic
		VULNERABLE_WATER,			// Vulnerable to Water Magic
		VULNERABLE_EARTH,			// Vulnerable to Earth Magic
		VULNERABLE_WIND,			// Vulnerable to Wind Magic
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
