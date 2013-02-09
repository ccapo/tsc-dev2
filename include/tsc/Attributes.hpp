#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Condition.hpp"

class Object;

class Consumable
{
	public:
	enum ConsumableType
	{
		POTION_ELIXIR,
		POTION_HEALTH,
		POTION_HEALTH_STRONG,
		POTION_MAGIC,
		POTION_MAGIC_STRONG,
		POTION_POISON_ANTIDOTE,
		MUSHROOM_HEALTH,
		MUSHROOM_MAGIC,
		MUSHROOM_POISON,
		MUSHROOM_WEAKNESS,
		MUSHROOM_SLUGGISHNESS,
		MUSHROOM_FEEBLENESS,
		MUSHROOM_INEPTNESS,
		MUSHROOM_CONFUSION,
		MUSHROOM_PARALYSIS,
		MUSHROOM_UNKNOWN,
		ENTRAILS,
		ROCKS,
		NCONSUMABLETYPES
	} type;

	Conditions *conditions;

	Consumable(ConsumableType type);
	~Consumable(){ if( conditions ) delete conditions; }
};

class Container
{
	public:
	int size;						// Maximum number of Objects. 0 = Unlimited
	float mass;						// Mass of contents
	TCODList<Object *> inventory;	// Inventory of contents

	Container(int size): size(size), mass(0.0f) {}
	~Container(){ inventory.clearAndDelete(); }

	bool add(Object *owner, Object *object);
	void remove(Object *object);
};

class Traversable
{
	public :
	int mapID, xTo, yTo;

	Traversable(int mapID, int xTo, int yTo): mapID(mapID), xTo(xTo), yTo(yTo) {}
	~Traversable(){}
};

class Wearable
{
	public:
	enum WearableType
	{
		WOODEN_SHIELD,
		REINFORCED_SHIELD,
		LEATHER_SHIELD,
		BRONZE_SHIELD,
		IRON_SHIELD,
		MITHRIL_SHIELD,
		HYDRASCALE_SHIELD,
		DRAGONSCALE_SHEILD,
		COTTON_ARMOUR,
		PADDED_ARMOUR,
		LEATHER_ARMOUR,
		BRONZE_ARMOUR,
		IRON_ARMOUR,
		MITHRIL_ARMOUR,
		HYDRASCALE_ARMOUR,
		DRAGONSCALE_ARMOUR,
		RING_HP_PLUS,
		RING_MP_PLUS,
		RING_STR_PLUS,
		RING_SPD_PLUS,
		RING_WIL_PLUS,
		RING_ACU_PLUS,
		RING_CURSED,
		NWEARABLETYPES
	} type;
	bool worn;

	Conditions *conditions;

	Wearable(WearableType type);
	~Wearable(){ if( conditions ) delete conditions; }
};

class Wieldable
{
	public:
	enum WieldableType
	{
		WOODEN_SWORD,
		BRONZE_SWORD,
		IRON_SWORD,
		ANCIENT_SWORD,
		ICE_SWORD,
		FIRE_SWORD,
		CURSED_SWORD,
		MITHRIL_SWORD,
		HYDRASLAYER_SWORD,
		DRAGONSLAYER_SWORD,
		NWIELDABLETYPES
	} type;
	bool wielded;

	Conditions *conditions;

	Wieldable(WieldableType type);
	~Wieldable(){ if( conditions ) delete conditions; }
};

#endif
