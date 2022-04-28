#ifndef __TILE_MANAGER_H__
#define __TILE_MANAGER_H__

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Defs.h"
#include "External/SDL/include/SDL.h"

#include "Point.h"
#include "Multibool.h"
#include "Tile.h"

#include <vector>

class Tile;
enum TileType;
enum Behaviour;
enum TileClass;

class TileManager
{
public: // Methods

	TileManager(Render* render, Input* input, Textures* texture);

	~TileManager() {}

	bool Update(float dt);

	bool Draw(float dt);

	bool DebugDraw();

	bool CleanUp();

	void PushTile(TileType type, Point position, float size, Input* input);

	void PushTile(Tile* push);

	void SetTileMaps();

	void ResetTileMap(Tile* tile);

	void ResetBehaviors(TileType type, Behaviour b, bool set);

	void SetLevelBehaviors();

	void SetOffset(Point offset)
	{
		this->offset = offset;
	}

private: // Methods

	TileClass GetClassFromType(TileType type);

public: // Variables

private: // Variables

	Point offset = {};

	Render* render = nullptr;
	Input* input = nullptr;
	Textures* texture = nullptr;

	std::vector<Tile*> tiles;
	std::vector<SDL_Texture*> textures;

	bool debug = false;

};

#endif // __TILE_H__
