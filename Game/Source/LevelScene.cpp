#include "LevelScene.h"

LevelScene::LevelScene(Render* render, Input* input, Player* player, const iPoint winSize)
{
	this->render = render;
	this->input = input;
	this->player = player;
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

	iPoint windowLvl = winSize;
	windowLvl -= level[lvl].offset;
	tileSize = level[lvl].GetTileSize(windowLvl);
	center = level[lvl].GetCenterParam(tileSize, windowLvl);

	player->Start(level[lvl].GetPlayerInitialPosition(center), tileSize);

	return true;
}

bool LevelScene::Update(float dt)
{
	/*
	if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) level[lvl].rows > 0 ? --level[lvl].rows : level[lvl].rows = 0;
	if (input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) ++level[lvl].rows;
	if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) level[lvl].columns > 0 ? --level[lvl].columns : level[lvl].columns = 0;
	if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) ++level[lvl].columns;
	*/

	player->Update(dt);

	return true;
}

bool LevelScene::Draw(float dt)
{
	DebugDraw();

	player->DebugDraw();
	player->Draw(dt);

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
	for (suint i = 0; i < level[lvl].rows + 1; ++i) // Rows
	{
		render->DrawLine(center.x + (level[lvl].offset.x / 2), (tileSize * i) + center.y + (level[lvl].offset.y / 2), (tileSize * level[lvl].columns) + center.x + (level[lvl].offset.x / 2), (tileSize * i) + center.y + (level[lvl].offset.y / 2));
	}
	for (suint i = 0; i < level[lvl].columns + 1; ++i) // Columns
	{
		render->DrawLine((tileSize * i) + center.x + (level[lvl].offset.x / 2), center.y + (level[lvl].offset.y / 2), (tileSize * i) + center.x + (level[lvl].offset.x / 2), (tileSize * level[lvl].rows) + center.y + (level[lvl].offset.y / 2));
	}

	//Player
	player->DebugDraw();

	return true;
}