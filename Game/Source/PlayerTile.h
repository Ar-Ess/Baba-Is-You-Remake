#ifndef __PLAYER_TILE_H__
#define __PLAYER_TILE_H__

#include "Tile.h"

#include "Point.h"
#include "Log.h"

#include "SDL/include/SDL.h"

class Animation;

class PlayerTile : public Tile
{
public:

    PlayerTile(fPoint position, float size, Render* render, Input* input);

    bool Start(iPoint position, fPoint offset, float size) override;

    bool Update(float dt, std::vector<Tile*>* map) override;

    bool Draw(float dt) override;

    bool DebugDraw() override;

    void SetTexture(SDL_Texture *tex);

private:

    SDL_Texture* texture = nullptr;

};

#endif // __PLAYER_TILE_H__
