#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"
#include "Point.h"

class GuiSlider : public GuiControl
{
public:

    GuiSlider(Rect bounds, SDL_Texture* texture, Point scale, suint id, bool anchored, Input* input, Render* render, GuiManager* gui, Audio* audio, Scene* scene);
    virtual ~GuiSlider();

    bool Update(float dt);
    bool Draw(float scaleX = 1.0f, float scaleY = 1.0f, bool drawTexture = true, bool staticPos = true);
    void Delete();

    void SetMinValue(int val);
    void SetMaxValue(int val);
    void SetValue(int val);
    void UpdateValue();
    void SetSliderValue();

    int GetMinValue() const
    {
        return minValue;
    }

    int GetMaxValue() const
    {
        return maxValue;
    }

    int GetValue() const
    {
        return value;
    }

    float GetPercentValue() const
    {
        return percentValue * 100;
    }

    void SetSlider(SDL_Rect bounds);

    bool sliderFocus = false;

private:
    void UpdateDimensions(Point magnitudes);

private:

    SDL_Rect slider;
    int value;
    float percentValue;

    int minValue;
    int maxValue;

    bool sliderClicked = false;

    Point disabled = { 0, 0};
    Point normal = { 0, 0 };
    Point focused = { 0, 0 };
    Point pressed = { 0, 0 };

    Point disabledButton = { 0, 0 };
    Point normalButton = { 0, 0 };
    Point focusedButton = { 0, 0 };
    Point pressedButton = { 0, 0 };
};

#endif // __GUISLIDER_H__
