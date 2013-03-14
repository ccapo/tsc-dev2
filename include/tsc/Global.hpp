#ifndef GLOBAL_HPP
#define GLOBAL_HPP
//------------------------------------------------------------------------
//
// Name: Global.hpp
//
// Description: Global constants
//
// Author: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
//
// The Serpentine Caves
// Copyright (c) 2011, 2012 Christopher Claudio Capobianco
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Christopher Claudio Capobianco may not be used to endorse
//       or promote products derived from this software without specific prior
//       written permission.
//
// THIS SOFTWARE IS PROVIDED BY CHRISTOPHER CLAUDIO CAPOBIANCO ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL CHRISTOPHER CLAUDIO CAPOBIANCO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Mingos' Noise Demo 2
// Copyright (c) 2010 Dominik Marczuk
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Dominik Marczuk may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <time.h>
#include <typeinfo>
#include <unistd.h>
#include <vector>
#include "libtcod.hpp"

using namespace std;

// Size of the display
#define DISPLAY_WIDTH 72
#define DISPLAY_HEIGHT 42

#define PANEL_HEIGHT 7
#define BAR_WIDTH 20
#define MSG_X (BAR_WIDTH + 2)
#define MSG_HEIGHT (PANEL_HEIGHT - 1)

#define FPSMAX 25

#define CHARMAX 128

#define PATTERNMAX 256

#define NBLOCK 9
#define NBORDER (NBLOCK - 1)

#define NSIZE 32
#define NMAPS (64 + 1)

#define LEVELMAX 50

#define HPMIN 5
#define HPMAX 750

#define APMIN 0
#define APMAX 50

#define DPMIN 0
#define DPMAX 50

#define STRMIN 0
#define STRMAX 50

#define SPDMIN 0
#define SPDMAX 50

#define MPMIN 1
#define MPMAX 250

#define MAPMIN 0
#define MAPMAX 50

#define MDPMIN 0
#define MDPMAX 50

#define WILMIN 0
#define WILMAX 50

#define ACUMIN 0
#define ACUMAX 50

// List of Tile Character Types
enum CharType
{
	// Default Character Tile
	CHAR_DEFAULT = -1,

	// Stairs
	CHAR_STAIRS_UP = 256,
	CHAR_STAIRS_DOWN,

	CHAR_HOLE,

	// Water Animation
	CHAR_WATER_01,
	CHAR_WATER_02,

	// Lava Animation
	CHAR_LAVA_01,
	CHAR_LAVA_02,

	// Chest
	CHAR_CHEST_OPEN,
	CHAR_CHEST_CLOSED,

	// Potions
	CHAR_POTION_YELLOW,
	CHAR_POTION_RED,
	CHAR_POTION_GREEN,
	CHAR_POTION_BLUE,

	CHAR_KEY,

	// Rings
	CHAR_RING_RED,
	CHAR_RING_GREEN,
	CHAR_RING_BLUE,
	CHAR_RING_RED_BIG,
	CHAR_RING_GREEN_BIG,
	CHAR_RING_BLUE_BIG,

	// Shields
	CHAR_SHIELD_BROWN,
	CHAR_SHIELD_GREY,
	CHAR_SHIELD_GOLD,

	// Swords
	CHAR_SWORD_BASIC,
	CHAR_SWORD_STEEL,
	CHAR_SWORD_GOLD,

	// Armour
	CHAR_ARMOUR_BROWN,
	CHAR_ARMOUR_YELLOW,
	CHAR_ARMOUR_RED,
	CHAR_ARMOUR_GREEN,
	CHAR_ARMOUR_BLUE,
	CHAR_ARMOUR_MITHRIL,

	// Magic Charge Bar
	CHAR_CHARGEBAR,

	// Player Tiles
	CHAR_PLAYER_RIGHT,
	CHAR_PLAYER_DOWN,
	CHAR_PLAYER_LEFT,
	CHAR_PLAYER_UP,

