#include "Main.hpp"

Object::Object(TCODList<int> x, TCODList<int> y, TCODList<int> sym, const TCODColor &colour, const char *name, float mass, bool obstructs): x(x), y(y), sym(sym), colour(colour), name(name), mass(mass), obstructs(obstructs), counter(-1), consumable(NULL), container(NULL), entity(NULL), traversable(NULL), wearable(NULL), wieldable(NULL)
{
	for(int i = 0; i < sym.size(); i++) cell.push(engine->map[engine->mapID].GetCell(x.get(i), y.get(i)));
}

Object::~Object()
{
	if( consumable ) delete consumable;
	if( container ) delete container;
	if( entity ) delete entity;
	if( traversable ) delete traversable;
	if( wearable ) delete wearable;
	if( wieldable ) delete wieldable;
}

bool Object::Update()
{
	if( counter == 0 )
	{
		// Rotate sym list for animated objects
		counter = FPSMAX/2;
		int symbol = sym.get(sym.size() - 1);
		for(int i = 0; i < sym.size() - 1; i++) sym.set(sym.get(i + 1), i);
		sym.set(symbol, sym.size() - 1);
	}
	else if( counter > 0 )
	{
		counter--;
	}

	if( entity && entity->ai )
	{
		return entity->ai->Update(this);
	}
	else
	{
		return false;
	}
}

void Object::Render() const
{
	for(int i = 0; i < sym.size(); i++)
	{
		TCODConsole::root->setChar(x.get(i), y.get(i), sym.get(i));
		TCODConsole::root->setCharForeground(x.get(i), y.get(i), colour);
	}
}
