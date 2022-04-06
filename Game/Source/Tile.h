#ifndef __TILE_H__
#define __TILE_H__

#include "Point.h"
#include "Input.h"
#include "Render.h"
#include <vector>

class Tile
{
public: // Methods

	Tile(fPoint position, float size, Render* render, Input* input) 
	{
		this->collider = { position, size, size };
		this->render = render;
		this->input = input;
	}

	virtual ~Tile() {}

	virtual bool Start(iPoint position, fPoint offset, float size) { return true; }

	virtual bool Update(float dt, std::vector<Tile*>* map) { return true; }

	virtual bool Draw(float dt) { return true; }

	virtual bool DebugDraw() { return true; }

	virtual bool CleanUp() { return true; }

	fPoint GetPosition() const
	{
		return fPoint{ collider.x, collider.y };
	}

protected: // Variables

	Rect collider = {};
	fPoint offset = {};
	Render* render = nullptr;
	Input* input = nullptr;

};

#endif // __TILE_H__