	// NPC Tiles
	CHAR_GUARDIAN,
	CHAR_KEEPER,
	CHAR_PERSON_MALE,
	CHAR_PERSON_FEMALE,

	// Monster Tiles
	CHAR_GUARD,

	CHAR_WARLOCK_PURPLE,

	CHAR_NECROMANCER_APPENTICE,
	CHAR_NECROMANCER_MASTER,

	CHAR_DARKELF_ARCHER,
	CHAR_DARKELF_WARRIOR,
	CHAR_DARKELF_MAGE,

	CHAR_DWARF_WARRIOR,
	CHAR_DWARF_AXEBEARER,
	CHAR_DWARF_MAGE,
	CHAR_DWARF_HERO,

	CHAR_UNDEAD_DWARF_WARRIOR,
	CHAR_UNDEAD_DWARF_AXEBEARER,
	CHAR_UNDEAD_DWARF_MAGE,
	CHAR_UNDEAD_DWARF_HERO,

	CHAR_GOBLIN_PEON,
	CHAR_GOBLIN_WARRIOR,
	CHAR_GOBLIN_MAGE,

	CHAR_IMP_BLUE,
	CHAR_IMP_RED,

	CHAR_ORGE_PEON_GREEN,
	CHAR_ORGE_WARRIOR_GREEN,

	CHAR_ORGE_PEON_RED,
	CHAR_ORGE_WARRIOR_RED,

	CHAR_SKELETON_PEON,
	CHAR_SKELETON_WARRIOR,
	CHAR_SKELETON_HERO,
	CHAR_SKELETON_MAGE,

	CHAR_SPRITE,

	CHAR_ORC_PEON,
	CHAR_ORC_WARRIOR,
	CHAR_ORC_HERO,
	CHAR_ORC_MAGE,

	CHAR_DEMON_PEON,
	CHAR_DEMON_HERO,
	CHAR_DEMON_MAGE,

	CHAR_FLAYER_WARRIOR,
	CHAR_FLAYER_MAGE,

	CHAR_SKULL,

	CHAR_GOLEM_GREY,
	CHAR_GOLEM_BROWN,
	CHAR_GOLEM_RED,

	CHAR_SLIME_BROWN,
	CHAR_SLIME_GREEN,

	CHAR_EYEBALL,

	CHAR_VERMIN_BROWN,

	CHAR_SNAKE_GREEN,

	CHAR_RUBBLE_PILE,

	CHAR_SCORPIAN_YELLOW,
	CHAR_SCORPIAN_BLACK,

	CHAR_SPIDER_BLACK,
	CHAR_SPIDER_RED,
	CHAR_SPIDER_GREEN,

	CHAR_PYTHON_RED,
	CHAR_PYTHON_BROWN,
	CHAR_PYTHON_YELLOW,

	CHAR_BAT_BROWN,
	CHAR_BAT_BLUE,

	// Environment Tiles
	CHAR_TREE_A,
	CHAR_TREE_B,
	CHAR_TREE_C,
	CHAR_TREE_D,
	CHAR_TREE_E,
	CHAR_TREE_F,
	CHAR_TREE_G,

	CHAR_SHRUB_A,
	CHAR_SHRUB_B,
	CHAR_SHRUB_C,
	CHAR_SHRUB_D,
	CHAR_MUSHROOM,
	CHAR_FLOWERS_WHITE,
	CHAR_FLOWERS_BLUE,

	CHAR_TEMPLE,
	CHAR_TOWN,
	CHAR_CAVE,

	CHAR_BED,
	CHAR_TABLE,
	CHAR_BOOKCASE,
	CHAR_CHAIR_RIGHT,
	CHAR_CHAIR_LEFT,

	// Minor Boss Tiles (Upper Portion)
	CHAR_DEMONLORD_WHITE_UL,
	CHAR_DEMONLORD_WHITE_UR,

