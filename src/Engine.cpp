#include "Main.hpp"

Engine::Engine(): seed(time(NULL)), status(true), engineState(ACTIVE), mapID(CAVETYPE_01), fontID(FONT_02), menuState(MENU_INACTIVE)
{
	static const char *fonts[NFONTS] = {"data/fonts/arial8x8-2.png",
										"data/fonts/arial16x16-2.png"};
	int fontFlags = TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE;
	int nCol = 32, nRow = 14;
	int initialDelay = 100, interval = 10;

	TCODConsole::setCustomFont(fonts[fontID], fontFlags, nCol, nRow);
	TCODConsole::initRoot(DISPLAY_WIDTH, DISPLAY_HEIGHT, "tsc-dev v2.0", false);
	TCODSystem::setFps(FPSMAX);
	TCODConsole::setKeyboardRepeat(initialDelay, interval);
	TCODMouse::showCursor(true);

	// Assign extra ascii keys
	int x = 0, y = 8;
	TCODConsole::mapAsciiCodeToFont(CHAR_STAIRS_UP, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_STAIRS_DOWN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_HOLE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_WATER_01, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_WATER_02, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_LAVA_01, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_LAVA_02, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_CHEST_OPEN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CHEST_CLOSED, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_POTION_YELLOW, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_POTION_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_POTION_GREEN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_POTION_BLUE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_KEY, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_RING_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_RING_GREEN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_RING_BLUE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_RING_RED_BIG, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_RING_GREEN_BIG, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_RING_BLUE_BIG, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SHIELD_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SHIELD_GREY, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SHIELD_GOLD, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SWORD_BASIC, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SWORD_STEEL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SWORD_GOLD, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_YELLOW, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_GREEN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_BLUE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_MITHRIL, x++, y);
	x = 0; y++;

	TCODConsole::mapAsciiCodeToFont(CHAR_CHARGEBAR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_RIGHT, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_DOWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_LEFT, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_UP, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_GUARDIAN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_KEEPER, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PERSON_MALE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PERSON_FEMALE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_GUARD, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_WARLOCK_PURPLE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_NECROMANCER_APPENTICE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_NECROMANCER_MASTER, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_ARCHER, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_AXEBEARER, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_MAGE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_HERO, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_AXEBEARER, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_MAGE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_HERO, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_PEON, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_IMP_BLUE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_IMP_RED, x++, y);
	x = 0; y++;

	TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_PEON_GREEN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_WARRIOR_GREEN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_PEON_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_WARRIOR_RED, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_PEON, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_HERO, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SPRITE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_ORC_PEON, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORC_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORC_HERO, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_ORC_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_PEON, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_HERO, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_FLAYER_WARRIOR, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLAYER_MAGE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SKULL, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_GREY, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_RED, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SLIME_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SLIME_GREEN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_EYEBALL, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_VERMIN_BROWN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SNAKE_GREEN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_RUBBLE_PILE, x++, y);
	x = 0; y++;

	TCODConsole::mapAsciiCodeToFont(CHAR_SCORPIAN_YELLOW, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SCORPIAN_BLACK, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_BLACK, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_GREEN, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_RED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_YELLOW, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BAT_BROWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BAT_BLUE, x++, y);

	// Environment Tiles
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_A, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_B, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_C, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_D, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_E, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_F, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TREE_G, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_A, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_B, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_C, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_D, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MUSHROOM, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLOWERS_WHITE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLOWERS_BLUE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_TEMPLE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TOWN, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CAVE, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BED, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_TABLE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BOOKCASE, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CHAIR_RIGHT, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CHAIR_LEFT, x++, y);
	x = 0; y++;

	// Minor Bosses (Upper Portion)
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_UR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_UR, x++, y);

	// Final Boss (Upper Portion)
	TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_UL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_UR, x++, y);
	x = 0; y++;

	// Minor Bosses (Lower Portion)
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_LR, x++, y);

	TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_LR, x++, y);

	// Final Boss (Lower Portion)
	TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_LL, x++, y);
	TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_LR, x++, y);
}

Engine::~Engine()
{
	if( player ) delete player;
	if( map ) delete [] map;
	if( gui ) delete gui;
	if( con ) delete con;
}

