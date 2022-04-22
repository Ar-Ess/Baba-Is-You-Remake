#include "GuiSlider.h"
#include "GuiManager.h"

GuiSlider::GuiSlider(Rect bounds, SDL_Texture* texture, Point scale, suint id, bool anchored, Input* input, Render* render, GuiManager* gui, Audio* audio, Scene* scene) :
    GuiControl(
        bounds,
        GuiControlType::SLIDER,
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

GuiSlider::~GuiSlider()
{
    app->tex->UnLoad(texture);
}

bool GuiSlider::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        float mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);

        if ((mouseX > slider.x) && (mouseX < (slider.x + slider.w)) &&
            (mouseY > slider.y) && (mouseY < (slider.y + slider.h)))
        {
            if (state == GuiControlState::NORMAL)
            {
                app->audio->SetFx(Effect::BUTTON_FOCUSSED);
            }
            state = GuiControlState::FOCUSED;

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN || app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT || app->input->GetControl(A) == KeyState::KEY_DOWN || app->input->GetControl(A) == KeyState::KEY_REPEAT) sliderClicked = true;
        }
        else if (sliderFocus)
        {
            if (state == GuiControlState::NORMAL)
            {
                app->audio->SetFx(Effect::BUTTON_FOCUSSED);
            }
            state = GuiControlState::FOCUSED;

            sliderClicked = true;
        }
        else if (!sliderClicked) state = GuiControlState::NORMAL;

        if (sliderClicked)
        {
            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT || app->input->GetControl(A) == KeyState::KEY_REPEAT)
            {
                if (state == GuiControlState::FOCUSED)
                {
                    app->audio->SetFx(Effect::BUTTON_RELEASED);
                }
                state = GuiControlState::PRESSED;

                if (mouseX > (bounds.x + slider.w / 2) && mouseX < (bounds.x + bounds.w - slider.w / 2)) slider.x = mouseX - (slider.w * 0.5);
                else if (mouseX + (int)(slider.w * 0.5) > (bounds.x + bounds.w)) slider.x = (bounds.x + bounds.w) - slider.w;
                else if ((mouseX - (int)(slider.w * 0.5)) < bounds.x) slider.x = bounds.x;
                UpdateValue();
            }
            else if (app->input->GetControl(LEFT_PAD) == KeyState::KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_DOWN)
            {
                if (state == GuiControlState::FOCUSED)
                {
                    app->audio->SetFx(Effect::BUTTON_RELEASED);
                }
                state = GuiControlState::SELECTED;

                slider.x -= 10;

                if (((slider.w / 2) + slider.x) < bounds.x)
                {
                    slider.x = bounds.x - (slider.w / 2);
                }

                UpdateValue();
            }
            else if (app->input->GetControl(RIGHT_PAD) == KeyState::KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_DOWN)
            {
                if (state == GuiControlState::FOCUSED)
                {
                    app->audio->SetFx(Effect::BUTTON_RELEASED);
                }
                state = GuiControlState::SELECTED;

                slider.x += 10;

                if (((slider.w / 2) + slider.x) > bounds.x + bounds.w) slider.x = bounds.x + bounds.w - (slider.w / 2);

                UpdateValue();
            }
            else if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP || app->input->GetControl(A) == KeyState::KEY_UP || !sliderFocus) sliderClicked = false;
        }
    }

    return false;
}

