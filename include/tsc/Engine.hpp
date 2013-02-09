#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "Attributes.hpp"

class Engine
{
	public:
	long seed;
	bool status;

	enum EngineStates
	{
		ACTIVE,
		INACTIVE,
		ENDGAME,
		NENGINESTATES
	} engineState;

	enum CaveTypes
	{
		CAVETYPE_01,
		CAVETYPE_02,
		CAVETYPE_03,
		CAVETYPE_04,
		NCAVETYPES
	} mapID;

	enum FontSizes
	{
		FONT_01,
		FONT_02,
		NFONTS
	} fontID;

	enum MenuStates
	{
		MENU_ACTIVE,
		MENU_INACTIVE,
		NMENUSTATES
	} menuState;

	enum CategoryTypes
	{
		CATEGORY_CONSUMABLE,
		CATEGORY_WEARABLE,
		CATEGORY_WIELDABLE,
		CATEGORY_MISC,
		NCATEGORIES
	};

	Consumable::ConsumableType ctype;

	Object *player;
	Map *map;
	GUI *gui;
	TCODConsole *con;

	TCOD_key_t key;
	TCOD_mouse_t mouse;

	Engine();
	~Engine();

	void Startup();
	void Shutdown();
	void GenerateCaveSystem();

	void Update();
	void Render();
};

#endif