	CHAR_DEMONLORD_RED_UL,
	CHAR_DEMONLORD_RED_UR,

	CHAR_CYCLOPS_UL,
	CHAR_CYCLOPS_UR,

	CHAR_DRAGON_LARGE_RED_UL,
	CHAR_DRAGON_LARGE_RED_UR,

	CHAR_DRAGON_LARGE_YELLOW_UL,
	CHAR_DRAGON_LARGE_YELLOW_UR,

	CHAR_DRAGON_LARGE_GREEN_UL,
	CHAR_DRAGON_LARGE_GREEN_UR,

	CHAR_DRAGON_LARGE_BLUE_UL,
	CHAR_DRAGON_LARGE_BLUE_UR,

	CHAR_DRAGON_LARGE_GREY_UL,
	CHAR_DRAGON_LARGE_GREY_UR,

	CHAR_MINOTAUR_UL,
	CHAR_MINOTAUR_UR,

	CHAR_LIZARD_GIANT_UL,
	CHAR_LIZARD_GIANT_UR,

	CHAR_MEDUSA_UL,
	CHAR_MEDUSA_UR,

	CHAR_FLYING_BRAIN_UL,
	CHAR_FLYING_BRAIN_UR,

	CHAR_SLIMELORD_UL,
	CHAR_SLIMELORD_UR,

	CHAR_BEHOLDER_UL,
	CHAR_BEHOLDER_UR,

	CHAR_BEHEMOTH_UL,
	CHAR_BEHEMOTH_UR,

	// Final Boss Tiles (Upper Portion)
	CHAR_FINAL_BOSS_UL,
	CHAR_FINAL_BOSS_UR,

	// Minor Boss Tiles (Lower Portion)
	CHAR_DEMONLORD_WHITE_LL,
	CHAR_DEMONLORD_WHITE_LR,

	CHAR_DEMONLORD_RED_LL,
	CHAR_DEMONLORD_RED_LR,

	CHAR_CYCLOPS_LL,
	CHAR_CYCLOPS_LR,

	CHAR_DRAGON_LARGE_RED_LL,
	CHAR_DRAGON_LARGE_RED_LR,

	CHAR_DRAGON_LARGE_YELLOW_LL,
	CHAR_DRAGON_LARGE_YELLOW_LR,

	CHAR_DRAGON_LARGE_GREEN_LL,
	CHAR_DRAGON_LARGE_GREEN_LR,

	CHAR_DRAGON_LARGE_BLUE_LL,
	CHAR_DRAGON_LARGE_BLUE_LR,

	CHAR_DRAGON_LARGE_GREY_LL,
	CHAR_DRAGON_LARGE_GREY_LR,

	CHAR_MINOTAUR_LL,
	CHAR_MINOTAUR_LR,

	CHAR_LIZARD_GIANT_LL,
	CHAR_LIZARD_GIANT_LR,

	CHAR_MEDUSA_LL,
	CHAR_MEDUSA_LR,

	CHAR_FLYING_BRAIN_LL,
	CHAR_FLYING_BRAIN_LR,

	CHAR_SLIMELORD_LL,
	CHAR_SLIMELORD_LR,

	CHAR_BEHOLDER_LL,
	CHAR_BEHOLDER_LR,

	CHAR_BEHEMOTH_LL,
	CHAR_BEHEMOTH_LR,

	// Final Boss Tiles (Lower Portion)
	CHAR_FINAL_BOSS_LL,
	CHAR_FINAL_BOSS_LR
};

// Clamps the first argument between the second two
template <class T>
inline T Clamp(T &arg, const T &minVal, const T &maxVal)
{
	//assert ( ((double)minVal < (double)maxVal) && "<Clamp>MaxVal < MinVal!");

	if( arg < minVal ) arg = minVal;

	if( arg > maxVal ) arg = maxVal;

	return arg;
}

#endif
