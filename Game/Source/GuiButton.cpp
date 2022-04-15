#include "GuiButton.h"
#include "GuiManager.h"

GuiButton::GuiButton(Rect bounds, SDL_Texture* texture, Point scale, suint id, bool anchored, Input* input, Render* render, GuiManager* gui, Audio* audio, Scene* scene) : 
    GuiControl(
        bounds,
        GuiControlType::BUTTON,
        texture,
        scale,
        id,
        anchored,
        input, 
        render, 
        gui, 
        audio,
        scene
    )
{
    SetDimensions(Point{ bounds.w, bounds.h });
}

GuiButton::~GuiButton()
{
	observer = nullptr;
    //text.Clear();
    //text.~SString();
}

bool GuiButton::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        Point mouse = input->GetMousePosition();

        if ((mouse.x > bounds.x) && (mouse.x < (bounds.x + bounds.w)) &&
            (mouse.y > bounds.y) && (mouse.y < (bounds.y + bounds.h)))
        {
            if (state == GuiControlState::NORMAL)
            {
                audio->SetFx(Effect::BUTTON_FOCUSSED);
            }
            state = GuiControlState::FOCUSED;
            if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP || input->GetControl(A) == KeyState::KEY_UP)
            {
                audio->SetFx(Effect::BUTTON_RELEASED);
                NotifyObserver();
            }
        }
        else if (buttonFocus)
        {
            if (state == GuiControlState::NORMAL)
            {
                audio->SetFx(Effect::BUTTON_FOCUSSED);
            }
            state = GuiControlState::FOCUSED;
            if ((input->GetControl(A) == KeyState::KEY_REPEAT) || (input->GetKey(SDL_SCANCODE_RETURN) == KeyState::KEY_REPEAT))
            {
                state = GuiControlState::PRESSED;
            }

            if ((input->GetControl(A) == KeyState::KEY_UP) || (input->GetKey(SDL_SCANCODE_RETURN) == KeyState::KEY_UP))
            {
                audio->SetFx(Effect::BUTTON_RELEASED);
                NotifyObserver();
                //gui->idSelection = -1;
            }
        }
        else state = GuiControlState::NORMAL;
    }
    return true;
}

bool GuiButton::Draw(float dt) const
{
    Rect section = { 0, 0, bounds.w, bounds.h };
    switch (state)
    {
    case GuiControlState::DISABLED:
        section.x = disabled.x;
        section.y = disabled.y;
        break;
    case GuiControlState::NORMAL:
        section.x = normal.x;
        section.y = normal.y;
        break;
    case GuiControlState::FOCUSED:
        section.x = focused.x;
        section.y = focused.y;
        break;
    case GuiControlState::PRESSED:
        section.x = pressed.x;
        section.y = pressed.y;
        break;
    }

    render->DrawTexture(texture, bounds.GetPosition(), scale, anchored, &section);

    if (text) text->Draw();

    if (gui->debug) DebugDraw();

    return false;
}

void GuiButton::DebugDraw() const
{
    Rect buttonRect = bounds;

    if (anchored)
    {
        buttonRect.x += (int)render->camera.x;
        buttonRect.y += (int)render->camera.y;
    }

    buttonRect.w *= scale.x;
    buttonRect.h *= scale.y;

    switch (state)
    {
    case GuiControlState::DISABLED: render->DrawRectangle(buttonRect, { 100, 100, 100, 80 });
        break;
    case GuiControlState::NORMAL: render->DrawRectangle(buttonRect, { 0, 255, 0, 80 });
        break;
    case GuiControlState::FOCUSED: render->DrawRectangle(buttonRect, { 255, 255, 0, 80 });
        break;
    case GuiControlState::PRESSED: render->DrawRectangle(buttonRect, { 0, 255, 255, 80 });
        break;
    }
}

void GuiButton::Delete()
{
    //observer = nullptr;
    //app->tex->UnLoad(spritesheet);
    //spritesheet = nullptr;
    //text.Clear();
}

void GuiButton::SetDimensions(Point magnitude)
{
    bounds.w = magnitude.x;
    bounds.h = magnitude.y / 4;

    disabled = { 0.0f, 0 * bounds.h};
    normal = { 0.0f, 1 * bounds.h };
    focused = { 0.0f, 2 * bounds.h };
    pressed = { 0.0f, 3 * bounds.h };
}
