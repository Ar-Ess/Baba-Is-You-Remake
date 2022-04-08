#include "LevelScene.h"
#include "Tile.h"

LevelScene::LevelScene(Render* render, Input* input, const Point winSize)
{
	this->render = render;
	this->input = input;
	this->player = player;
	this->winSize = winSize;

	//                        Rows  Columns  WindowSize  PlayerInitPos  Offset
	level[0] = new LevelConfig(14,    26,     winSize,     { 0, 0 },   { 150, 70 });
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

	player = new Tile(PLAYER_TILE, level[lvl]->playerInitPos, level[lvl]->tileSize, level[lvl]->GetMapOffset(), render, input);
	player->SetBehaviour(PLAYER, true);
	tiles.push_back(player);

	for (suint i = 0; i < level[lvl]->rows; ++i)
	{
		tiles.push_back(new Tile(BLOCK_TILE, { -1, i }, level[lvl]->tileSize, level[lvl]->GetMapOffset(), render, input));
		tiles.push_back(new Tile(BLOCK_TILE, { level[lvl]->columns, i }, level[lvl]->tileSize, level[lvl]->GetMapOffset(), render, input));
	}
	for (suint i = 0; i < level[lvl]->columns; ++i)
	{
		tiles.push_back(new Tile(BLOCK_TILE, { i, -1 }, level[lvl]->tileSize, level[lvl]->GetMapOffset(), render, input));
		tiles.push_back(new Tile(BLOCK_TILE, { i, level[lvl]->rows }, level[lvl]->tileSize, level[lvl]->GetMapOffset(), render, input));
	}

	tiles.push_back(new Tile(ROCK_TILE, { 4, 6 }, level[lvl]->tileSize, level[lvl]->GetMapOffset(), render, input));
	tiles.at(tiles.size() - 1)->SetBehaviour(PUSH, true);

	return true;
}

bool LevelScene::Update(float dt)
{
	suint size = tiles.size();
	Multibool map(4);
	for (suint i = 0; i < size; ++i)
	{
		Tile* tile = tiles[i];

		if (tile->GetBehaviour(PLAYER))
		{
			for (suint a = 0; a < size; ++a)
			{
				if (a == i) continue;
				// Check distance and if larger do continue
				Tile* mapTile = tiles[a];

				if (!map.Get(0) && tile->GetPosition().Apply(0, -1) == mapTile->GetPosition()) map.Set(0, true);
				if (!map.Get(1) && tile->GetPosition().Apply(0, 1) == mapTile->GetPosition()) map.Set(1, true);
				if (!map.Get(2) && tile->GetPosition().Apply(-1, 0) == mapTile->GetPosition()) map.Set(2, true);
				if (!map.Get(3) && tile->GetPosition().Apply(1, 0) == mapTile->GetPosition()) map.Set(3, true);
			}
		}

		if (!tiles[i]->Update(dt, map)) break;
		map.SetAllFalse();
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
	suint size = tiles.size();
	for (suint i = 0; i < size; ++i) tiles[i]->CleanUp();
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