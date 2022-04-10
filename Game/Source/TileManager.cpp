#include "TileManager.h"

TileManager::TileManager(Render* render, Input* input)
{
	this->render = render;
	this->input = input;
}

bool TileManager::Update(float dt)
{
	BehaviorChangeDebug();

	suint size = tiles.size();
	bool change = false;

	for (suint i = 0; i < size; ++i)
	{
		bool tileChange = false;
		tileChange = tiles[i]->Update(dt);
		if (tileChange) change = true;

		if (!change && !tiles[i + 1]->behaviours->Get(PLAYER)) break;
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
		Rect top = { (collider.x * collider.w) + (collider.w / 3) + offset.x, (collider.y * collider.w) + (collider.w / 10) + offset.y, collider.w / 3, collider.h / 7 };
		Rect bottom = { (collider.x * collider.w) + (collider.w / 3) + offset.x, ((collider.y + 1) * collider.w) - (collider.w / 10 * 2) + offset.y, collider.w / 3, collider.h / 7 };
		Rect left = { (collider.x * collider.w) + (collider.w / 10) + offset.x, (collider.y * collider.w) + (collider.w / 3) + offset.y, collider.w / 7, collider.h / 3 };
		Rect right = { ((collider.x + 1) * collider.w) - (collider.w / 10 * 2) + offset.x, (collider.y * collider.w) + (collider.w / 3) + offset.y, collider.w / 7, collider.h / 3 };

		SDL_Color color = {};
		SDL_Color color1 = {255, 150, 0, 100};

		switch (draw->type)
		{
		case PLAYER_TILE: color = { 0, 255, 0, 150 }; break;
		case BLOCK_TILE: color = { 255, 0, 0, 150 }; break;
		case ROCK_TILE: color = { 140, 80, 0, 150 }; break;
		}

		render->DrawRectangle(rect, color);
		if (draw->map.top) render->DrawRectangle(top, {255, 255, 255, 100});
		if (draw->map.bottom) render->DrawRectangle(bottom, { 255, 255, 255, 100 });
		if (draw->map.left) render->DrawRectangle(left, { 255, 255, 255, 100 });
		if (draw->map.right) render->DrawRectangle(right, { 255, 255, 255, 100 });
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

void TileManager::BehaviorChangeDebug()
{
	if (input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		suint size = tiles.size();
		for (suint i = 0; i < size; ++i)
		{
			Tile* tile = tiles[i];
			switch (tile->type)
			{
			case PLAYER_TILE:
				tile->behaviours->Set(PLAYER, false);
				tile->behaviours->Set(PUSH, true);
				break;

			case ROCK_TILE:
				tile->behaviours->Set(PLAYER, true);
				tile->behaviours->Set(PUSH, false);
				tiles.erase(tiles.begin() + i);
				tiles.insert(tiles.begin(), tile);
				break;
			}
		}
	}

	if (input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		suint size = tiles.size();
		for (suint i = 0; i < size; ++i)
		{
			Tile* tile = tiles[i];
			switch (tile->type)
			{
			case PLAYER_TILE:
				tile->behaviours->Set(PLAYER, true);
				tile->behaviours->Set(PUSH, false);
				tiles.erase(tiles.begin() + i);
				tiles.insert(tiles.begin(), tile);
				break;

			case ROCK_TILE:
				tile->behaviours->Set(PLAYER, false);
				tile->behaviours->Set(PUSH, true);
				break;
			}
		}
	}
}
