#include "LevelScene.h"
#include "Tile.h"
#include <fstream>
#include <sstream>

LevelScene::LevelScene(Render* render, Input* input, const Point winSize)
{
	this->render = render;
	this->input = input;
	this->player = player;
	this->winSize = winSize;

	tileManager = new TileManager(render, input);
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

	if (!BuildLevel(index)) return false;
	/*
	lvl = index;

	player = new Tile(PLAYER_TILE, level[lvl]->playerInitPos, level[lvl]->tileSize, input);
	player->SetBehaviour(PLAYER, true);
	tileManager->PushTile(player);

	// Level construction (at the end, this will be done with an excel)
	for (suint i = 0; i < level[lvl]->rows; ++i)
	{
		tileManager->PushTile(BLOCK_TILE, { -1, i }, level[lvl]->tileSize, input);
		tileManager->PushTile(BLOCK_TILE, { level[lvl]->columns, i }, level[lvl]->tileSize, input);
	}
	for (suint i = 0; i < level[lvl]->columns; ++i)
	{
		tileManager->PushTile(BLOCK_TILE, { i, -1 }, level[lvl]->tileSize, input);
		tileManager->PushTile(BLOCK_TILE, { i, level[lvl]->rows }, level[lvl]->tileSize, input);
	}

	Tile* rock = new Tile(ROCK_TILE, { 7, 11 }, level[lvl]->tileSize, input);
	tileManager->PushTile(rock);

	Tile* playerText = new Tile(PLAYER_TEXT_TILE, { 4, 5 }, level[lvl]->tileSize, input);
	playerText->SetBehaviour(PUSH, true);
	tileManager->PushTile(playerText);

	Tile* isText = new Tile(IS_TILE, { 5, 5 }, level[lvl]->tileSize, input);
	isText->SetBehaviour(PUSH, true);
	tileManager->PushTile(isText);

	Tile* youText = new Tile(YOU_TILE, { 6, 5 }, level[lvl]->tileSize, input);
	youText->SetBehaviour(PUSH, true);
	tileManager->PushTile(youText);

	Tile* rockText = new Tile(ROCK_TEXT_TILE, { 10, 4 }, level[lvl]->tileSize, input);
	rockText->SetBehaviour(PUSH, true);
	tileManager->PushTile(rockText);

	Tile* isText1 = new Tile(IS_TILE, { 11, 5 }, level[lvl]->tileSize, input);
	isText1->SetBehaviour(PUSH, true);
	tileManager->PushTile(isText1);

	Tile* pushText = new Tile(PUSH_TILE, { 12, 5 }, level[lvl]->tileSize, input);
	pushText->SetBehaviour(PUSH, true);
	tileManager->PushTile(pushText);
	// Level construction (at the end, this will be done with an excel)

	*/

	tileManager->SetTileMaps();
	tileManager->SetOffset(level->GetMapOffset());
	tileManager->SetLevelBehaviors();

	return true;
}

bool LevelScene::Update(float dt)
{
	tileManager->Update(dt);

	return true;
}

bool LevelScene::Draw(float dt)
{
	this->DebugDraw();
	tileManager->DebugDraw();

	tileManager->Draw(dt);

	return true;
}

bool LevelScene::CleanUp()
{
	tileManager->CleanUp();
	return true;
}

// -------------------------------------------

bool LevelScene::DebugDraw()
{
	// Grid
	for (suint i = 0; i < level->rows + 1; ++i) // Rows
	{
		render->DrawLine(level->center.x + (level->offset.x / 2), (level->tileSize * i) + level->center.y + (level->offset.y / 2), (level->tileSize * level->columns) + level->center.x + (level->offset.x / 2), (level->tileSize * i) + level->center.y + (level->offset.y / 2));
	}
	for (suint i = 0; i < level->columns + 1; ++i) // Columns
	{
		render->DrawLine((level->tileSize * i) + level->center.x + (level->offset.x / 2), level->center.y + (level->offset.y / 2), (level->tileSize * i) + level->center.x + (level->offset.x / 2), (level->tileSize * level->rows) + level->center.y + (level->offset.y / 2));
	}

	return true;
}

bool LevelScene::BuildLevel(suint level)
{
	std::string fileName = "Assets/Levels/level";
	fileName += std::to_string(level + 1);
	fileName += ".csv";
	std::ifstream levelFile(fileName);

	if (!levelFile.is_open()) return false;

	suint rows = 0, columns = 0, offsetx = 0, offsety = 0, textDefaultPush = 0;
	char dummy;
	std::string line;

	levelFile >> rows;
	levelFile >> dummy;
	levelFile >> columns;
	levelFile >> dummy;
	levelFile >> textDefaultPush;
	levelFile >> dummy;
	levelFile >> offsetx;
	levelFile >> dummy;
	levelFile >> offsety;

	std::getline(levelFile, line);
	line.shrink_to_fit();
	line.clear();

	this->level = new LevelConfig(rows - 2, columns - 2, winSize, Point{ offsetx, offsety });

	for (suint i = 0; i < rows; ++i) 
	{
		std::getline(levelFile, line);
		suint x = 0;
		for (suint a = 0; a < columns; ++a)
		{
			if (line[x] == '0')
			{
				tileManager->PushTile(BLOCK_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				++x;
			}
			else if (line[x] == 'p' && line[x + 1] == ',')
			{
				tileManager->PushTile(PLAYER_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				++x;
			}
			else if (line[x] == 'p' && line[x + 1] == 't')
			{
				Tile* tile = new Tile(PLAYER_TEXT_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush) tile->SetBehaviour(PUSH, true);
				tileManager->PushTile(tile);
				x += 2;
			}
			else if (line[x] == 'i' && line[x + 1] == 's')
			{
				Tile* tile = new Tile(IS_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush) tile->SetBehaviour(PUSH, true);
				tileManager->PushTile(tile);
				x += 2;
			}
			else if (line[x] == 'y')
			{
				Tile* tile = new Tile(YOU_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush) tile->SetBehaviour(PUSH, true);
				tileManager->PushTile(tile);
				++x;
			}
			else if (line[x] == 'f' && line[x + 1] == ',')
			{
				//tileManager->PushTile(FLAG_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				++x;
			}
			else if (line[x] == 'w')
			{
				/*Tile* tile = new Tile(WIN_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush) tile->SetBehaviour(PUSH, true);
				tileManager->PushTile(tile);*/
				++x;
			}
			else if (line[x] == 'f' && line[x + 1] == 't')
			{
				/*Tile* tile = new Tile(FLAG_TEXT_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush) tile->SetBehaviour(PUSH, true);
				tileManager->PushTile(tile);*/
				x += 2;
			}
			++x;
		}

		line.shrink_to_fit();
		line.clear();
	}

	levelFile.close();

	return true;
}
