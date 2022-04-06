#include "LevelScene.h"
#include "PlayerTile.h"
#include "BlockTile.h"

LevelScene::LevelScene(Render* render, Input* input, Tile* player, const iPoint winSize)
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

	for (suint i = 0; i < tiles.size(); ++i)
	{
		// IN DEVELOPMENT (Put in map the four tiles around player)
		std::vector<Tile*> map;
		bool top = false, left = false, right = false, down = false;
		for (suint a = 0; a < tiles.size(); ++a)
		{
			if (a == i) continue;

			Tile* tile = tiles[i];
			Tile* mapTile = tiles[a];

			if (!left && tile->GetPosition().x - 1 == mapTile->GetPosition().x && tile->GetPosition().y == mapTile->GetPosition().y)
			{
				left = true;
				map.push_back(mapTile);
			}
		}
		// IN DEVELOPMENT

		tiles[i]->Update(dt, &map);
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