#ifndef __TILE_H__
#define __TILE_H__

#include "TileManager.h"
#include <vector>

enum Direction
{
	NO_DIR = -1,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

enum Behaviour
{
	NO_BEHAVIOR = -1,
	PLAYER,
	WIN,
	PUSH,
	STOP
};

enum TileType
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
	// Behavior Tiles
	YOU_B_TILE,
	PUSH_B_TILE,
	WIN_B_TILE,
	STOP_B_TILE,
	// Linker Tiles
	IS_TILE
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

	Tile(TileType type, Point position, float size, Input* input);

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

	bool IsStatic()
	{
		return (!GetBehaviour(PUSH) || GetBehaviour(STOP));
	}

	float DistanceTo(Point to)
	{
		Point position = GetPosition();
		return position.Distance(to);
	}

private: // Methods

	friend class TileManager;

	void SetTexture(SDL_Texture* tex);

	bool IsAccessible(Direction dir);

	void MovementLogic(Direction dir);

public: // Variables

	TileType type = NO_TILE;
	//                 Top    Bottom    Left     Right
	Map map = Map();

protected: // Variables

	Rect collider = {};
	Input* input = nullptr;
	SDL_Texture* texture = nullptr;

	TileManager* manager = nullptr;

	Multibool* behaviours = nullptr;

	//Provably separate by classes "Tiles" "TextTiles" "BehaviourTiles"
	// This should only be in the "TextTiles"
	TileType* prevBehaviourTile[2] = { nullptr, nullptr };
};

#endif // __TILE_H__
