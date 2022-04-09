#ifndef __TILE_MANAGER_H__
#define __TILE_MANAGER_H__

#include "Input.h"
#include "Render.h"
#include "Defs.h"
#include "External/SDL/include/SDL.h"

#include "Point.h"
#include "Multibool.h"
#include "Tile.h"

#include <vector>

class Tile;
enum TileType;

class TileManager
{
public: // Methods

	TileManager(Render* render, Input* input);

	~TileManager() {}

	bool Update(float dt);

	bool Draw(float dt);

	bool DebugDraw();

	bool CleanUp();

	void PushTile(TileType type, Point position, float size, Input* input);

	void PushTile(Tile* push);

	void SetTileMaps();

	void SetOffset(Point offset)
	{
		this->offset = offset;
	}

private: // Methods

public: // Variables

private: // Variables

	Point offset = {};

	Render* render = nullptr;
	Input* input = nullptr;

	std::vector<Tile*> tiles;

};

#endif // __TILE_H__
