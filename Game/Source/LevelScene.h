#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "Point.h"
#include "Render.h"
#include "Input.h"
#include "Textures.h"
#include "Scene.h"
#include "Tile.h"
#include "Multibool.h"
#include <vector>
#include "Defs.h"

struct LevelConfig
{
	LevelConfig(suint rows, suint columns, Point winSize, Point offset = { 50, 40 })
	{
		this->rows = rows;
		this->columns = columns;
		this->offset = offset;
		
		winSize -= offset;
		tileSize = GenerateTileSize(winSize);
		center = GenerateCenterParam(winSize);
	}

	~LevelConfig() {}

	Point GetMapOffset()
	{
		return Point{ (offset.x / 2) + center.x, (offset.y / 2) + center.y };
	}

	suint rows = 0;
	suint columns = 0;
	Point offset = {0, 0};
	Point center = {0, 0};
	float tileSize = 0;

private: // Methods

	// Function: Algorithm that returns the value of a tile width & height given window width & height.
	float GenerateTileSize(Point winSize)
	{
		float ret = 0;

		columns == 0 ? ret = 0 : ret = winSize.x / columns;
		rows == 0 ? ret = ret : ret > (winSize.y / rows) ? ret = winSize.y / rows : ret = ret;

		return ret;
	}

	// Function: Algorithm that returns half of the distance between the grid end (right) and the window end (right).
	// This parameter helps to center the grid to avoid having it aligned to de left.
	Point GenerateCenterParam(Point windowLvl)
	{
		return Point{ ((tileSize * columns) - windowLvl.x) / -2, ((tileSize * rows) - windowLvl.y) / -2 };
	}
};

class LevelScene
{
public: // Methods

	LevelScene(Render* render, Input* input, Textures* texture, const Point winSize, suint level);

	~LevelScene();

	bool Start();

	bool Update(float dt);

	bool Draw(float dt);

	bool CleanUp();

private: // Methods

	bool DebugDraw();

	bool BuildLevel(suint level);

private: // Variables

	Render* render = nullptr;
	Input* input = nullptr;
	Tile* player = nullptr;

	Point winSize = { 0, 0 };
	suint lvl = 0;

	LevelConfig* level = nullptr;

	TileManager* tileManager = nullptr;

};

#endif // __LEVEL_SCENE_H__