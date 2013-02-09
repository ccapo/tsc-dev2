#ifndef STATS_HPP
#define STATS_HPP

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
// Copyright (c) 2009 J.C.Wilk
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of J.C.Wilk may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY J.C.WILK ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL J.C.WILK BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "Global.hpp"

// The class that holds information about player/creature and equipment stats
class Stats
{
	public:
	int hpmax;								// Max. Health Points
	int ap, dp;								// Physical Attack and Defense Power
	int str, spd;							// Strength and Speed
	int mpmax;								// Max. Magic Points
	int map, mdp;							// Magic Attack and Defense Power
	int wil, acu;							// Willpower and Acuity

	Stats(): hpmax(HPMIN), ap(APMIN), dp(DPMIN), str(STRMIN), spd((SPDMAX - SPDMIN)/2), mpmax(MPMIN), map(MAPMIN), mdp(MDPMIN), wil(WILMIN), acu(ACUMIN) {}
	Stats(int hpmax, int ap, int dp, int str, int spd, int mpmax, int map, int mdp, int wil, int acu): hpmax(hpmax), ap(ap), dp(dp), str(str), spd(spd), mpmax(mpmax), map(map), mdp(mdp), wil(wil), acu(acu) {}
	Stats &operator= (const Stats &rhs);	// The Assignment Operator
	Stats &operator+= (const Stats &rhs);	// The Compound Assignment Operator
	Stats &operator-= (const Stats &rhs);	// The Compound Assignment Operator
};

// The class that holds information about player/creature health status
class Health
{
	public:
	int hp;									// Current Health Points
	int mp;									// Current Magic Points
	int xp, xpnext;							// Current Experience Points, Experience Points For Next Level

	Health(int hp, int mp, int xpnext): hp(hp), mp(mp), xp(xpnext > 0 ? 0 : -xpnext), xpnext(xpnext > 0 ? xpnext : -xpnext) {}
	Health &operator= (const Health &rhs);	// The Assignment Operator
	Health &operator+= (const Health &rhs);	// The Compound Assignment Operator
	Health &operator-= (const Health &rhs);	// The Compound Assignment Operator
};

#endif
