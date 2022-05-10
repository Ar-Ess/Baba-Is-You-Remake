#include "GuiString.h"
#include "GuiManager.h"
#include "Textures.h"
#include "App.h"

GuiString::GuiString(Rect bounds, const char* string, suint fontIndex, suint id, Point scale, Render* render, GuiManager* gui, Textures* tex, bool anchored, SDL_Color color) :
	GuiControl(
		bounds, 
		GuiControlType::TEXT, 
		gui->PrintFont(string, color, fontIndex),
		id, 
		scale, 
		anchored, 
		render, 
		gui,
		tex
	)
{
	Point result = {};
	gui->CalculateSize(string, fontIndex, &result);
	this->bounds.w = result.x;
	this->bounds.h = result.y;
	this->fontId = fontIndex;
}

GuiString::~GuiString()
{
	if (text) delete text;
	tex->UnLoad(texture);
	texture = nullptr;
}

bool GuiString::Draw(float dt) const
{
	render->DrawTexture(texture, bounds.GetPosition().Apply(offset), scale, anchored);

	if (gui->debug) DebugDraw(dt);

	return true;
}

bool GuiString::DebugDraw(float dt) const
{
	render->DrawRectangle({ bounds.GetPosition().Apply(offset), bounds.GetDimensions().Multiply(scale)}, { 0, 255, 0, 80 });

	return true;
}

void GuiString::Delete()
{
	app->tex->UnLoad(texture);
	texture = nullptr;
}

void GuiString::SetString(const char* text, SDL_Color color)
{
	this->~GuiString();
	this->texture = gui->PrintFont(text, color, fontId);
}
