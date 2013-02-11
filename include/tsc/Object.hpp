#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Global.hpp"
#include "Attributes.hpp"
#include "Entity.hpp"

class Object
{
	public:

	// Object Types
	enum ObjectType
	{
		CONSUMABLE,
		CONTAINER,
		ENTITY,
		TRAVERSABLE,
		WEARABLE,
		WIELDABLE,
		MISC,
		NOBJECTTYPES
	};

	// Basic Attributes
	TCODList<int> x, y;				// Object's position list on the map
	float xc, yc;					// Object's central position on the map
	TCODList<int> sym;				// Object's symbol list on the map
	TCODColor colour;				// Object's colour on the map
	const char *name;				// Object's name
	float mass;						// Object's mass
	bool obstructs;					// Does this object obstruct?
	int counter;					// Object's animation counter

	// Optional Attributes
	Consumable *consumable;			// Pointer to Consumable Attribute
	Container *container;			// Pointer to Container Attribute
	Entity *entity;					// Pointer to Entity Attribute
	Traversable *traversable;		// Pointer to Traversable Attribute
	Wearable *wearable;				// Pointer to Wearable Attribute
	Wieldable *wieldable;			// Pointer to Wieldable Attribute
 
	Object(TCODList<int> x, TCODList<int> y, TCODList<int> sym, const TCODColor &colour, const char *name, float mass, bool obstructs);
	~Object();

	bool Update();
	void Render() const;
};

#endif
