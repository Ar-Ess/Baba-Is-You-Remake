#include "GuiImage.h"
#include "GuiManager.h"

GuiImage::GuiImage(Rect bounds, SDL_Texture* texture, Point scale, suint id, bool anchored, Input* input, Render* render, GuiManager* gui, Audio* audio, Scene* scene, Textures* tex) :
    GuiControl(
        bounds,
        GuiControlType::IMAGE,
        texture,
        scale,
        id,
        anchored,
        input,
        render,
        gui,
        audio,
        scene,
        tex
    )
{
    SetDimensions(Point{ bounds.w, bounds.h });
}

GuiImage::~GuiImage()
{
}

bool GuiImage::Update(float dt)
{
    return true;
}

bool GuiImage::Draw(float dt) const
{
    render->DrawTexture(texture, bounds.GetPosition(), scale, anchored);

    return false;
}

void GuiImage::Delete()
{
    //observer = nullptr;
    //app->tex->UnLoad(spritesheet);
    //spritesheet = nullptr;
    //text.Clear();
}

void GuiImage::SetDimensions(Point magnitude)
{
    bounds.w = magnitude.x;
    bounds.h = magnitude.y;
}