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

	tileManager->SetTileMaps();
	tileManager->SetOffset(level[lvl]->GetMapOffset());

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
	for (suint i = 0; i < level[lvl]->rows + 1; ++i) // Rows
	{
		render->DrawLine(level[lvl]->center.x + (level[lvl]->offset.x / 2), (level[lvl]->tileSize * i) + level[lvl]->center.y + (level[lvl]->offset.y / 2), (level[lvl]->tileSize * level[lvl]->columns) + level[lvl]->center.x + (level[lvl]->offset.x / 2), (level[lvl]->tileSize * i) + level[lvl]->center.y + (level[lvl]->offset.y / 2));
	}
	for (suint i = 0; i < level[lvl]->columns + 1; ++i) // Columns
	{
		render->DrawLine((level[lvl]->tileSize * i) + level[lvl]->center.x + (level[lvl]->offset.x / 2), level[lvl]->center.y + (level[lvl]->offset.y / 2), (level[lvl]->tileSize * i) + level[lvl]->center.x + (level[lvl]->offset.x / 2), (level[lvl]->tileSize * level[lvl]->rows) + level[lvl]->center.y + (level[lvl]->offset.y / 2));
	}

	return true;
}