void Engine::Startup()
{
	int w = 3*DISPLAY_WIDTH/4, h = 3*(DISPLAY_HEIGHT - PANEL_HEIGHT)/4;

	map = new Map[NMAPS];

	GenerateCaveSystem();

	int x = rng->getInt(1, map[mapID].width - 2);
	int y = rng->getInt(1, map[mapID].height - 2);
	while( map[mapID].IsObstructed(x, y) || map[mapID].CellType(x, y) == Feature::TRAP )
	{
		x = rng->getInt(1, map[mapID].width - 2);
		y = rng->getInt(1, map[mapID].height - 2);
	}

	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_PLAYER_RIGHT);
	player = new Object(xlist, ylist, symlist, TCODColor::white, "The Player", 100.0f, true);
	Stats player_stats = Stats(25, 8, 4, 10, 25, 15, 4, 2, 2, 1);
	Health player_health = Health(player_stats.hpmax, player_stats.mpmax, 100);
	player->entity = new Entity(player_stats, player_health, CHAR_SKULL, TCODColor::darkRed, "Your Corpse");
	player->entity->ai = new PlayerAI();
	Stats stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Health health = Health(0, 1, 0);
	player->entity->conditions->addToFront(new Condition(Condition::CON_NONE, -1, 5*FPSMAX, stats, health, NULL, NULL, NULL));
	player->container = new Container(0);

	Object *item;
	item = new Object(x, y, CHAR_SWORD_BASIC, TCODColor::white, "A Bronze Sword", 1.0f, false);
	item->wieldable = new Wieldable(Wieldable::BRONZE_SWORD);
	player->container->add(player, item);

	item = new Object(x, y, CHAR_SWORD_STEEL, TCODColor::white, "An Iron Sword", 1.0f, false);
	item->wieldable = new Wieldable(Wieldable::IRON_SWORD);
	item->wieldable->wielded = true;
	player->container->add(player, item);

	item = new Object(x, y, CHAR_ARMOUR_BROWN, TCODColor::white, "A Cotton Tunic", 0.25f, false);
	item->wearable = new Wearable(Wearable::COTTON_ARMOUR);
	player->container->add(player, item);

	item = new Object(x, y, CHAR_ARMOUR_BROWN, TCODColor::white, "A Leather Tunic", 0.5f, false);
	item->wearable = new Wearable(Wearable::LEATHER_ARMOUR);
	item->wearable->worn = true;
	player->container->add(player, item);

	item = new Object(x, y, CHAR_RING_RED, TCODColor::white, "A HP+ Ring", 0.1f, false);
	item->wearable = new Wearable(Wearable::RING_HP_PLUS);
	item->wearable->worn = false;
	player->container->add(player, item);

	ctype = Consumable::MUSHROOM_UNKNOWN;
	item = new Object(x, y, CHAR_MUSHROOM, TCODColor::white, "An Unknown Mushroom", 0.05f, false);
	item->consumable = new Consumable(ctype);
	player->container->add(player, item);

	item = new Object(x, y, CHAR_POTION_BLUE, TCODColor::white, "A Health Potion", 0.25f, false);
	item->consumable = new Consumable(Consumable::POTION_HEALTH);
	player->container->add(player, item);

	item = new Object(x, y, CHAR_RUBBLE_PILE, TCODColor::white, "A Pebble", 0.05f, false);
	item->consumable = new Consumable(Consumable::ROCKS);
	player->container->add(player, item);

	item = new Object(x, y, CHAR_KEY, TCODColor::white, "A Key", 0.1f, false);
	player->container->add(player, item);

	gui = new GUI();
	gui->MessageLog(TCODColor::red, "Welcome Adventurer!\nPrepare to perish in the Serpentine Caves.");

	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::yellow, TCODColor::black);
	con = new TCODConsole(w, h);
	con->setAlignment(TCOD_CENTER);
	con->setBackgroundFlag(TCOD_BKGND_SET);
	con->setDefaultBackground(TCODColor::black);
	con->setDefaultForeground(TCODColor::white);
}

void Engine::Shutdown()
{
#ifndef DEV
	// Fade Out
	for(int i = 1; i <= 2*FPSMAX; i++)
	{
		int fade = 255*(2*FPSMAX - i)/(2*FPSMAX - 1);
		TCODConsole::setFade(fade, TCODColor::black);
		TCODConsole::root->flush();
	}
#endif
}

