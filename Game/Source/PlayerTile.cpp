#include "PlayerTile.h"

PlayerTile::PlayerTile(fPoint position, float size, Render* render, Input* input) : Tile(position, size, render, input)
{
}

bool PlayerTile::Start(iPoint position, fPoint offset, float size)
{
    this->offset = offset;
    this->collider = { (float)position.x, (float)position.y, size, size};
    return true;
}

bool PlayerTile::Update(float dt, std::vector<Tile*>* map)
{
    fPoint newPos = collider.GetPosition();

    if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) newPos.y -= 1;
    else if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) newPos.y += 1;
    else if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) newPos.x -= 1;
    else if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) newPos.x += 1;

    collider.SetPosition(newPos);

    return true;
}

bool PlayerTile::Draw(float dt)
{
    return true;
}

bool PlayerTile::DebugDraw()
{
    Rect rect = {(collider.x * collider.w) + offset.x, (collider.y * collider.w) + offset.y, collider.w, collider.h};
    render->DrawRectangle(rect, { 0, 255, 0, 100 });
    return true;
}

void PlayerTile::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}
