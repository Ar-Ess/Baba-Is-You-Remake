#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "App.h"
#include "Entity.h"

#include "Point.h"
#include "Rect.h"
#include "Log.h"

#include "SDL/include/SDL.h"

class Animation;

class Player : public Entity
{
public:

    Player(Render* render, Input* input);

    bool Start(fPoint position, float size);

    bool Update(float dt);

    bool Draw(float dt);

    bool DebugDraw();

    void SetTexture(SDL_Texture *tex);

private:

    SDL_Texture* texture = nullptr;
    Rect collider = {};

};

#endif // __PLAYER_H__
