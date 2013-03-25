#ifndef MAP_HPP
#define MAP_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Feature.hpp"

class Cell
{
	public:
	Feature *feature;				// Current Feature of this cell
	Feature *feature_initial;		// Initial Feature of this cell

	Cell(): feature(new Floor()), feature_initial(new Floor()) {}
	Cell(Feature *feature): feature(feature), feature_initial(feature) {}
	~Cell()
	{
		if( feature ) delete feature;
		if( feature_initial ) delete feature_initial;
	}

	void revert()
	{
		feature = feature_initial;
	}
};
 
class Map
{
	public:
	int width, height, type;
	int nCreatures, nNpcs, nItems, nTraps;
	map<int, int> object_chances;
	TCODList<Object *> objects;

	Map(): width(DISPLAY_WIDTH), height(DISPLAY_HEIGHT - PANEL_HEIGHT - 1), type(-1), nCreatures(10), nNpcs(0), nItems(4), nTraps(4)
	{
		cells = new Cell[width*height];
	}
	~Map()
	{
		objects.clearAndDelete();
		delete [] cells;
	}

	void GenerateMap(int caveType);
	void Render();

	inline void Action(Object *owner, int x, int y){ cells[x + y*width].feature->Action(owner, x, y); }
	inline int CellType(int x, int y) const { return cells[x + y*width].feature->cellType; }
	inline int TrapType(int x, int y) const { return cells[x + y*width].feature->trapType; }
	inline TCODColor Colour(int x, int y) const { return cells[x + y*width].feature->colour; }
	inline void Colour(int x, int y, TCODColor colour) { cells[x + y*width].feature->colour = colour; }
	inline bool Activated(int x, int y) const { return cells[x + y*width].feature->activated; }
	inline void Activated(int x, int y, bool lvalue) { cells[x + y*width].feature->activated = lvalue; }
	inline bool Explored(int x, int y) const { return cells[x + y*width].feature->explored; }
	inline void Explored(int x, int y, bool lvalue) { cells[x + y*width].feature->explored = lvalue; }
	inline void RevertCell(int x, int y){ cells[x + y*width].revert(); }
	inline void SetFloor(int x, int y){ Cell *cell = new Cell(new Floor()); cells[x + y*width] = *cell; }
	inline void SetDoor(int x, int y){ Cell *cell = new Cell(new Door()); cells[x + y*width] = *cell; }
	inline void SetTrap(int x, int y, int type, int mapID = -1, int xTo = -1, int yTo = -1){ Cell *cell = new Cell(new Trap(type, mapID, xTo, yTo)); cells[x + y*width] = *cell; }
	inline void SetCreature(int x, int y){ cells[x + y*width].feature = new Creature(); }
	inline void SetNpc(int x, int y){ cells[x + y*width].feature = new Npc(); }

	void GetItemChances(int caveType);
	void GetTrapChances(int caveType);
	void GetCreatureChances(int caveType);
	void AddWall(int x, int y, bool imprevious);
	void AddTunnelUp(int x, int y, int mapID, int xTo, int yTo);
	void AddTunnelDown(int x, int y, int mapID, int xTo, int yTo);
	void AddTunnelSurface(int x, int y, int mapID, int xTo, int yTo);
	void AddItem(int x, int y);
	void AddTrap(int x, int y);
	void AddCreature(int x, int y);
	void AddBoss(int x, int y);
	void AddNpc(int x, int y);
	int RandomChoiceIndex(TCODList<int> chances);
	int RandomChoice(map<int, int> object_chances);

	void SendToBack(Object *object);
	bool IsObstructed(int x, int y) const;
	Object *GetObject(int x, int y) const;
	Object *GetEntity(int x, int y) const;

	protected:
	Cell *cells;
};

#endif
