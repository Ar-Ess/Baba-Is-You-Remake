#include "TileManager.h"

TileManager::TileManager(Render* render, Input* input)
{
	this->render = render;
	this->input = input;
}

bool TileManager::Update(float dt)
{
	suint size = tiles.size();
	bool change = false;
	for (suint i = 0; i < size; ++i)
	{
		change = tiles[i]->Update(dt);
		if (!change) break;
	}

	if (change) SetTileMaps();

	return true;
}

bool TileManager::Draw(float dt)
{
	return true;

	suint size = tiles.size();
	for (suint i = 0; i < size; ++i)
	{
		Tile* draw = tiles[i];
		Point position = draw->GetPosition();

		SDL_Texture* texture = nullptr;

		switch (draw->type)
		{
		case PLAYER_TILE: texture = nullptr; break;
		case BLOCK_TILE: texture = nullptr; break;
		case ROCK_TILE: texture = nullptr; break;
		}

		render->DrawTexture(texture, position.x, position.y, 1, 1);
	}

	return true;
}

bool TileManager::DebugDraw()
{
	suint size = tiles.size();
	for (suint i = 0; i < size; ++i)
	{
		Tile* draw = tiles[i];
		Rect collider = draw->collider;

		Rect rect = { (collider.x * collider.w) + offset.x, (collider.y * collider.w) + offset.y, collider.w, collider.h };

		SDL_Color color = {};
		SDL_Color color1 = {255, 150, 0, 100};

		switch (draw->type)
		{
		case PLAYER_TILE: color = { 0, 255, 0, 150 }; break;
		case BLOCK_TILE: color = { 255, 0, 0, 150 }; break;
		case ROCK_TILE: color = { 140, 80, 0, 150 }; break;
		}

		if (draw->map.top || draw->map.bottom || draw->map.left || draw->map.right) color.b = 200;

		render->DrawRectangle(rect, color);
	}

	return true;
}

bool TileManager::CleanUp()
{
	suint size = tiles.size();
	for (suint i = 0; i < size; ++i) tiles[i]->CleanUp();
	return true;
}

void TileManager::PushTile(TileType type, Point position, float size, Input* input)
{
	Tile* push = new Tile(type, position, size, input);
	push->tiles = &tiles;
	this->tiles.push_back(push);
	if (type == BLOCK_TILE) push->SetBehaviour(STOP, true);
}

void TileManager::PushTile(Tile* push)
{
	push->tiles = &tiles;
	this->tiles.push_back(push);
}

void TileManager::SetTileMaps()
{
	suint size = tiles.size();
	for (suint i = 0; i < size; ++i)
	{
		Tile* tile = tiles[i];
		tile->map.Reset();

		for (suint a = 0; a < size; ++a)
		{
			if (a == i) continue;
			Tile* mapTile = tiles[a];
			if (tile->DistanceTo(mapTile->GetPosition()) >= 2) continue;

			if (tile->GetPosition().Apply(0, -1) == mapTile->GetPosition()) tile->map.top = mapTile;
			if (tile->GetPosition().Apply(0, 1) == mapTile->GetPosition()) tile->map.bottom = mapTile;
			if (tile->GetPosition().Apply(-1, 0) == mapTile->GetPosition()) tile->map.left = mapTile;
			if (tile->GetPosition().Apply(1, 0) == mapTile->GetPosition()) tile->map.right = mapTile;
		}
	}
}
