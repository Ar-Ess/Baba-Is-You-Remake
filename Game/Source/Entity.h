#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Render.h"
#include "Input.h"

class Enemy;
class Player;
class Boss;
class Item;
class NPC;

enum class EntityType
{
    PLAYER,
    ENEMY,
	BOSS,
    ITEM,
    NPC,
    UNKNOWN
};

class Entity
{
public:

    Entity(EntityType type) : type(type) {}

    Entity(EntityType type, Render* render, Input* input) : type(type), render(render), input(input) {}

    virtual bool Update(float dt)
    {
        return true;
    }

public:
    EntityType type;
    Render* render = nullptr;
    Input* input = nullptr;
};

#endif // __ENTITY_H__