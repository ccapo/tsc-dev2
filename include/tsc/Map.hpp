#ifndef MAP_HPP
#define MAP_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Feature.hpp"

class Cell
{
	public:
	Feature *feature;				// Feature of this cell
	Cell(): feature(new Floor()) {}
};
 
class Map
{
	public:
	int width, height;
	int nCreatures, nNpcs, nItems, nTraps;
	map<int, int> object_chances;
	TCODList<Object *> objects;

	Map(): width(DISPLAY_WIDTH), height(DISPLAY_HEIGHT - PANEL_HEIGHT - 1), nCreatures(5), nNpcs(5), nItems(16), nTraps(4)
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
	inline TCODColor CellColour(int x, int y) const { return cells[x + y*width].feature->colour; }
	//inline void SetCellColour(int x, int y, TCODColor colour) { cells[x + y*width].feature->colour = colour; }
	inline bool GetFeatureActivated(int x, int y) const { return cells[x + y*width].feature->activated; }
	inline void SetFeatureActivated(int x, int y, bool lvalue) { cells[x + y*width].feature->activated = lvalue; }

	inline Cell GetCell(int x, int y) const { return cells[x + y*width]; }
	inline void SetCell(int x, int y, Cell cell){ cells[x + y*width] = cell; }
	inline void SetFloor(int x, int y){ cells[x + y*width].feature = new Floor(); }
	inline void SetDoor(int x, int y){ cells[x + y*width].feature = new Door(); }
	inline void SetTrap(int x, int y, int type, int mapID = -1, int xTo = -1, int yTo = -1){ cells[x + y*width].feature = new Trap(type, mapID, xTo, yTo); }
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
