#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"
#include "Point.h"
#include "Collider.h"

class GuiSlider : public GuiControl
{
public:

    GuiSlider(Rect bounds, SDL_Texture* texture, Point scale, suint id, bool anchored, Input* input, Render* render, GuiManager* gui, Audio* audio, Scene* scene);
    virtual ~GuiSlider();

    bool Update(float dt);
    bool Draw(float dt) const;
    void Delete();

    void SetMinValue(int val);
    void SetMaxValue(int val);
    void SetValue(int val);
    void UpdateValue();
    void SetSliderValue();

private:
    void SetDimensions(Point magnitudes);

private:

    Rect slider;
    Collision collisionUtils;
    float value = 0;

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
