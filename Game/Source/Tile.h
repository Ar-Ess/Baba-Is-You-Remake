#ifndef __TILE_H__
#define __TILE_H__

#include "TileManager.h"
#include <vector>

enum Behaviour
{
	NO_BEHAVIOR,
	PLAYER = 0,
	WIN,
	PUSH,
	STOP
};

enum Direction
{
	NO_DIR = -1,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

enum TileType
{
	NO_TILE,
	PLAYER_TILE,
	BLOCK_TILE,
	ROCK_TILE,
	PLAYER_TEXT_TILE,
	ROCK_TEXT_TILE,
	IS_TILE,
	YOU_TILE,
	PUSH_TILE,
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

	bool Update(float dt);

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

	bool UpdateBehaviour();

	bool UpdateLogic();

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
};

#endif // __TILE_H__
