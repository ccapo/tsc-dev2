#ifndef AI_HPP
#define AI_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Map.hpp"

class AI
{
	public:
	enum AIType
	{
		ORC,
		GOBLIN,
		WARG,
		TROLL,
		DEMON,
		NAITYPES
	};
	AI(){}
	virtual ~AI(){}
	virtual bool Update(Object *owner) = 0;
};

class PlayerAI: public AI
{
	public:
	PlayerAI();
	~PlayerAI();
	bool Update(Object *owner);

	protected:
	void UpdateConfused(Object *owner, int &dx, int &dy);
};

class CreatureAI: public AI
{
	public:
	CreatureAI();
	~CreatureAI();
	bool Update(Object *owner);

	protected:
	void RandomWalk(Object *owner);
	void ChaseOrAttack(Object *owner, int targetx, int targety);
};

class BossAI: public AI
{
	public:
	enum MovementType
	{
		DONT_MOVE,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP_LEFT,
		MOVE_UP_RIGHT,
		MOVE_DOWN_LEFT,
		MOVE_DOWN_RIGHT,
		CIRCLE_CLOCKWISE,
		CIRCLE_COUNTERCLOCKWISE,
		ZIGZAG_LEFT,
		ZIGZAG_RIGHT,
		ZIGZAG_UP,
		ZIGZAG_DOWN,
		SPIRAL_OUT,
		NMOVEMENTTYPES
	};
	enum PatternType
	{
		BOSS_PATTERN_01,
		BOSS_PATTERN_02,
		BOSS_PATTERN_03,
		BOSS_PATTERN_04,
		BOSS_PATTERN_05,
		NPATTERNTYPES
	};
	TCODList<int> patternList;
	map<int, PointType> patternData[PATTERNMAX];

	BossAI();
	BossAI(int type);
	~BossAI();
	bool Update(Object *owner);

	protected:
	void RandomWalk(Object *owner);
	void WalkPattern(Object *owner);
	void LinearPattern(Object *owner, int &x, int &y);
	void ListPattern(Object *owner, int &x, int &y);
	void ChaseOrAttack(Object *owner, int targetx, int targety);

	// Pattern Collections
	void PatternCollections(int type)
	{
		if( patternList.size() > 0 )
		{
			patternList.clear();
			for(int i = 0; i < PATTERNMAX; i++) patternData[i].clear();
		}

		switch( type )
		{
			case BOSS_PATTERN_01:
			{
				// Dumbbell Pattern
				patternList.push(MOVE_LEFT);
				patternList.push(CIRCLE_COUNTERCLOCKWISE);
				patternList.push(MOVE_RIGHT);
				patternList.push(CIRCLE_CLOCKWISE);

				//patternList.push(DONT_MOVE);
				//patternList.push(DONT_MOVE);
				break;
			}
			case BOSS_PATTERN_02:
			{
				// Zig-Zag Dumbbell Pattern
				patternList.push(ZIGZAG_LEFT);
				patternList.push(CIRCLE_COUNTERCLOCKWISE);
				patternList.push(ZIGZAG_RIGHT);
				patternList.push(CIRCLE_CLOCKWISE);

				//patternList.push(DONT_MOVE);
				//patternList.push(DONT_MOVE);
				break;
			}
			case BOSS_PATTERN_03:
			{
				// Square Coverleaf Pattern
				patternList.push(MOVE_UP);
				patternList.push(MOVE_RIGHT);
				patternList.push(MOVE_DOWN);
				patternList.push(MOVE_LEFT);

				patternList.push(MOVE_LEFT);
				patternList.push(MOVE_UP);
				patternList.push(MOVE_RIGHT);
				patternList.push(MOVE_DOWN);

				patternList.push(MOVE_DOWN);
				patternList.push(MOVE_LEFT);
				patternList.push(MOVE_UP);
				patternList.push(MOVE_RIGHT);

				patternList.push(MOVE_RIGHT);
				patternList.push(MOVE_DOWN);
				patternList.push(MOVE_LEFT);
				patternList.push(MOVE_UP);

				//patternList.push(DONT_MOVE);
				//patternList.push(DONT_MOVE);
				break;
			}
			case BOSS_PATTERN_04:
			{
				// Spiral Zig-Zag Pattern
				patternList.push(SPIRAL_OUT);
				patternList.push(MOVE_UP_LEFT);
				patternList.push(MOVE_UP_LEFT);
				patternList.push(ZIGZAG_DOWN);

				//patternList.push(DONT_MOVE);
				//patternList.push(DONT_MOVE);
				break;
			}
			default:
			{
				// Simple Pattern
				patternList.push(MOVE_LEFT);
				patternList.push(MOVE_RIGHT);

				//patternList.push(DONT_MOVE);
				//patternList.push(DONT_MOVE);
				break;
			}
		}

		for(int i = 0; i < patternList.size(); i++) MovementPatterns(i, patternList.get(i));
	}

