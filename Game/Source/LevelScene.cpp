#include "LevelScene.h"
#include "Tile.h"
#include <fstream>
#include <sstream>

LevelScene::LevelScene(Render* render, Input* input, Textures* texture, const Point winSize)
{
	this->render = render;
	this->input = input;
	this->player = player;
	this->winSize = winSize;

	tileManager = new TileManager(render, input, texture);
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
			// BLOCK
			if (line[x] == '0')
			{
				tileManager->PushTile(BLOCK_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				++x;
			}
			// Player
			else if (line[x] == 'p' && line[x + 1] == ',')
			{
				tileManager->PushTile(PLAYER_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				++x;
			}
			// Player Text
			else if (line[x] == 'p' && line[x + 1] == 't')
			{
				Tile* tile = new Tile(PLAYER_TEXT_TILE, TEXT, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
				x += 2;
			}
			// Is Text
			else if (line[x] == 'i' && line[x + 1] == 's')
			{
				Tile* tile = new Tile(IS_TILE, LINKER, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
				x += 2;
			}
			// You Text
			else if (line[x] == 'y')
			{
				Tile* tile = new Tile(YOU_B_TILE, BEHAVIOR,{ a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
				++x;
			}
			// Push Behavior
			else if (line[x] == 'p' && line[x + 1] == 's' && line[x + 2] == 'h')
			{
				Tile* tile = new Tile(PUSH_B_TILE, BEHAVIOR, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
				x += 3;
			}
			// Flag
			else if (line[x] == 'f' && line[x + 1] == ',')
			{
				tileManager->PushTile(FLAG_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				++x;
			}
			// Win Behavior
			else if (line[x] == 'w' && line[x + 1] == ',')
			{
				Tile* tile = new Tile(WIN_B_TILE, BEHAVIOR, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
				++x;
			}
			// Flag Text
			else if (line[x] == 'f' && line[x + 1] == 't')
			{
				Tile* tile = new Tile(FLAG_TEXT_TILE, TEXT, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
				x += 2;
			}
			// Stop Behavior
			else if (line[x] == 's' && line[x + 1] == 't' && line[x + 2] == 'p')
			{
				Tile* tile = new Tile(STOP_B_TILE, BEHAVIOR, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
				x += 3;
			}
			// Wall
			else if (line[x] == 'w' && line[x + 1] == 'l' && line[x + 2] == ',')
			{
				tileManager->PushTile(WALL_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
				x += 2;
			}
			// Wall Text
			else if (line[x] == 'w' && line[x + 1] == 'l' && line[x + 2] == 't')
			{
				Tile* tile = new Tile(WALL_TEXT_TILE, TEXT, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
				x += 3;
			}
			// Rock
			else if (line[x] == 'r' && line[x + 1] == ',')
			{
			tileManager->PushTile(ROCK_TILE, { a - 1, i - 1 }, this->level->tileSize, input);
			++x;
			}
			// Rock Text
			else if (line[x] == 'r' && line[x + 1] == 't')
			{
				Tile* tile = new Tile(ROCK_TEXT_TILE, TEXT, { a - 1, i - 1 }, this->level->tileSize, input);
				if (textDefaultPush)
				{
					tile->SetBehaviour(PUSH, true);
					tile->SetBehaviour(STOP, true);
				}
				tileManager->PushTile(tile);
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
