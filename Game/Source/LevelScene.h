#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "Point.h"
#include "Render.h"
#include "Input.h"
#include "Scene.h"
#include <vector>

#define NUM_OF_LEVELS 2

struct SDL_Texture;

struct LevelConfig
{
	LevelConfig(suint rows, suint columns, iPoint offset)
	{
		this->rows = rows;
		this->columns = columns;
		this->offset = offset;
	}

	~LevelConfig() {}

	// Function: Algorithm that returns the value of a tile width & height given window width & height.
	float GetTileSize(iPoint winSize)
	{
		float ret = 0;

		columns == 0 ? ret = 0 : ret = winSize.x / columns;
		rows == 0 ? ret = ret : ret > (winSize.y / rows) ? ret = winSize.y / rows : ret = ret;

		return ret;
	}

	// Function: Algorithm that returns half of the distance between the grid end (right) and the window end (right).
	// This parameter helps to center the grid to avoid having it aligned to de left.
	fPoint GetCenterParam(float tileSize, iPoint windowLvl)
	{
		return fPoint{ ((tileSize * columns) - windowLvl.x) / -2, ((tileSize * rows) - windowLvl.y) / -2 };
	}

	suint rows = 0;
	suint columns = 0;

	iPoint offset = {0, 0};
};

class LevelScene
{
public: // Methods

	LevelScene(Render* render, Input* input, const iPoint winSize);

	~LevelScene();

	bool Start(suint index);

	bool Update(float dt);

	bool Draw(float dt);

	bool CleanUp();

private: // Methods

	bool DebugDraw();

private: // Variables

	Render* render = nullptr;
	Input* input = nullptr;

	iPoint winSize = { 0, 0 };
	fPoint center = { 0, 0 };

	float tileSize = 0;
	suint lvl = 0;

	LevelConfig level[NUM_OF_LEVELS] = {
	// Rows  Columns  Offset
	{   2,     2,    {30, 20} }, 
	{   3,     3,    {50, 40} }
	};

};

#endif // __LEVEL_SCENE_H__