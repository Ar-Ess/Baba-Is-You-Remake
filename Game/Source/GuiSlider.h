#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"

enum SliderType {
    MUSIC,
    FX,
};

class GuiSlider : public GuiControl
{
public:

    GuiSlider(SDL_Rect bounds, const char *text);
    virtual ~GuiSlider();

    bool Update(float dt);
    bool Draw(float scaleX = 1.0f, float scaleY = 1.0f, bool drawTexture = true, bool staticPos = true);
    void SetTexture(const char* path, Point barMagnitude, Point sMagnitude);
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
    void UpdateDimensions(Point barMagnitudes, Point sMagnitudes);

private:

    SDL_Rect slider;
    SDL_Texture* spritesheet = nullptr;
    int value;
    float percentValue;

    int minValue;
    int maxValue;

    bool sliderClicked = false;

    Point locked = { 0, 0};
    Point normal = { 0, 0 };
    Point focused = { 0, 0 };
    Point pressed = { 0, 0 };

    Point sLocked = { 0, 0 };
    Point sNormal = { 0, 0 };
    Point sFocused = { 0, 0 };
    Point sPressed = { 0, 0 };

    Point sLowLocked = { 0, 0 };
    Point sLowNormal = { 0, 0 };
    Point sLowFocused = { 0, 0 };
    Point sLowPressed = { 0, 0 };

    Point sMuteLocked = { 0, 0 };
    Point sMuteNormal = { 0, 0 };
    Point sMuteFocused = { 0, 0 };
    Point sMutePressed = { 0, 0 };
};

#endif // __GUISLIDER_H__
