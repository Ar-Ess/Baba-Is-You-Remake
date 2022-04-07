#ifndef __TILE_H__
#define __TILE_H__

#include "Point.h"
#include "Input.h"
#include "Render.h"
#include <vector>
#include "Defs.h"

class Tile
{
public: // Methods

	Tile(Point position, float size, Render* render, Input* input) 
	{
		this->collider = { position, size, size };
		this->render = render;
		this->input = input;
	}

	virtual ~Tile() {}

	virtual bool Start(Point position, Point offset, float size) { return true; }

	virtual bool Update(float dt, suint* map) { return true; }

	virtual bool Draw(float dt) { return true; }

	virtual bool DebugDraw() { return true; }

	virtual bool CleanUp() { return true; }

	Point GetPosition() const
	{
		return Point{ collider.x, collider.y };
	}

protected: // Variables

	Rect collider = {};
	Point offset = {};
	Render* render = nullptr;
	Input* input = nullptr;

};

#endif // __TILE_H__
