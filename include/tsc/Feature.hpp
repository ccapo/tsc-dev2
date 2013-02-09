#ifndef FEATURE_HPP
#define FEATURE_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "Condition.hpp"

class Object;

class Feature
{
	public:
	enum FeatureType
	{
		FLOOR,
		WALL,
		DOOR,
		TRAP,
		CREATURE,
		NPC,
		NFEATURES
	};
	int cellType;
	int trapType;

	bool explored;		// Has this feature been explored?
	bool activated;		// Has this feature been activated?
	TCODColor colour;	// The background colour for this feature
	TCODColor darkWall;
	TCODColor darkGround;

	Feature();
	virtual void Action(Object *owner, int x, int y) = 0;
};

class Floor: public Feature
{
	public:
	Floor();
	void Action(Object *owner, int x, int y);
};

class Wall: public Feature
{
	public:
	Wall();
	void Action(Object *owner, int x, int y);
};
 
class Door: public Feature
{
	public:
	bool open;
	Door();
	void Action(Object *owner, int x, int y);
};

class Trap: public Feature
{
	public:
	enum TrapType
	{
		INVISIBLEBARRIER,
		DARKTUNNEL,
		NTRAPS
	};

	int mapID;
	int xTo, yTo;
	TCODColor flashColor;
	Conditions *conditions;	// Trap's List of Conditions

	Trap(int type, int mapID, int xTo, int yTo);
	~Trap(){ if( conditions ) delete conditions; }

	void Action(Object *owner, int x, int y);
};

class Creature: public Feature
{
	public:
	Creature();
	void Action(Object *owner, int x, int y);
};

class Npc: public Feature
{
	public:
	Npc();
	void Action(Object *owner, int x, int y);
};

#endif
