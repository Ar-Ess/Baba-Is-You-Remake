#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "Point.h"
#include "Render.h"
#include "Input.h"
#include "Scene.h"
#include <vector>

struct SDL_Texture;

struct LevelConfig
{
	LevelConfig(suint rows, suint columns)
	{
		this->rows = rows;
		this->columns = columns;
	}

	~LevelConfig() {}

	float GetTileSize(iPoint winSize)
	{
		float ret = 0;

		columns == 0 ? ret = 0 : ret = winSize.x / columns;
		rows == 0 ? ret = ret : ret > (winSize.y / rows) ? ret = winSize.y / rows : ret = ret;

		return ret;
	}

	suint rows = 0;
	suint columns = 0;
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

	iPoint winSize = {0, 0};
	iPoint table = {0, 0};

	float tileSize = 0;

	std::vector<LevelConfig> level;

};

#endif // __LEVEL_SCENE_H__