	// Movement Patterns
	void MovementPatterns(int index, int type)
	{
		int i = 0;
		switch( type )
		{
			case DONT_MOVE:
			{	// Move Left										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+0, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +0, +0)));
				break;
			}
			case MOVE_UP:
			{	// Move Up											x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+0, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, -2, +0)));
				break;
			}
			case MOVE_DOWN:
			{	// Move Down										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+0, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +2, +0)));
				break;
			}
			case MOVE_LEFT:
			{	// Move Left										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(-2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +0, +0)));
				break;
			}
			case MOVE_RIGHT:
			{	// Move Right										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));
				break;
			}
			case MOVE_UP_LEFT:
			{	// Move Up Left										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				break;
			}
			case MOVE_UP_RIGHT:
			{	// Move Up Right									x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				break;
			}
			case MOVE_DOWN_LEFT:
			{	// Move Down Left									x, y, spd
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				break;
			}
			case MOVE_DOWN_RIGHT:
			{	// Move Down Right									x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				break;
			}
			case CIRCLE_CLOCKWISE:
			{	// Circle Clockwise									x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +2, +25)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, -2, -25)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				break;
			}
			case CIRCLE_COUNTERCLOCKWISE:
			{	// Circle Counter-Clockwise							x, y, spd
				patternData[index].insert(make_pair(i++, PointType(-2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +2, +25)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, -2, -25)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				break;
			}
			case ZIGZAG_LEFT:
			{	// Zig-Zag Left										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				break;
			}
			case ZIGZAG_RIGHT:
			{	// Zig-Zag Right									x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				break;
			}
			case ZIGZAG_UP:
			{	// Zig-Zag Up										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				break;
			}
			case ZIGZAG_DOWN:
			{	// Zig-Zag Down										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));
				break;
			}
			case SPIRAL_OUT:
			{	// Spiral Out										x, y, spd
				patternData[index].insert(make_pair(i++, PointType(-1, +0, +0)));

				patternData[index].insert(make_pair(i++, PointType(+0, -1, +0)));

				patternData[index].insert(make_pair(i++, PointType(+1, -1, +0)));

				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));

				patternData[index].insert(make_pair(i++, PointType(+1, +1, +0)));

				patternData[index].insert(make_pair(i++, PointType(+0, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +1, +0)));

				patternData[index].insert(make_pair(i++, PointType(-2, +2, +0)));

				patternData[index].insert(make_pair(i++, PointType(-2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(-1, +0, +0)));

				patternData[index].insert(make_pair(i++, PointType(-2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(-1, -1, +0)));

				patternData[index].insert(make_pair(i++, PointType(+0, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, -2, +0)));

				patternData[index].insert(make_pair(i++, PointType(+2, -2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+1, -1, +0)));

				patternData[index].insert(make_pair(i++, PointType(+2, +0, +25)));
				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +0, +0)));

				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+2, +2, +0)));

				patternData[index].insert(make_pair(i++, PointType(+0, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +2, +0)));
				patternData[index].insert(make_pair(i++, PointType(+0, +2, +0)));

				patternData[index].insert(make_pair(i++, PointType(-2, +1, +0)));
				patternData[index].insert(make_pair(i++, PointType(-2, +1, +0)));

				patternData[index].insert(make_pair(i++, PointType(-2, +0, -25)));
				patternData[index].insert(make_pair(i++, PointType(-2, +0, +0)));
				break;
			}
			default: break;
		}
	}
};

class NpcAI: public AI
{
	public:
	NpcAI();
	~NpcAI();
	bool Update(Object *owner);

	protected:
	void MoveToTarget(Object *owner, int targetx, int targety);
};

#endif
