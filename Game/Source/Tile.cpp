#include "Tile.h"

Tile::Tile(TileType type, TileClass clas, Point position, float size, Input* input)
{
    this->collider = { (float)position.x, (float)position.y, size, size };
    this->input = input;
    this->behaviours = new Multibool(8);
    this->type = type;
    this->clas = clas;
    if (type == BLOCK_TILE) SetBehaviour(STOP, true);
}

bool Tile::Start()
{
    return true;
}

bool Tile::UpdateBehaviour(float dt)
{
    bool ret = true;
    if (GetBehaviour(PLAYER))
    {
        Direction dir = NO_DIR;
        Point newPos = collider.GetPosition();
        Tile* interact = nullptr;

        if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && IsAccessible(TOP)) dir = TOP;
        else if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && IsAccessible(BOTTOM)) dir = BOTTOM;
        else if (input->GetKey(SDL_SCANCODE_A) == KEY_DOWN && IsAccessible(LEFT)) dir = LEFT;
        else if (input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && IsAccessible(RIGHT)) dir = RIGHT;

        ret = !(dir == NO_DIR);
        if (ret)
        {
            MovementLogic(dir);
        }
    }

    return ret;
}

bool Tile::UpdateLogic(float dt)
{
    if (clas != TEXT) return true;

    TileType affected = NO_TILE;

    switch (type)
    {
    case PLAYER_TEXT_TILE: affected = PLAYER_TILE;break;
    case ROCK_TEXT_TILE: affected = ROCK_TILE; break;
    case FLAG_TEXT_TILE: affected = FLAG_TILE; break;
    case WALL_TEXT_TILE: affected = WALL_TILE; break;
    }

    // IMPORTANT: If a tile is not stop it should be transpassable
    // Maybe each position may have more than one tile...

    LookAheadLogic(RIGHT, affected);
    LookAheadLogic(BOTTOM, affected);

    /*Bottom Logic, problem with overwritting of the "Right-direction" logic*/
    //next = map.bottom;
    //if (!next || next->type != IS_TILE)
    //{
    //    manager->ResetBehaviors(affected, PLAYER, false);
    //    manager->ResetBehaviors(affected, PUSH, false);
    //    return true;
    //}
    //if (!next->map.bottom) return true;
    //switch (next->map.bottom->type) //probably ending up being recursive (if AND TILE implemented)
    //{
    //case YOU_B_TILE: manager->ResetBehaviors(affected, PLAYER, true); break;
    //case PUSH_B_TILE: manager->ResetBehaviors(affected, PUSH, true); break;
    //default:
    //    if (!prevBehaviourTile[1]) break;
    //    switch (*prevBehaviourTile[1])
    //    {
    //    case YOU_B_TILE: manager->ResetBehaviors(affected, PLAYER, false); break;
    //    case PUSH_B_TILE: manager->ResetBehaviors(affected, PUSH, false); break;
    //    }
    //    break;
    //}
    //prevBehaviourTile[1] = &next->map.bottom->type;

    return true;
}

bool Tile::CleanUp()
{
    delete behaviours;
    return true;
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
    if (check->IsTransparent()) return true;
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
        manager->ResetTileMap(this);
        return;
    }
    if (next->behaviours->Get(PUSH))
    {
        next->MovementLogic(dir);
        return;
    }

    manager->ResetTileMap(this);
}

void Tile::LookAheadLogic(Direction dir, TileType affected)
{
    Tile* next = map.Get(dir);

    if (!next || next->clas != LINKER)
    {
        if (prevBehaviourTile[dir] == NO_TILE) return;
        // No available for "Tile change" mechanic (Player->Is->Flag)
        manager->ResetBehaviors(affected, GetBehaviorFromType(prevBehaviourTile[dir]), false);
        prevBehaviourTile[dir] = NO_TILE;
        return;
    }

    next = next->map.Get(dir);
    if (!next || next->clas != BEHAVIOR)
    {
        if (prevBehaviourTile[dir] == NO_TILE) return;

        manager->ResetBehaviors(affected, GetBehaviorFromType(prevBehaviourTile[dir]), false);
        prevBehaviourTile[dir] = NO_TILE;
        return;
    }

    if (prevBehaviourTile[dir] != NO_TILE) manager->ResetBehaviors(affected, GetBehaviorFromType(prevBehaviourTile[dir]), false);
    manager->ResetBehaviors(affected, GetBehaviorFromType(next->type), true);
    prevBehaviourTile[dir] = next->type;
    return;

}

Behaviour Tile::GetBehaviorFromType(TileType type)
{
    Behaviour ret = NO_BEHAVIOR;
    switch (type)
    {
    case PUSH_B_TILE: ret = PUSH; break;
    case YOU_B_TILE: ret = PLAYER; break;
    case STOP_B_TILE: ret = STOP; break;
    case WIN_B_TILE: ret = WIN; break;
    }

    return ret;
}
