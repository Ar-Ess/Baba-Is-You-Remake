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

	ControlSettings* AlignTo(Align align = TOP_LEFT)
	{
		GuiString* text = control->text;
		switch (align)
		{
		case CENTER:
			text->offset = {(dimensions.x / 2) - (text->bounds.w / 2), (dimensions.y / 2) - (text->bounds.h / 2) };
			break;
		}

		text->alignment = align;

		return ret;
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

		control->text = new GuiString(control->bounds, text, fontIndex, control->id, control->scale, control->render, control->gui, control->anchored, color);

		return Alignment(control, Point{control->bounds.w, control->bounds.h}, this);
	}

	// SliderSettings function allows to modify some parts of the functionality of a slider:
	//   - Initial Value: Set an initial value in which the slider will start
	//   - Allow RIPS: this system stands for "Retrieve Information Pressed State". If this option is false, 
	//                 the slider will retieve the value when the the click button is released. If the option
	//                 it true, it will retrieve the value each frame that the slider is pressed.
	void SliderSettings(float initialValue = 0.0f, bool allowRIPS = false)
	{
		// You tried to modify slider setting in another gui control. SliderSettings is only for Sliders
		assert(control->type == GuiControlType::SLIDER);

		GuiSlider* slider = (GuiSlider*)control;
		slider->SetRIPS(allowRIPS);
		slider->SetInitialValue(initialValue);
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

	ControlSettings CreateGuiControl(GuiControlType type, Point position = { 0, 0 }, Point scale = { 1, 1 }, bool anchored = false, suint texIndex = 0);

	void DestroyGuiControl(suint index);

	int CreateTexture(const char* path, GuiControlType type);

	TextureSwitcher ChangeTexture(suint controlIndex);
	
	void DestroyTexture(suint index);

	void CreateFont(const char* path, suint fontSize);

	SDL_Texture* PrintFont(const char* text, SDL_Color color, suint fontIndex, int endLine = -1);

	TextureSwitcher ChangeFont(suint controlIndex);

	void DestroyFont(suint index);

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

//TEXT
/*    IMPLEMENTATION
//testText = (GuiString*)app->guiManager->CreateGuiControl(GuiControlType::TEXT);
//testText->bounds = {400, 400, 0, 0};
//testText->SetString("TEST");
//testText->SetTextFont(app->fontTTF->defaultFont);

//    UPDATING
//testText->Draw();

//    DELETING
//testText->Delete();
//app->guiManager->DestroyGuiControl(testText);
//testText = nullptr;*/

//BUTTON
/*    IMPLEMENTATION
//testButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON);
//testButton->bounds = { 200, 200, 0, 0 };
//testButton->SetTexture("Assets/Textures/UI/button_set_1.png", { 163, 62 });
//testButton->SetObserver(this);
//testButton->text = "test";

//    UPDATING
//testButton->Update(0.0f);
//testButton->Draw();

//    DELETING
//testButton->Delete();
//app->guiManager->DestroyGuiControl(testButton);
//testButton = nullptr;*/

//CHECKBOX
/*    IMPLEMENTATION
//testCheckBox = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX);
//testCheckBox->bounds = { 400, 400, 0, 0 };
//testCheckBox->SetTexture("Assets/Textures/UI/checkbox_set_1.png", { 60, 64 });
//testCheckBox->SetObserver(this);
//testCheckBox->text = "test";

//    UPDATING
//testCheckBox->Update(0.0f);
//testCheckBox->Draw();

//    DELETING
//testCheckBox->Delete();
//app->guiManager->DestroyGuiControl(testCheckBox);
//testCheckBox = nullptr;*/

//SLIDER
/*    IMPLEMENTATION
//testSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER);
//testSlider->bounds = { 700, 400, 0, 0 };
//testSlider->SetMaxValue(128);
//testSlider->SetMinValue(0);
//testSlider->SetTexture("Assets/Textures/UI/slider_set_1.png", { 487, 22 }, { 60, 64 });
//testSlider->SetObserver(this);
//testSlider->text = "test";

//    UPDATING
//testSlider->Update(0.0f);
//testSlider->Draw();

//    DELETING
//testString->Delete();
//app->guiManager->DestroyGuiControl(testSlider);
//testString = nullptr;*/