void Engine::GenerateCaveSystem()
{
	const int dx[NBORDER] = {-1,  0, +1, -1, +1, -1,  0, +1};
	const int dy[NBORDER] = {-1, -1, -1,  0,  0, +1, +1, +1};
	int g_depthMax = -1;

	// Cave System Data
	struct CaveData
	{
		bool occupied;
		int mapID;
		int depth;
	} caveData[NSIZE*NSIZE];

	// Initialize caveData
	for(int y = 0; y < NSIZE; y++)
	{
		for(int x = 0; x < NSIZE; x++)
		{
			int offset =  x + y*NSIZE;
			caveData[offset].occupied = false;
			caveData[offset].mapID = -1;
			caveData[offset].depth = -1;
		}
	}

	int srcMapID = 0;
	int srcDepth = -5;
	int srcCaveType = srcDepth/5;
	map[srcMapID].GenerateMap(srcCaveType);

	// Seed Brownian Tree Cave System
	int offset =  NSIZE/2 + (NSIZE/2)*NSIZE;
	caveData[offset].occupied = true;
	caveData[offset].mapID = 1;
	caveData[offset].depth = 0;
	//printf("Map: %d, Depth: %d\n", caveData[offset].mapID, caveData[offset].depth);

	// Generate Map
	int dstMapID = caveData[offset].mapID;
	int dstDepth = caveData[offset].depth;
	int dstCaveType = dstDepth/5;
	map[dstMapID].GenerateMap(dstCaveType);

	int xFrom = map[srcMapID].width/2;
	int yFrom = map[srcMapID].height/2;
	int xTo = rng->getInt(2, map[dstMapID].width - 3);
	int yTo = rng->getInt(2, map[dstMapID].height - 3);
	//printf("(%d, %d) ", dstMapID, dstDepth);
	while( map[dstMapID].IsObstructed(xTo, yTo) || map[dstMapID].CellType(xTo, yTo) == Feature::TRAP )
	{
		xTo = rng->getInt(2, map[dstMapID].width - 3);
		yTo = rng->getInt(2, map[dstMapID].height - 3);
	}
	map[srcMapID].AddTunnelDown(xFrom, yFrom, dstMapID, xTo, yTo);
	map[dstMapID].AddTunnelSurface(xTo, yTo, srcMapID, xFrom, yFrom);

	// Add A Map
	for(int i = 2; i < NMAPS; i++)
	{
		// Start Map Position At Random
		int x, y, offset;
		OVER: do
		{
			x = rng->getInt(1, NSIZE - 2);
			y = rng->getInt(1, NSIZE - 2);
			offset =  x + y*NSIZE;
		} while( caveData[offset].occupied );

		// Random Walk Map Position Until Adjacent To Existing Maps
		bool vacant = true;
		for(int j = 0; j < NBORDER; j++)
		{
			offset = (x + dx[j]) + (y + dy[j])*NSIZE;
			vacant = vacant && !caveData[offset].occupied;
		}
		while( vacant )
		{
			int k = rng->getInt(0, NBORDER - 1);
			x += dx[k];
			y += dy[k];

			// Start Over If We Leave The Grid
			if(x < 1 || x >= NSIZE - 1 || y < 1 || y >= NSIZE - 1) goto OVER;
			vacant = true;
			for(int j = 0; j < NBORDER; j++)
			{
				offset = (x + dx[j]) + (y + dy[j])*NSIZE;
				vacant = vacant && !caveData[offset].occupied;
			}
		}

		// Store Information For Current Map
		offset =  x + y*NSIZE;
		caveData[offset].occupied = true;
		caveData[offset].mapID = i;

		// Determine Maximum Depth Of Adjacent Maps
		int depthMax = 0;
		for(int j = 0; j < NBORDER; j++)
		{
			offset = (x + dx[j]) + (y + dy[j])*NSIZE;
			if( caveData[offset].depth >= depthMax ) depthMax = caveData[offset].depth;
		}

		// Assign Depth For Current Map
		depthMax++;
		offset =  x + y*NSIZE;
		caveData[offset].depth = depthMax;

		// Keep Track Of Global Max. Depth
		if( depthMax >= g_depthMax ) g_depthMax = depthMax;

		// Generate Map
		int srcMapID = caveData[offset].mapID;
		int srcDepth = caveData[offset].depth;
		int srcCaveType = srcDepth/5;
		map[srcMapID].GenerateMap(srcCaveType);

		//printf("Map: %d, Depth: %d\n", srcMapID, srcDepth);
		//printf("Connected To Maps: ");
		for(int j = 0; j < NBORDER; j++)
		{
			offset = (x + dx[j]) + (y + dy[j])*NSIZE;
			if( caveData[offset].depth >= depthMax - 1 )
			{
				// Connect Maps
				int dstMapID = caveData[offset].mapID;
				int xFrom = rng->getInt(2, map[srcMapID].width - 3);
				int yFrom = rng->getInt(2, map[srcMapID].height - 3);
				int xTo = rng->getInt(2, map[dstMapID].width - 3);
				int yTo = rng->getInt(2, map[dstMapID].height - 3);
				//printf("(%d, %d) ", dstMapID, dstDepth);

				while( map[srcMapID].IsObstructed(xFrom, yFrom) || map[srcMapID].CellType(xFrom, yFrom) == Feature::TRAP )
				{
					xFrom = rng->getInt(2, map[srcMapID].width - 3);
					yFrom = rng->getInt(2, map[srcMapID].height - 3);
				}

				while( map[dstMapID].IsObstructed(xTo, yTo) || map[dstMapID].CellType(xTo, yTo) == Feature::TRAP )
				{
					xTo = rng->getInt(2, map[dstMapID].width - 3);
					yTo = rng->getInt(2, map[dstMapID].height - 3);
				}

				map[srcMapID].AddTunnelUp(xFrom, yFrom, dstMapID, xTo, yTo);
				map[dstMapID].AddTunnelDown(xTo, yTo, srcMapID, xFrom, yFrom);
			}
		}
		//printf("\n");
	}

	// Handle Dark Tunnel Traps
	for(int i = 0; i < NMAPS; i++)
	{
		for(int y = 0; y < map[i].height; y++)
		{
			for(int x = 0; x < map[i].width; x++)
			{
				if( map[i].TrapType(x, y) == Trap::DARKTUNNEL )
				{
					if( i <= NMAPS - 5 )
					{
						int dstMapID = rng->getInt(i + 1, i + 4);
						int xTo = rng->getInt(1, map[dstMapID].width - 2);
						int yTo = rng->getInt(1, map[dstMapID].height - 2);
						while( map[dstMapID].IsObstructed(xTo, yTo) || map[dstMapID].CellType(xTo, yTo) == Feature::TRAP )
						{
							xTo = rng->getInt(1, map[dstMapID].width - 2);
							yTo = rng->getInt(1, map[dstMapID].height - 2);
						}
						map[i].SetTrap(x, y, Trap::DARKTUNNEL, dstMapID, xTo, yTo);
					}
					else
					{
						map[i].SetFloor(x, y);
					}
				}
			}
		}
	}
	//printf("Max Depth: %d\n", g_depthMax);

	// Store Map Information In A PGM Image
	//FILE *fout = fopen("image.pgm", "w");
	//fprintf(fout, "P2\n%d %d\n%d\n", NSIZE, NSIZE, g_depthMax + 1);
	//for(int y = 0; y < NSIZE; y++)
	//{
	//	for(int x = 0; x < NSIZE; x++)
	//	{
	//		offset =  x + y*NSIZE;
	//		fprintf(fout, "%d ", caveData[offset].occupied ? caveData[offset].depth : g_depthMax + 1);
	//	}
	//	fprintf(fout, "\n");
	//}
	//fclose(fout);

	// Convert PGM Image to PNG Image
	//system("convert image.pgm image.png; rm image.pgm");
}

