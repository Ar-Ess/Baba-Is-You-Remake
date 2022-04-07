#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "App.h"
#include "GuiControl.h"

#include "Point.h"

class GuiCheckBox : public GuiControl
{
public:

    GuiCheckBox(SDL_Rect bounds, const char *text);
    virtual ~GuiCheckBox();

    bool Update(float dt);
    bool Draw(float scaleX = 1.0f, float scaleY = 1.0f, bool drawTexture = true, bool staticPos = true);
    void SetTexture(const char* path, Point magnitude);
    void Delete();
    
    bool checkBoxFocus = false;

    bool GetCheckedState() const
    {
        return checked;
    }

private:
    void UpdateDimensions(Point magnitudes);
    bool checked = false;
    SDL_Texture* spritesheet = nullptr;
    //options menu

    Point checkNormal = {0, 0};
    Point checkFocused = { 0, 0 };
    Point checkPressed = { 0, 0 };
    Point uncheckNormal = { 0, 0 };
    Point uncheckFocused = { 0, 0 };
    Point uncheckPressed = { 0, 0 };
    Point locked = {0, 0};
};

#endif // __GUICHECKBOX_H__
