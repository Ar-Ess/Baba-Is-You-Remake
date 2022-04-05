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
	tileSize = level[index].GetTileSize(winSize);

	return true;
}

bool LevelScene::Update(float dt)
{
	if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) table.x > 0 ? --table.x : table.x = 0;
	if (input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) ++table.x;
	if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) table.y > 0 ? --table.y : table.y = 0;
	if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) ++table.y;

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

	for (suint i = 0; i < table.x + 1; ++i) // Rows
	{
		render->DrawLine(0, tileSize * i, tileSize * table.y, tileSize * i);
	}

	for (suint i = 0; i < table.y + 1; ++i) // Columns
	{
		render->DrawLine(tileSize * i, 0, tileSize * i, tileSize * table.x);
	}

	return true;
}