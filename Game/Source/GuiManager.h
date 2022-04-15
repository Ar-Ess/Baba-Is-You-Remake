#ifndef __GUI_MANAGER_H__
#define __GUI_MANAGER_H__

#include "Module.h"
#include "GuiControl.h"

#include <vector>

struct SDL_Texture;
enum class GuiControlType;

struct Texture
{
	Texture(SDL_Texture* texture, Point dimensions)
	{
		this->texture = texture;
		this->dimensions = dimensions;
	}

	SDL_Texture* texture = nullptr;
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
		suint index = -1;
		for (suint i = 0; i < size; ++i)
		{
			if (textures->at(i)->texture == control->texture)
			{
				index = i;
				break;
			}
		}

		if (index == -1) return false;

		if (index == (size - 1)) index = 0;
		else ++index;

		Texture* newTexture = textures->at(index);
		control->texture = newTexture->texture;
		control->SetDimensions(newTexture->dimensions);

		return true;
	}

	bool Prev()
	{
		suint size = textures->size();
		suint index = -1;
		for (suint i = 0; i < size; ++i)
		{
			if (textures->at(i)->texture == control->texture)
			{
				index = i;
				break;
			}
		}

		if (index == -1) return false;

		if (index == 0) index = size - 1;
		else --index;

		Texture* newTexture = textures->at(index);
		control->texture = newTexture->texture;
		control->SetDimensions(newTexture->dimensions);

		return true;
	}

private:

	GuiControl* control = nullptr;
	std::vector<Texture*>* textures = {};
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

	void CreateGuiControl(GuiControlType type, Point position = { 0, 0 }, Point scale = { 1, 1 }, bool anchored = false, suint texIndex = 0);

	void DestroyGuiControl(suint index);

	void CreateTexture(const char* path);

	TextureSwitcher ChangeTexture(suint controlIndex);
	
	void DestroyTesture(suint index);

	void DisableAllButtons();

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
