#ifndef __GUI_MANAGER_H__
#define __GUI_MANAGER_H__

#include "Module.h"
#include "GuiControl.h"
#include "GuiString.h"
#include "GuiSlider.h"
#include "SDL/include/SDL_pixels.h"
#include "AlignEnum.h"

#include <vector>

class ControlSettings;
struct SDL_Texture;
struct _TTF_Font;
enum class GuiControlType;

struct Texture
{
	Texture(SDL_Texture* texture, Point dimensions, GuiControlType guiType)
	{
		this->texture = texture;
		this->dimensions = dimensions;
		this->type = guiType;
	}

	SDL_Texture* texture = nullptr;
	Point dimensions = {};
	GuiControlType type;
};

class Alignment
{
public:
	Alignment(GuiControl* control, Point dimensions, ControlSettings* ret)
	{
		this->control = control;
		this->dimensions = dimensions;
		this->ret = ret;
	}

	ControlSettings* AlignTo(Align align = TOP_LEFT, Point offset = {0, 0})
	{
		GuiString* text = control->text;
		switch (control->type)
		{
		case GuiControlType::BUTTON: ButtonAlignment(text, align); break;
		}

		text->alignment = align;

		text->offset += offset;

		return ret;
	}

private:

	void ButtonAlignment(GuiString* text, Align align)
	{
		switch (align)
		{
		case CENTER:
			text->offset = { (dimensions.x / 2) - (text->bounds.w / 2), (dimensions.y / 2) - (text->bounds.h / 2) };
			break;

		case BOTTOM_LEFT:
			text->offset = { 0.0f, dimensions.y - (0.25f * text->bounds.h) };
			break;

		case TOP_LEFT:
			text->offset = { 0.0f, (-0.75f * text->bounds.h) };
			break;

		case CENTER_LEFT:
			text->offset = { 0.0f, (dimensions.y / 2) - (text->bounds.h / 2) };
			break;

		case BOTTOM_RIGHT:
			text->offset = { dimensions.x - text->bounds.w, dimensions.y - (0.25f * text->bounds.h) };
			break;

		case TOP_RIGHT:
			text->offset = { dimensions.x - text->bounds.w, (-0.75f * text->bounds.h) };
			break;

		case CENTER_RIGHT:
			text->offset = { dimensions.x - text->bounds.w, (dimensions.y / 2) - (text->bounds.h / 2) };
			break;

		case CENTER_TOP:
			text->offset = { (dimensions.x / 2) - (text->bounds.w / 2), (-0.75f * text->bounds.h) };
			break;

		case CENTER_BOTTOM:
			text->offset = { (dimensions.x / 2) - (text->bounds.w / 2), dimensions.y - (0.25f * text->bounds.h) };
			break;
		}
	}

private:

	GuiControl* control = nullptr;
	ControlSettings* ret = nullptr;
	Point dimensions = {};
};

class TextureSwitcher
{
public:
	TextureSwitcher(GuiControl* control, std::vector<Texture*>* textures)
	{
		this->control = control;
		this->textures = textures;
	}

	void To(suint newTextureId)
	{
		assert(newTextureId > 0 && newTextureId < textures->size());
		Texture* newTexture = textures->at(newTextureId);
		control->texture = newTexture->texture;
		control->SetDimensions(newTexture->dimensions);
	}

	bool Next()
	{
		suint size = textures->size();
		int index = -1;
		for (suint i = 0; i < size; ++i)
		{
			if (textures->at(i)->texture == control->texture)
			{
				index = i;
				break;
			}
		}

		if (index == -1) return false;

		Texture* newTexture = textures->at(index);

		for (suint i = index + 1; i != index; ++i)
		{
			if (i == (size - 1)) i = 0;

			if (textures->at(i)->type == control->type)
			{
				newTexture = textures->at(i);
				break;
			}
		}

		control->texture = newTexture->texture;
		control->SetDimensions(newTexture->dimensions);

		return true;
	}

	bool Prev()
	{
		suint size = textures->size();
		int index = -1;
		for (suint i = 0; i < size; ++i)
		{
			if (textures->at(i)->texture == control->texture)
			{
				index = i;
				break;
			}
		}

		if (index == -1) return false;

		Texture* newTexture = textures->at(index);

		for (int i = index - 1; i != index; --i)
		{
			if (i == -1) i = size - 1;

			if (textures->at(i)->type == control->type)
			{
				newTexture = textures->at(i);
				break;
			}
		}

		control->texture = newTexture->texture;
		control->SetDimensions(newTexture->dimensions);

		return true;
	}

private:

	GuiControl* control = nullptr;
	std::vector<Texture*>* textures = {};
};

class FontSwitcher
{
public:
	FontSwitcher(GuiControl* control, std::vector<_TTF_Font*>* fonts)
	{
		this->control = control;
		this->fonts = fonts;
	}

