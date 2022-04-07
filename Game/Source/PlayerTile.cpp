#include "PlayerTile.h"

PlayerTile::PlayerTile(Point position, float size, Render* render, Input* input) : Tile(position, size, render, input)
{
}

bool PlayerTile::Start(Point position, Point offset, float size)
{
    this->offset = offset;
    this->collider = { (float)position.x, (float)position.y, size, size};
    return true;
}

bool PlayerTile::Update(float dt, suint* map)
{
    // 20000 is the end, 1000 is top bool, 100 is down bool, 10 is left bool, 1 is right bool
    if (map == nullptr || *map == 21111) return true;

    Point newPos = collider.GetPosition();

    if      ((*map - 1000) >= 20000 && input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) newPos.y -= 1;
    else if ((*map - 1100) >= 20000 && input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) newPos.y += 1;
    else if ((*map - 1110) >= 20000 && input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) newPos.x -= 1;
    else if ((*map - 1111) >= 20000 && input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) newPos.x += 1;

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
