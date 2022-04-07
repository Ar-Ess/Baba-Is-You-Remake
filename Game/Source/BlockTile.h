#ifndef __BLOCK_TILE_H__
#define __BLOCK_TILE_H__

#include "Point.h"
#include "Tile.h"

class BlockTile : public Tile
{
public: // Methods

	BlockTile(Render* render, Input* input) : Tile({0, 0}, 0, render, input)
	{

	}

	~BlockTile() override {}

	bool Start(Point position, Point offset, float size) override
	{
		this->offset = offset;
		this->collider = { (float)position.x, (float)position.y, size, size };
		return true;
	}

	bool Update(float dt, suint* map) override
	{
		if (map == nullptr || *map == 21111) return true;

		return true;
	}

	bool Draw(float dt) override
	{
		return true;
	}

	bool DebugDraw() override
	{
		Rect rect = { (collider.x * collider.w) + offset.x, (collider.y * collider.w) + offset.y, collider.w, collider.h };
		render->DrawRectangle(rect, { 255, 0, 0, 100 });
		return true;
	}

	bool CleanUp() override
	{
		return true;
	}

private: // Methods

private: // Variables
};

#endif // __TILE_H__

