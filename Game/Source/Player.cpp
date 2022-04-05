#include "Player.h"

Player::Player(Render* render, Input* input) : Entity(EntityType::PLAYER, render, input)
{
}

bool Player::Start(fPoint position, float size)
{
    collider = {position.x, position.y, size, size};
    return true;
}

bool Player::Update(float dt)
{
    fPoint newPos = { 0, 0 };

    if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) collider.y -= collider.w;
    if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) collider.y += collider.w;
    if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) collider.x -= collider.w;
    if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) collider.x += collider.w;

    return true;
}

bool Player::Draw(float dt)
{
    return true;
}

bool Player::DebugDraw()
{
    render->DrawRectangle(collider, { 0, 255, 0, 150 });
    return true;
}

void Player::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}
