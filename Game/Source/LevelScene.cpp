#include "LevelScene.h"
#include "PlayerTile.h"
#include "BlockTile.h"

LevelScene::LevelScene(Render* render, Input* input, Tile* player, const Point winSize)
{
	this->render = render;
	this->input = input;
	this->player = player;
	this->winSize = winSize;

	//                        Rows  Columns  WindowSize  PlayerInitPos  Offset
	level[0] = new LevelConfig(14,    26,     winSize,     { 0, 0 },   { 100, 70 });
	level[1] = new LevelConfig( 3,     3,     winSize,     { 0, 0 },   { 10, 7 });
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

	player->Start(level[lvl]->playerInitPos, level[lvl]->GetMapOffset(), level[lvl]->tileSize);
	tiles.push_back(player);

	tiles.push_back(new BlockTile(render, input));

	for (suint i = 1; i < tiles.size(); ++i) tiles[i]->Start({-1, 0}, level[lvl]->GetMapOffset(), level[lvl]->tileSize);

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

	suint size = tiles.size();
	for (suint i = 0; i < size; ++i)
	{
		suint* mapPtr = nullptr;

		Multibool mapp(3);
		mapp.Set(1, true);

		bool test0 = mapp.Get(0);
		bool test1 = mapp.Get(1);

		// IN DEVELOPMENT ("if (tiles[i].type == PLAYER) {")
		suint map = 20000; // Do a .h class of this bool method
		for (suint a = 0; a < size; ++a)
		{
			if (a == i) continue;

			Tile* tile = tiles[i];
			Tile* mapTile = tiles[a];

			if ((map - 1000) < 20000 && tile->GetPosition().Apply(0, -1) == mapTile->GetPosition())
			{
				map += 1000;
				if (mapPtr == nullptr) mapPtr = &map;
			}
			if ((map - 1100) < 20000 && tile->GetPosition().Apply(0,  1) == mapTile->GetPosition())
			{
				map += 100;
				if (mapPtr = nullptr) mapPtr = &map;
			}
			if ((map - 1110) < 20000 && tile->GetPosition().Apply(-1, 0) == mapTile->GetPosition())
			{
				map += 10;
				if (mapPtr == nullptr) mapPtr = &map;
			}
			if ((map - 1111) < 20000 && tile->GetPosition().Apply(1,  0) == mapTile->GetPosition())
			{
				map += 1;
				if (mapPtr == nullptr) mapPtr = &map;
			}
		}
		// IN DEVELOPMENT (} "If" depending on the enum type)

		tiles[i]->Update(dt, mapPtr);
	}

	return true;
}

bool LevelScene::Draw(float dt)
{
	DebugDraw();

	for (suint i = 0; i < tiles.size(); ++i) tiles[i]->Draw(dt);

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
	for (suint i = 0; i < level[lvl]->rows + 1; ++i) // Rows
	{
		render->DrawLine(level[lvl]->center.x + (level[lvl]->offset.x / 2), (level[lvl]->tileSize * i) + level[lvl]->center.y + (level[lvl]->offset.y / 2), (level[lvl]->tileSize * level[lvl]->columns) + level[lvl]->center.x + (level[lvl]->offset.x / 2), (level[lvl]->tileSize * i) + level[lvl]->center.y + (level[lvl]->offset.y / 2));
	}
	for (suint i = 0; i < level[lvl]->columns + 1; ++i) // Columns
	{
		render->DrawLine((level[lvl]->tileSize * i) + level[lvl]->center.x + (level[lvl]->offset.x / 2), level[lvl]->center.y + (level[lvl]->offset.y / 2), (level[lvl]->tileSize * i) + level[lvl]->center.x + (level[lvl]->offset.x / 2), (level[lvl]->tileSize * level[lvl]->rows) + level[lvl]->center.y + (level[lvl]->offset.y / 2));
	}

	// Tiles
	for (suint i = 0; i < tiles.size(); ++i) tiles[i]->DebugDraw();

	return true;
}