#include "Tile.h"

Tile::Tile(TileType type, Point position, float size, Input* input)
{
    this->collider = { (float)position.x, (float)position.y, size, size };
    this->input = input;
    this->behaviours = new Multibool(8);
    this->type = type;
    if (type == BLOCK_TILE) SetBehaviour(STOP, true);

    this->tiles = tiles;
}

bool Tile::Start()
{
    return true;
}

bool Tile::Update(float dt)
{
    bool ret = UpdateBehaviour();

    return ret;
}

bool Tile::CleanUp()
{
    delete behaviours;
    delete texture;
    return true;
}

bool Tile::UpdateBehaviour()
{
    bool ret = true;
    if (GetBehaviour(PLAYER))
    {
        Direction dir = NO_DIR;
        Point newPos = collider.GetPosition();
        Tile* interact = nullptr;

        if (IsAccessible(TOP) && input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
        {
            dir = TOP;
            /*if (map.top && map.top->GetBehaviour(PUSH)) --map.top->collider.y;
            interact = map.top;
            newPos.y -= 1;*/
        }
        else if (IsAccessible(BOTTOM) && input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
        {
            dir = BOTTOM;
            /*if (map.bottom && map.bottom->GetBehaviour(PUSH)) ++map.bottom->collider.y;
            interact = map.bottom;
            newPos.y += 1;*/
        }
        else if (IsAccessible(LEFT) && input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
        {
            dir = LEFT;
            /*if (map.left && map.left->GetBehaviour(PUSH)) --map.left->collider.x;
            interact = map.left;
            newPos.x -= 1;*/
        }
        else if (IsAccessible(RIGHT) && input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
        {
            dir = RIGHT;
            /*if (map.right && map.right->GetBehaviour(PUSH)) ++map.right->collider.x;
            interact = map.right;
            newPos.x += 1;*/
        }
        
        ret = !(dir == NO_DIR);
        if (ret)
        {
            MovementLogic(dir);
            /*collider.SetPosition(newPos);
            ResetMap();
            if (interact) interact->ResetMap();*/
        }
    }

    return ret;
}

void Tile::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

void Tile::ResetMap()
{
    suint size = tiles->size();
    map.Reset();

    for (suint a = 0; a < size; ++a)
    {
        Tile* mapTile = tiles->at(a);
        if (this == mapTile) continue;
        if (DistanceTo(mapTile->GetPosition()) >= 2) continue;

        if (GetPosition().Apply(0, -1) == mapTile->GetPosition()) map.top = mapTile;
        if (GetPosition().Apply(0, 1) == mapTile->GetPosition()) map.bottom = mapTile;
        if (GetPosition().Apply(-1, 0) == mapTile->GetPosition()) map.left = mapTile;
        if (GetPosition().Apply(1, 0) == mapTile->GetPosition()) map.right = mapTile;
    }
}

bool Tile::IsAccessible(Direction dir)
{
    Tile* check = nullptr;

    switch (dir)
    {
    case TOP: check = map.top; break;
    case BOTTOM: check = map.bottom; break;
    case LEFT: check = map.left; break;
    case RIGHT: check = map.right; break;
    }

    if (check == nullptr) return true;
    if (check->IsStatic()) return false;

    return check->IsAccessible(dir);
}

void Tile::MovementLogic(Direction dir)
{
    Point movement = {0, 0};
    Tile* next = nullptr;

    switch (dir)
    {
    case TOP: 
        movement = {0, -1}; 
        next = map.top;
        break;
    case BOTTOM: 
        movement = {0, 1};
        next = map.bottom;
        break;
    case LEFT: 
        movement = {-1, 0};
        next = map.left;
        break;
    case RIGHT: 
        movement = {1, 0};
        next = map.right;
        break;
    }

    collider.SetPosition(collider.GetPosition().Apply(movement));

    if (next == nullptr)
    {
        ResetMap();
        return;
    }
    if (next->IsStatic())
    {
        ResetMap();
        return;
    }

    next->MovementLogic(dir);

    ResetMap();
}
