#ifndef _GUISTRING_H_
#define _GUISTRING_H_

#include "GuiControl.h"
#include "FontTTF.h"

struct _TTF_Font;
struct SDL_Texture;

class GuiString : public GuiControl
{
public:
	GuiString(Rect bounds, const char* text, suint fontIndex, suint id, Point scale, Render* render, GuiManager* gui, bool anchored = false, SDL_Color color = {0, 0, 0, 255});

	virtual ~GuiString();

public:

	bool Draw() const;
	void Delete();
	void CenterAlign();

private:

	friend class Alignment;
	Point offset = { 0, 0 };

};

#endif // !_GUISTRING_H_
