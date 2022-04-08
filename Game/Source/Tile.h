#ifndef __TILE_H__
#define __TILE_H__

#include "Point.h"
#include "Input.h"
#include "Render.h"
#include "Defs.h"
#include "Multibool.h"
#include "External/SDL/include/SDL.h"

enum TileType
{
	NO_TILE,
	PLAYER_TILE,
	BLOCK_TILE,
	ROCK_TILE
};

enum Behaviour
{
	NO_BEHAVIOR,
	PLAYER = 0,
	WIN,
	PUSH
};

class Tile
{
public: // Methods

	Tile(TileType type, Point position, float size, Point offset, Render* render, Input* input);

	~Tile() {}

	bool Start();

	bool Update(float dt, Multibool map);

	bool Draw(float dt);

	bool DebugDraw();

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

private: // Methods

	bool UpdateBehaviour(Multibool map);

	void SetTexture(SDL_Texture* tex);

public: // Variables

	TileType type = NO_TILE;

protected: // Variables

	Rect collider = {};
	Point offset = {};
	Render* render = nullptr;
	Input* input = nullptr;
	SDL_Texture* texture = nullptr;

	Multibool* behaviours = nullptr;
};

#endif // __TILE_H__
