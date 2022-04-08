#include "Tile.h"

Tile::Tile(TileType type, Point position, float size, Point offset, Render* render, Input* input)
{
    this->type = type;
    this->collider = { (float)position.x, (float)position.y, size, size };
    this->offset = offset;
    this->render = render;
    this->input = input;
    this->behaviours = new Multibool(8);
}

bool Tile::Start()
{
    return true;
}

bool Tile::Update(float dt, Multibool map)
{
    bool ret = UpdateBehaviour(map);

    return ret;
}

bool Tile::Draw(float dt)
{
    return true;
}

bool Tile::DebugDraw()
{
    Rect rect = {(collider.x * collider.w) + offset.x, (collider.y * collider.w) + offset.y, collider.w, collider.h};
    SDL_Color color = {};

    switch (type)
    {
    case PLAYER_TILE: color = {0, 255, 0, 150}; break;
    case BLOCK_TILE: color = { 255, 0, 0, 150 }; break;
    case ROCK_TILE: color = { 90, 30, 0, 150 }; break;
    }

    render->DrawRectangle(rect, color);
    return true;
}

bool Tile::CleanUp()
{
    delete behaviours;
    delete texture;
    return true;
}

bool Tile::UpdateBehaviour(Multibool map)
{
    bool ret = true;
    if (GetBehaviour(PLAYER))
    {
        if (map.IsAllTrue()) return true; // TEMPORAL (tiles could be push)

        Point newPos = collider.GetPosition();

        if (!map.Get(0) && input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) newPos.y -= 1;
        else if (!map.Get(1) && input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) newPos.y += 1;
        else if (!map.Get(2) && input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) newPos.x -= 1;
        else if (!map.Get(3) && input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) newPos.x += 1;
        
        ret = !(collider.GetPosition() == newPos);
        if (ret) collider.SetPosition(newPos);
    }

    return ret;
}

void Tile::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}
