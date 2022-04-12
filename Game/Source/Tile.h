#ifndef __TILE_H__
#define __TILE_H__

#include "TileManager.h"
#include <vector>

enum Direction
{
	NO_DIR = -1,
	RIGHT,
	BOTTOM,
	TOP,
	LEFT
};

enum Behaviour // Remember to modify GetBehaviourFromType in Tile.cpp
{
	NO_BEHAVIOR = -1,
	PLAYER,
	WIN,
	PUSH,
	STOP
};

enum TileType // Remember to modify function "GetClassFromTile" in Tile.cpp
{
	// Static Tiles
	NO_TILE = -2,
	BLOCK_TILE,
	// Object Tiles
	PLAYER_TILE,
	ROCK_TILE,
	FLAG_TILE,
	WALL_TILE,
	// Text Tiles
	PLAYER_TEXT_TILE,
	ROCK_TEXT_TILE,
	FLAG_TEXT_TILE,
	WALL_TEXT_TILE,
	// Behavior Tiles (Remember to modify GetBehaviourFromType in TileManager.cpp)
	YOU_B_TILE,
	WIN_B_TILE,
	PUSH_B_TILE,
	STOP_B_TILE,
	// Linker Tiles
	IS_TILE
};

enum TileClass
{
	NO_CLASS = -1,
	OBJECT,
	TEXT,
	BEHAVIOR,
	LINKER
};

class Tile;

struct Map
{
	Map()
	{
		top = nullptr;
		bottom = nullptr;
		left = nullptr;
		right = nullptr;
	}

	Tile* Get(Direction dir)
	{
		Tile* ret = nullptr;

		switch (dir)
		{
		case TOP: ret = top; break;
		case BOTTOM: ret = bottom; break;
		case LEFT: ret = left; break;
		case RIGHT: ret = right; break;
		}

		return ret;
	}

	void Reset()
	{
		top = nullptr;
		bottom = nullptr;
		left = nullptr;
		right = nullptr;
	}

	Tile* top = nullptr;
	Tile* bottom = nullptr;
	Tile* left = nullptr;
	Tile* right = nullptr;
};

class Tile
{
public: // Methods

	Tile(TileType type, TileClass clas, Point position, float size, Input* input);

	~Tile() {}

	bool Start();

	bool UpdateBehaviour(float dt);

	bool UpdateLogic(float dt);

	bool CleanUp();

	Point GetPosition() const
	{
		return Point{ collider.x, collider.y };
	}

	bool GetBehaviour(Behaviour b) const
	{
		return behaviours->Get((int)b);
	}

	void SetBehaviour(Behaviour b, bool set)
	{
		behaviours->Set((int)b, set);
	}

	// This function returns if this tile can't be entered nor pushed
	bool IsStatic()
	{
		return (!GetBehaviour(PUSH) && GetBehaviour(STOP));
	}

	// This function returns if this tile can be accessed
	bool IsTransparent()
	{
		return (!GetBehaviour(PUSH) && !GetBehaviour(STOP));
	}

	float DistanceTo(Point to)
	{
		Point position = GetPosition();
		return position.Distance(to);
	}

private: // Methods

	friend class TileManager;

	bool IsAccessible(Direction dir);

	void MovementLogic(Direction dir);

	void LookAheadLogic(Direction dir, TileType affected);

	Behaviour GetBehaviorFromType(TileType type);

public: // Variables

	TileType type = NO_TILE;
	TileClass clas = NO_CLASS;
	//                 Top    Bottom    Left     Right
	Map map = Map();

protected: // Variables

	Rect collider = {};
	Input* input = nullptr;

	TileManager* manager = nullptr;

	Multibool* behaviours = nullptr;

	//Provably separate by classes "Tiles" "TextTiles" "BehaviourTiles"
	// This should only be in the "TextTiles"
	TileType prevBehaviourTile[2] = { NO_TILE, NO_TILE };
};

#endif // __TILE_H__
