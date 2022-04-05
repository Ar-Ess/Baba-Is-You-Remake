#include "LevelScene.h"

LevelScene::LevelScene(Render* render, Input* input, const iPoint winSize)
{
	this->render = render;
	this->input = input;
	this->winSize = winSize;
}

LevelScene::~LevelScene()
{
}

bool LevelScene::Start(suint index)
{
	if (NUM_OF_LEVELS <= index)
	{
		LOG("Accessing a non existent level - [ NUM_OF_LEVELS <= index ]");
		return false;
	}

	lvl = index;
	tileSize = level[lvl].GetTileSize(winSize);

	return true;
}

bool LevelScene::Update(float dt)
{
	if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) level[lvl].rows > 0 ? --level[lvl].rows : level[lvl].rows = 0;
	if (input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) ++level[lvl].rows;
	if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) level[lvl].columns > 0 ? --level[lvl].columns : level[lvl].columns = 0;
	if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) ++level[lvl].columns;

	return true;
}

bool LevelScene::Draw(float dt)
{
	DebugDraw();

	return true;
}

bool LevelScene::CleanUp()
{
	return true;
}

// -------------------------------------------

bool LevelScene::DebugDraw()
{
	// Grid
	tileSize = level[lvl].GetTileSize(winSize);

	for (suint i = 0; i < level[lvl].rows + 1; ++i) // Rows
	{
		render->DrawLine(0, tileSize * i, tileSize * level[lvl].columns, tileSize * i);
	}

	for (suint i = 0; i < level[lvl].columns + 1; ++i) // Columns
	{
		render->DrawLine(tileSize * i, 0, tileSize * i, tileSize * level[lvl].rows);
	}

	return true;
}