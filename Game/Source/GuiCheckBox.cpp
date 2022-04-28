#include "GuiCheckBox.h"
#include "GuiManager.h"

GuiCheckBox::GuiCheckBox(Rect bounds, SDL_Texture* texture, Point scale, suint id, bool anchored, Input* input, Render* render, GuiManager* gui, Audio* audio, Scene* scene, Textures* tex) :
    GuiControl(
        bounds,
        GuiControlType::CHECKBOX,
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

GuiCheckBox::~GuiCheckBox()
{

}

bool GuiCheckBox::Update(float dt)
{
    if (state == GuiControlState::DISABLED) return true;
    Point mouse = input->GetMousePosition();
    bool on = collisionUtils.CheckCollision(Rect{ mouse, 1.0f, 1.0f }, bounds);
    bool click = (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT);
    GuiControlState prevState = state;


    if (!on && !click)
    {
        if (prevState == GuiControlState::PRESSED)
        {
            checked = !checked;
            NotifyObserver(0.0f, checked);
        }
        state = GuiControlState::NORMAL;
        prevState = state;
        return true;
    }

    switch (state)
    {
    case GuiControlState::NORMAL:
        state = GuiControlState::NORMAL;
        if (!on) break;
        audio->SetFx(Effect::BUTTON_FOCUSSED);
        state = GuiControlState::FOCUSED;

    case GuiControlState::FOCUSED:
        if (!click) break;
        state = GuiControlState::PRESSED;
        audio->SetFx(Effect::BUTTON_RELEASED);
        break;

    case GuiControlState::PRESSED:
        if (click) break;

        state = GuiControlState::FOCUSED;
        checked = !checked;
        NotifyObserver(0.0f, checked);
        break;
    }

    prevState = state;

    return true;
}

bool GuiCheckBox::Draw(float dt) const
{
    Rect section = { 0, 0, bounds.w, bounds.h };

    switch (state)
    {
    case GuiControlState::DISABLED:
        section.x = disabled.x;
        section.y = disabled.y;
        break;

    case GuiControlState::NORMAL:
        if (checked)
        {
            section.x = checkNormal.x;
            section.y = checkNormal.y;
        }
        else
        {
            section.x = uncheckNormal.x;
            section.y = uncheckNormal.y;
        }
        break;

    case GuiControlState::FOCUSED:
        if (checked)
        {
            section.x = checkFocused.x;
            section.y = checkFocused.y;
        }
        else
        {
            section.x = uncheckFocused.x;
            section.y = uncheckFocused.y;
        }
        break;

    case GuiControlState::PRESSED:
        if (checked)
        {
            section.x = checkPressed.x;
            section.y = checkPressed.y;
        }
        else
        {
            section.x = uncheckPressed.x;
            section.y = uncheckPressed.y;
        }
        break;

    default:
        break;
    }

    render->DrawTexture(texture, bounds.GetPosition(), scale, anchored, &section);

    if (gui->debug) DebugDraw();

    return true;
}

void GuiCheckBox::DebugDraw() const
{
    Rect buttonRect = bounds;

    if (anchored)
    {
        buttonRect.x += (int)app->render->camera.x;
        buttonRect.y += (int)app->render->camera.y;
    }

    buttonRect.w *= scale.x;
    buttonRect.h *= scale.y;

    switch (state)
    {
    case GuiControlState::DISABLED: app->render->DrawRectangle(buttonRect, { 100, 100, 100, 80 });
        break;
    case GuiControlState::NORMAL: app->render->DrawRectangle(buttonRect, { 0, 255, 0, 80 });
        break;
    case GuiControlState::FOCUSED: app->render->DrawRectangle(buttonRect, { 255, 255, 0, 80 });
        break;
    case GuiControlState::PRESSED: app->render->DrawRectangle(buttonRect, { 0, 255, 255, 80 });
        break;
    default:
        break;
    }
}

void GuiCheckBox::Delete()
{
    tex->UnLoad(texture);
    texture = nullptr;
}

void GuiCheckBox::SetDimensions(Point magnitude)
{
    bounds.w = magnitude.x;
    bounds.h = magnitude.y / 7;

    disabled = { 0.0f, 0 * bounds.h };
    checkNormal = { 0.0f, 1 * bounds.h };
    checkFocused = { 0.0f, 2 * bounds.h };
    checkPressed = { 0.0f, 3 * bounds.h };
    uncheckNormal = { 0.0f, 4 * bounds.h };
    uncheckFocused = { 0.0f, 5 * bounds.h };
    uncheckPressed = { 0.0f, 6 * bounds.h };
}
