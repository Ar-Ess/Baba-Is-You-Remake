#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"
#include "Point.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(SDL_Rect bounds, const char* text);
    virtual ~GuiButton();

    bool Update(float dt);
    bool Draw(float scaleX = 1.0f, float scaleY = 1.0f, bool drawTexture = true, bool staticPos = true);
    void SetTexture(const char* path, Point magnitude);
    void Delete();
	bool buttonFocus = false;

private:
    void UpdateDimensions(Point magnitudes);

private:
    //Texture sections
    Point locked = { 0, 0};
    Point normal = { 0, 0};
    Point focused = { 0, 0};
    Point pressed = { 0, 0};
    SDL_Texture* spritesheet = nullptr;
};

#endif // __GUIBUTTON_H__
