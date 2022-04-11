#include "TileManager.h"

TileManager::TileManager(Render* render, Input* input, Textures* texture)
{
	this->render = render;
	this->input = input;
	this->texture = texture;

	textures.push_back(texture->Load("Assets/Textures/Tiles/player_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/rock_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/flag_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/wall_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/player_text_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/rock_text_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/flag_text_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/wall_text_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/you_b_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/push_b_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/win_b_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/stop_b_tile.png"));
	textures.push_back(texture->Load("Assets/Textures/Tiles/is_tile.png"));
}

bool TileManager::Update(float dt)
{
	if (input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) debug = !debug;

	suint size = tiles.size();
	bool change = false;

	for (suint i = 0; i < size; ++i)
	{
		bool tileChange = false;
		tileChange = tiles[i]->UpdateBehaviour(dt);
		if (tileChange) change = true;

		if (!change && !tiles[i + 1]->behaviours->Get(PLAYER)) break;
	}

	if (!change) return true;
	
	SetTileMaps();
	for (suint i = 0; i < size; ++i) tiles[i]->UpdateLogic(dt);

	return true;
}

bool TileManager::Draw(float dt)
{

	suint size = tiles.size();
	for (suint i = 0; i < size; ++i)
	{
		Tile* draw = tiles[i];
		if (draw->type == BLOCK_TILE) continue;

		float size = draw->collider.w;

		render->DrawTexture(textures.at((int)draw->type), (draw->collider.x * size) + offset.x, (draw->collider.y * size) + offset.y, size / 100, size / 100);
	}

	return true;
}

bool TileManager::DebugDraw()
{
	if (!debug) return true;

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

		switch (draw->type)
		{
		// Static Tiles
		case BLOCK_TILE: color = { 255, 0, 0, 150 }; break;

		// Object Tiles
		case PLAYER_TILE: color = { 0, 255, 0, 150 }; break;
		case ROCK_TILE: color = { 100, 40, 0, 150 }; break;
		case FLAG_TILE: color = { 200, 200, 50, 150 }; break;

		// Text Tiles
		case PLAYER_TEXT_TILE: color = {180, 180, 255, 150}; break;
		case ROCK_TEXT_TILE: color = { 200, 140, 30, 150 }; break;
		case FLAG_TEXT_TILE: color = { 200, 200, 150, 150 }; break;

		// Behaviour Tiles
		case YOU_B_TILE: color = { 0, 0, 255, 150}; break;
		case PUSH_B_TILE: color = { 0, 255, 255, 150 }; break;
		case WIN_B_TILE: color = { 200, 100, 100, 150 }; break;

		// Linker Tiles
		case IS_TILE: color = { 100, 100, 255, 150 }; break;

		default: color = {255, 255, 255, 255}; break;
		}

		render->DrawRectangle(rect, color);
		if (draw->map.top) render->DrawRectangle(top, {255, 255, 255, 75});
		if (draw->map.bottom) render->DrawRectangle(bottom, { 255, 255, 255, 75 });
		if (draw->map.left) render->DrawRectangle(left, { 255, 255, 255, 75 });
		if (draw->map.right) render->DrawRectangle(right, { 255, 255, 255, 75 });
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
	push->manager = this;
	type == PLAYER_TILE ? tiles.insert(tiles.begin(), push) : tiles.push_back(push);
	if (type == BLOCK_TILE) push->SetBehaviour(STOP, true);
}

void TileManager::PushTile(Tile* push)
{
	push->manager = this;
	this->tiles.push_back(push);
}

void TileManager::SetTileMaps()
{
	suint size = tiles.size();
	for (suint i = 0; i < size; ++i)
	{
		Tile* tile = tiles[i];
		if (tile->type == BLOCK_TILE) continue;
		tile->map.Reset();

		for (suint a = 0; a < size; ++a)
		{
			if (a == i) continue;
			Tile* mapTile = tiles[a];
			if (tile->DistanceTo(mapTile->GetPosition()) > 1.3f) continue;

			if (tile->GetPosition().Apply(0, -1) == mapTile->GetPosition()) tile->map.top = mapTile;
			else if (tile->GetPosition().Apply(0, 1) == mapTile->GetPosition()) tile->map.bottom = mapTile;
			else if (tile->GetPosition().Apply(-1, 0) == mapTile->GetPosition()) tile->map.left = mapTile;
			else if (tile->GetPosition().Apply(1, 0) == mapTile->GetPosition()) tile->map.right = mapTile;
		}
	}
}

void TileManager::ResetTileMap(Tile* tile)
{
	suint size = tiles.size();
	tile->map.Reset();

	for (suint a = 0; a < size; ++a)
	{
		Tile* mapTile = tiles[a];
		if (tile == mapTile) continue;
		if (tile->DistanceTo(mapTile->GetPosition()) >= 2) continue;

		if (tile->GetPosition().Apply(0, -1) == mapTile->GetPosition()) tile->map.top = mapTile;
		if (tile->GetPosition().Apply(0, 1) == mapTile->GetPosition()) tile->map.bottom = mapTile;
		if (tile->GetPosition().Apply(-1, 0) == mapTile->GetPosition()) tile->map.left = mapTile;
		if (tile->GetPosition().Apply(1, 0) == mapTile->GetPosition()) tile->map.right = mapTile;
	}
}

void TileManager::ResetBehaviors(TileType type, Behaviour b, bool set)
{
	suint size = tiles.size();
	for (suint i = 0; i < size; ++i)
	{
		Tile* tile = tiles[i];
		if (tile->type != type) continue;

		tile->behaviours->Set((int)b, set);
	}
}

void TileManager::SetLevelBehaviors()
{
	suint size = tiles.size();
	for (suint i = 0; i < size; ++i)
	{
		Tile* tile = tiles[i];

		switch (tile->type)
		{
		case PLAYER_TEXT_TILE:
			if (!tile->map.right || tile->map.right->type != IS_TILE)
			{
				ResetBehaviors(PLAYER_TILE, PLAYER, false);
				ResetBehaviors(PLAYER_TILE, PUSH, false);
				break;
			}

			switch (tile->map.right->map.right->type) //provably ending up being recursive (if AND TILE implemented)
			{
			case YOU_B_TILE: ResetBehaviors(PLAYER_TILE, PLAYER, true); break;
			case PUSH_B_TILE: ResetBehaviors(PLAYER_TILE, PUSH, true); break;
			}

			break;

		case ROCK_TEXT_TILE:
			if (!tile->map.right || tile->map.right->type != IS_TILE)
			{
				ResetBehaviors(ROCK_TILE, PLAYER, false);
				ResetBehaviors(ROCK_TILE, PUSH, false);
				break;
			}

			switch (tile->map.right->map.right->type) //provably ending up being recursive (if AND TILE implemented)
			{
			case YOU_B_TILE: ResetBehaviors(ROCK_TILE, PLAYER, true); break;
			case PUSH_B_TILE: ResetBehaviors(ROCK_TILE, PUSH, true); break;
			}

			break;
		}
	}
}