	void To(suint newFontId)
	{
		assert(newFontId >= 0 && newFontId < fonts->size());

		GuiString* string = control->text;
		Point position = control->GetPosition();
		Align alignment = string->alignment;
		GuiString* newString = new GuiString(string->bounds, string->string, newFontId, string->id, string->scale, string->render, string->gui, string->tex, string->anchored, string->color);
		
		RELEASE(string);
		newString->SetPosition(position);
		newString->alignment = alignment;
		if (control->type != GuiControlType::TEXT) control->text = newString;
		else control = newString;

		Alignment align(control, control->bounds.GetDimensions(), nullptr);
		align.AlignTo(alignment);
	}

	bool Next()
	{
		GuiString* str = nullptr;
		if (control->type != GuiControlType::TEXT) str = control->text;
		else str = (GuiString*)control;
		short int newIndex = str->fontId;

		if (str->fontId == fonts->size() - 1) newIndex = -1;

		newIndex++;

		To(newIndex);

		return true;
	}

	bool Prev()
	{
		GuiString* str = nullptr;
		if (control->type != GuiControlType::TEXT) str = control->text;
		else str = (GuiString*)control;
		short int newIndex = str->fontId;

		if (str->fontId == 0) newIndex = fonts->size();

		newIndex--;

		To(newIndex);

		return true;
	}

private:

	GuiControl* control = nullptr;
	std::vector<_TTF_Font*>* fonts = {};
};

class ControlSettings
{
public:
	ControlSettings(GuiControl* control)
	{
		this->control = control;
	}

	Alignment AddGuiString(const char* text, suint fontIndex = 0, SDL_Color color = { 0, 0, 0, 255 })
	{
		// You already created a text for this Gui Control, no more that 1 text is allowed
		assert(control->type != GuiControlType::TEXT && control->text == nullptr);

		control->text = new GuiString(control->bounds, text, fontIndex, control->id, control->scale, control->render, control->gui, control->tex, control->anchored, color);

		return Alignment(control, Point{control->bounds.w, control->bounds.h}, this);
	}

	// SliderSettings function allows to modify some parts of the functionality of a slider:
	//   - Initial Value: Set an initial value in which the slider will start
	//   - Allow RIPS: this system stands for "Retrieve Information Pressed State". If this option is false, 
	//                    the slider will retieve the value when the the click button is released. If the option
	//                    it true, it will retrieve the value each frame that the slider is pressed.
	//   - Range: this variable allows to set the value given at the minimum position and the value given at the
	//            maximum position of the slider. Point{minimum, maximum}
	ControlSettings* SliderSettings(float initialValue = 0.0f, bool allowRIPS = false, Point range = {0, 100})
	{
		// You tried to modify slider setting in another gui control. SliderSettings is only for Sliders
		assert(control->type == GuiControlType::SLIDER);

		GuiSlider* slider = (GuiSlider*)control;
		slider->SetRIPS(allowRIPS);
		slider->SetInitialValue(initialValue);
		slider->SetRange(range);

		return this;
	}

private:

	GuiControl* control = nullptr;
};

class GuiManager : public Module
{
public:

	GuiManager(Input* input, Render* Render, Audio* audio, Textures* texture, int selectKey = 43);

	virtual ~GuiManager();

	bool Awake(pugi::xml_node&);

	bool Start(Scene* scene);

	bool Update(float dt);

	bool Draw(float dt);

	bool CleanUp();

	ControlSettings CreateGuiControl(GuiControlType type, Point position = { 0, 0 }, suint texIndex = 0, bool anchored = false, Point scale = {1, 1});

	void DestroyGuiControl(suint index);

	int CreateTexture(const char* path, GuiControlType type);

	TextureSwitcher ChangeTexture(suint controlIndex);
	
	void DestroyTexture(suint index);

	void CreateFont(const char* path, suint fontSize);

	SDL_Texture* PrintFont(const char* text, SDL_Color color, suint fontIndex, int endLine = -1);

	FontSwitcher ChangeFont(suint controlIndex);

	void DisableAllButtons();

private:
	
	friend class GuiString;
	bool CalculateSize(const char* text, suint fontIndex, Point* result) const;

	bool InitializeFonts();

	void SelectButtonsLogic();

public:

	bool debug = false;

private:

	Input* input = nullptr;
	Render* render = nullptr;
	Audio* audio = nullptr;
	Textures* texture = nullptr;
	Scene* scene = nullptr;

	std::vector<GuiControl*> controls;
	std::vector<Texture*> textures;
	std::vector<_TTF_Font*> fonts;
	
	int selectKey = 43;
	int idSelection = -1;

};

#endif // __GUI_MANAGER_H__