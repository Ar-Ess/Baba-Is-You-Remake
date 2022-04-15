#include "GuiString.h"
#include "GuiManager.h"
#include "Textures.h"
#include "App.h"

GuiString::GuiString(Rect bounds, const char* text, suint fontIndex, suint id, Point scale, Render* render, GuiManager* gui, bool anchored, SDL_Color color) : GuiControl(bounds, GuiControlType::TEXT, gui->PrintFont(text, color, fontIndex), id, scale, anchored, render, gui)
{
	Point result = {};
	gui->CalculateSize(text, fontIndex, &result);
	this->bounds.w = result.x;
	this->bounds.h = result.y;
}

GuiString::~GuiString()
{
	app->tex->UnLoad(texture);
}

bool GuiString::Draw() const
{
	Point position = bounds.GetPosition().Apply(offset);
	render->DrawTexture(texture, position, scale, anchored);

	return true;
}

void GuiString::Delete()
{
	app->tex->UnLoad(texture);
	texture = nullptr;
}

void GuiString::CenterAlign()
{
	int width = 0, height = 0;
	//app->fontTTF->CalcSize(text.GetString(), width, height, textFont);

	bounds.x += (bounds.w / 2) - (width / 2);
	bounds.y += (bounds.h / 2) - (height / 2);
}
