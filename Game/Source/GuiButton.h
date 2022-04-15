#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"
#include "Point.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(Rect bounds, SDL_Texture* texture, Point scale, suint id, bool anchored, Input* input, Render* render, GuiManager* gui, Audio* audio, Scene* scene);
    virtual ~GuiButton();

    bool Update(float dt);
    bool Draw(float dt) const;
    void Delete();
	bool buttonFocus = false;

private:
    void SetDimensions(Point magnitudes);

    void DebugDraw() const;

private:

    //Texture sections
    Point disabled = { 0, 0};
    Point normal = { 0, 0};
    Point focused = { 0, 0};
    Point pressed = { 0, 0};
};

#endif // __GUIBUTTON_H__
