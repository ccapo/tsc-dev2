#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Stats.hpp"
#include "Condition.hpp"
#include "AI.hpp"

class Entity
{
	public:
	Stats base_stats;		// Base Entity Stats
	Stats stats;			// Current Entity Stats
	Health health;			// Current Entity Health

	int mapID;				// Map ID
	float displacement;		// Entity's Movement Displacement

	int corpseSym;			// Entity's Corpse Symbol
	TCODColor corpseColour;	// Entity's Corpse Colour
	const char *corpseName; // Entity's Corpse Name

	AI *ai;					// Entity's AI
	Conditions *conditions;	// Entity's Conditions

	Entity(Stats stats, Health health, int corpseSym, const TCODColor &corpseColour, const char *corpseName): base_stats(stats), stats(stats), health(health), mapID(0), displacement(0.0f), corpseSym(corpseSym), corpseColour(corpseColour), corpseName(corpseName), ai(NULL)
	{
		conditions = new Conditions();
	}

	~Entity()
	{
		if( ai ) delete ai;
		if( conditions ) delete conditions;
	}

	void Attack(Object *owner, Object *target);
	int TakeDamage(int amount);
	int Heal(int amount);
	inline bool IsDead() { return health.hp <= 0; }
	void Death(Object *owner);

	// Condition functions
	void updateConditions(Object *owner);
	void addConditions(Object *owner);
	bool hasCondition(Condition::ConditionType type) const;
	Condition *getCondition(Condition::ConditionType type) const;
};

#endif