bool GuiSlider::Draw(float scaleX, float scaleY, bool drawTexture, bool staticPos)
{
    /*
    if (drawTexture)
    {
        SDL_Rect barSection = { 0, 0, bounds.w, bounds.h };
        SDL_Rect sSection = { 0, 0, slider.w, slider.h };

        switch (state)
        {
        case GuiControlState::DISABLED:
            barSection.x = disabled.x;
            barSection.y = disabled.y;
            app->render->DrawTexture(texture, bounds.x, bounds.y, scaleX, scaleY, &barSection, false, staticPos);
            if (GetValue() > 65)
            {
                sSection.x = sLocked.x;
                sSection.y = sLocked.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            else if (GetValue() > 0)
            {
                sSection.x = sLowLocked.x;
                sSection.y = sLowLocked.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            else
            {
                sSection.x = sMuteLocked.x;
                sSection.y = sMuteLocked.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            break;

        case GuiControlState::NORMAL:
            barSection.x = normal.x;
            barSection.y = normal.y;
            app->render->DrawTexture(texture, bounds.x, bounds.y, scaleX, scaleY, &barSection, false, staticPos);

            if (GetValue() > 65)
            {
                sSection.x = sNormal.x;
                sSection.y = sNormal.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            else if (GetValue() > 0)
            {
                sSection.x = sLowNormal.x;
                sSection.y = sLowNormal.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            else
            {
                sSection.x = sMuteNormal.x;
                sSection.y = sMuteNormal.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            break;

        case GuiControlState::FOCUSED:
            barSection.x = focused.x;
            barSection.y = focused.y;
            app->render->DrawTexture(texture, bounds.x, bounds.y, scaleX, scaleY, &barSection, false, staticPos);

            if (GetValue() > 65)
            {
                sSection.x = sFocused.x;
                sSection.y = sFocused.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            else if (GetValue() > 0)
            {
                sSection.x = sLowFocused.x;
                sSection.y = sLowFocused.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            else
            {
                sSection.x = sMuteFocused.x;
                sSection.y = sMuteFocused.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            break;

        case GuiControlState::PRESSED:
            barSection.x = pressed.x;
            barSection.y = pressed.y;
            app->render->DrawTexture(texture, bounds.x, bounds.y, scaleX, scaleY, &barSection, false, staticPos);

            if (GetValue() > 65)
            {
                sSection.x = sPressed.x;
                sSection.y = sPressed.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            else if (GetValue() > 0)
            {
                sSection.x = sLowPressed.x;
                sSection.y = sLowPressed.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            else
            {
                sSection.x = sMutePressed.x;
                sSection.y = sMutePressed.y;
                app->render->DrawTexture(texture, slider.x, slider.y, scaleX, scaleY, &sSection, false, staticPos);
            }
            break;
        }
    }
    */

    if (app->guiManager->debug)
    {
        Rect barRect = bounds;
        SDL_Rect sRect = slider;

        if (staticPos)
        {
            barRect.x += (int)app->render->camera.x;
            barRect.y += (int)app->render->camera.y;
            sRect.x += (int)app->render->camera.x;
            sRect.y += (int)app->render->camera.y;
        }
        barRect.w *= scaleX;
        barRect.h *= scaleY;
        sRect.w *= scaleX;
        sRect.h *= scaleY;

        switch (state)
        {
        case GuiControlState::DISABLED:
            app->render->DrawRectangle(barRect, { 100, 100, 100, 80 });
            app->render->DrawRectangle(slider, { 150, 100, 100, 80 });
            break;

        case GuiControlState::NORMAL:
            app->render->DrawRectangle(barRect, { 0, 255, 0, 80 });
            app->render->DrawRectangle(slider, { 0, 200, 0, 80 });
            break;

        case GuiControlState::FOCUSED:
            app->render->DrawRectangle(barRect, { 255, 255, 0, 80 });
            app->render->DrawRectangle(slider, { 255, 255, 0, 80 });
            break;

        case GuiControlState::PRESSED:
            app->render->DrawRectangle(barRect, { 0, 255, 255, 80 });
            app->render->DrawRectangle(slider, { 0, 200, 200, 80 });
            break;
        }
    }

    return false;
}

void GuiSlider::SetMinValue(int val)
{
    minValue = val;
}

void GuiSlider::SetMaxValue(int val)
{
    maxValue = val;
}

void GuiSlider::SetValue(int val)
{
    value = val;
}

void GuiSlider::UpdateValue()
{
    float sliderPos = ((slider.x + (slider.w / 2)) - (bounds.x + (slider.w / 2)));
    float totalWidth = bounds.w - slider.w;

    percentValue = sliderPos / totalWidth;

    value = (int)floor(percentValue * maxValue);
}

void GuiSlider::SetSliderValue()
{
    float v = (float)value;
    float mV = (float)maxValue;
    float prop = v / mV;
    slider.x = bounds.x + (bounds.w * prop);
    slider.y = (bounds.y + (bounds.h / 2)) - (slider.h / 2);
}

void GuiSlider::SetSlider(SDL_Rect bounds)
{
    slider = { (bounds.x + (int)(bounds.w * 0.5)) - (int)(bounds.h * 0.5), bounds.y, bounds.h,bounds.h };
    UpdateValue();
}

void GuiSlider::Delete()
{
    observer = nullptr;
    app->tex->UnLoad(texture);
    texture = nullptr;
}

void GuiSlider::UpdateDimensions(Point magnitudes)
{
    bounds.w = magnitudes.x;
    bounds.h = magnitudes.y / 8;

    disabled = { 0.0f, 0 * bounds.h };
    normal =   { 0.0f, 1 * bounds.h };
    focused =  { 0.0f, 2 * bounds.h };
    pressed =  { 0.0f, 3 * bounds.h };
    disabledButton = { 0.0f, 4 * bounds.h };
    normalButton =   { 0.0f, 5 * bounds.h };
    focusedButton  =  { 0.0f, 6 * bounds.h };
    pressedButton =  { 0.0f, 7 * bounds.h };

    if (text) Alignment(text, Point{ bounds.w, bounds.h }).AlignTo(text->GetAlignment());
}
