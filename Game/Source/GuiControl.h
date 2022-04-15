#ifndef __GUICONTROL_H__
#define __GUICONTROL_H__

#include "Input.h"
#include "Audio.h"
#include "Render.h"
#include "Textures.h"
#include "Scene.h"

#include "Point.h"
#include "Rect.h"
#include "SString.h"

class Input;
class Audio;
class Render;
class Textures;
class Scene;
class GuiString;
class GuiManager;


enum class GuiControlType
{
    BUTTON,
    TOGGLE,
    CHECKBOX,
    SLIDER,
    SLIDERBAR,
    COMBOBOX,
    DROPDOWNBOX,
    INPUTBOX,
    VALUEBOX,
    SPINNER, 
    TEXT
};

enum class GuiControlState
{
    DISABLED,
    NORMAL,
    FOCUSED,
    PRESSED,
    SELECTED
};

class GuiControl
{
public:

    GuiControl(Rect bounds, GuiControlType type, SDL_Texture* texture, Point scale, suint id, bool anchored, Input* input, Render* render, GuiManager* gui, Audio* audio, Scene* scene) : 
        bounds(bounds), type(type), 
        state(GuiControlState::NORMAL), 
        texture(texture), 
        scale(scale), 
        id(id),
        anchored(anchored), 
        input(input), render(render), gui(gui), audio(audio), observer(scene) {}

    GuiControl(Rect bounds, GuiControlType type, SDL_Texture* texture, suint id, Point scale, bool anchored, Render* render, GuiManager* gui) :
        bounds(bounds),
        type(type),
        texture(texture),
        id(id),
        scale(scale),
        anchored(anchored),
        render(render), gui(gui) {}

    GuiControl(GuiControlType type) // Temp
    {

    }

    virtual bool Update(float dt)
    {
        return true;
    }

    virtual bool Draw(float dt) const
    {
        return true;
    }

    virtual void SetDimensions(Point dimensions) {}

    void NotifyObserver()
    {
        observer->OnGuiMouseClickEvent(this);
    }

public:
    Input* input = nullptr;
    Render* render = nullptr;
    GuiManager* gui = nullptr;
    Audio* audio = nullptr;
    Scene* observer = nullptr;
    GuiString* text;

    GuiControlType type;
    GuiControlState state;
    Rect bounds = {};
    suint id = 0;
    SDL_Texture* texture = nullptr;
    bool anchored = false;
    Point scale = { 0, 0 };
};

#endif // __GUICONTROL_H__