void Engine::Update()
{
	int w = 3*DISPLAY_WIDTH/4, h = 3*(DISPLAY_HEIGHT - PANEL_HEIGHT)/4;
	int x = w/2, y = h/2;

	struct InvCategory
	{
		char name[CHARMAX];
		TCODList<int> list;
	} invCategory[NCATEGORIES];
	strcpy(invCategory[CATEGORY_CONSUMABLE].name, "Consumable");
	strcpy(invCategory[CATEGORY_WEARABLE].name, "Wearable");
	strcpy(invCategory[CATEGORY_WIELDABLE].name, "Wieldable");
	strcpy(invCategory[CATEGORY_MISC].name, "Misc");

	for(int i = 0; i < player->container->inventory.size(); i++)
	{
		Object *object = player->container->inventory.get(i);
		if( object->consumable )
		{
			invCategory[CATEGORY_CONSUMABLE].list.push(i);
		}
		else if( object->wearable )
		{
			invCategory[CATEGORY_WEARABLE].list.push(i);
		}
		else if( object->wieldable )
		{
			invCategory[CATEGORY_WIELDABLE].list.push(i);
		}
		else
		{
			invCategory[CATEGORY_MISC].list.push(i);
		}
	}

	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &key, &mouse);

	switch( engineState )
	{
		case ACTIVE:
		{
			// Update all the objects
			for(int i = 0; i < map[mapID].objects.size(); i++)
			{
				Object *object = map[mapID].objects.get(i);
				object->Update();
			}

			// Update the player
			status = player->Update();

			switch( key.vk )
			{
				case TCODK_ESCAPE:
				{
					menuState = static_cast<MenuStates>((menuState + 1) % NMENUSTATES);
					if( menuState == MENU_ACTIVE )
					{
						con->setAlignment(TCOD_LEFT);
						con->setBackgroundFlag(TCOD_BKGND_SET);
						con->setDefaultBackground(TCODColor::black);
						con->setDefaultForeground(TCODColor::white);
						con->clear();
						con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET, "Inventory");

						int u = 2, v = 2, shortcut = 1;
						for(int i = 0; i < NCATEGORIES; i++)
						{
							if( invCategory[i].list.size() > 0 )
							{
								con->setDefaultForeground(TCODColor::white);
								con->print(u, v++, "%c %s Items", TCOD_CHAR_ARROW2_S, invCategory[i].name);
								con->setDefaultForeground(TCODColor::lightGrey);
								for(int j = 0; j < invCategory[i].list.size(); j++)
								{
									int k = invCategory[i].list.get(j);
									Object *object = player->container->inventory.get(k);
									if( object->consumable )
									{
										con->print(u, v++, "%d. %s", shortcut, object->name);
									}
									else if( object->wearable )
									{
										con->print(u, v++, object->wearable->worn ? "%d. %s %c(worn)%c" : "%d. %s", shortcut, object->name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
									}
									else if( object->wieldable )
									{
										con->print(u, v++, object->wieldable->wielded ? "%d. %s %c(wielded)%c" : "%d. %s", shortcut, object->name, TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
									}
									else
									{
										con->print(u, v++, "%d. %s", shortcut, object->name);
									}
									shortcut++;
								}
								v++;
							}
							else
							{
								con->setDefaultForeground(TCODColor::white);
								con->print(u, v++, "%c %s Items", TCOD_CHAR_ARROW2_E, invCategory[i].name);
								con->setDefaultForeground(TCODColor::lightGrey);
								v++;
							}
						}
					}
					else
					{
						con->clear();
					}
					break;
				}
				case TCODK_ENTER:
				{
					for(int i = 0; i < invCategory[CATEGORY_CONSUMABLE].list.size(); i++)
					{
						int k = invCategory[CATEGORY_CONSUMABLE].list.get(i);
						Object *object = player->container->inventory.get(k);
						if( object->consumable && object->consumable->type == ctype )
						{
							gui->MessageLog(TCODColor::lightGrey, "You Consume %s", object->name);

							for(int j = 0; j < object->consumable->conditions->inventory.size(); j++)
							{
								Condition *condition = object->consumable->conditions->inventory.get(j);
								if( condition && condition->first )
								{
									gui->MessageLog(TCODColor::green, "%s", condition->msg_start);
									player->entity->conditions->addToBack(condition);
								}
							}

							player->container->remove(object);
							break;

						}
					}
					break;
				}
				case TCODK_PAUSE:
				{
					engineState = static_cast<EngineStates>((engineState + 1) % (NENGINESTATES - 1));
					break;
				}
				default: break;
			}
			break;
		}
		case INACTIVE:
		{
			static int nframe = 0;
			static bool redflag = false;

			con->setAlignment(TCOD_CENTER);
			con->setBackgroundFlag(TCOD_BKGND_SET);
			con->setDefaultBackground(TCODColor::black);
			con->setDefaultForeground(TCODColor::white);
			con->clear();
			con->printFrame(0, 0, w, h, false, TCOD_BKGND_SET);

			if( nframe == FPSMAX )
			{
				nframe = 0;
				redflag = !redflag;
			}
			else
			{
				nframe++;
			}

			if( redflag )
			{
				con->print(x, y, "%cPaused%c", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
			}
			else
			{
				con->print(x, y, "%cPaused%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
			}

			switch( key.vk )
			{
				case TCODK_PAUSE:
				{
					engineState = static_cast<EngineStates>((engineState + 1) % (NENGINESTATES - 1));
					nframe = 0;
					redflag = false;
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
}

void Engine::Render()
{
	int w = 3*DISPLAY_WIDTH/4, h = 3*(DISPLAY_HEIGHT - PANEL_HEIGHT)/4;
	int x = DISPLAY_WIDTH/2 - w/2, y = (DISPLAY_HEIGHT - PANEL_HEIGHT)/2 - h/2;

	TCODConsole::root->clear();

	// Draw the map
	map[mapID].Render();

	// Draw all the objects
	for(int i = 0; i < map[mapID].objects.size(); i++)
	{
		Object *object = map[mapID].objects.get(i);
		object->Render();
	}

	// Draw the player
	player->Render();

	// Draw the GUI
	gui->Render();

	switch( engineState )
	{
		case ACTIVE:
		{
			if( menuState == MENU_ACTIVE )
			{
				TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 1.0f);
			}
			break;
		}
		case INACTIVE:
		{
			TCODConsole::blit(con, 0, 0, w, h, TCODConsole::root, x, y, 1.0f, 0.85f);
			break;
		}
		default: break;
	}
}
