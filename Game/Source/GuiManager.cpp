#include "GuiManager.h"

#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
#include "GuiString.h"
#include "FontTTF.h"

#include "Log.h"

GuiManager::GuiManager(Input* input, Render* render, Audio* audio, Textures* texture, int selectKey)
{
	this->selectKey = selectKey;
	this->texture = texture;
	this->input = input;
	this->render = render;
	this->audio = audio;
}

GuiManager::~GuiManager()
{
}

bool GuiManager::Awake(pugi::xml_node&)
{
	return true;
}

bool GuiManager::Start(Scene* scene)
{
	CreateTexture("Assets/Textures/UI/button_default_set.png");
	debug = false;
	this->scene = scene;
	return true;
}

bool GuiManager::Update(float dt)
{
	suint size = controls.size();
	for (suint i = 0; i < size; ++i)
	{
		controls[i]->Update(dt);
	}

	SelectButtonsLogic();

	return true;
}

bool GuiManager::Draw(float dt)
{
	suint size = controls.size();
	for (suint i = 0; i < size; ++i)
	{
		controls[i]->Draw(dt);
	}

	return true;
}

void GuiManager::CreateGuiControl(GuiControlType type, Point position, Point scale, bool anchored, suint texIndex)
{
	GuiControl* control = nullptr;

	Texture* tex = textures.at(texIndex);
	Rect bounds = { position.x, position.y, tex->dimensions.x, tex->dimensions.y};

	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(bounds, tex->texture, scale, controls.size(), anchored, input, render, this, audio, scene); 
		break;
	case GuiControlType::CHECKBOX: control = new GuiCheckBox({ 0, 0, 0, 0 }, "0"); break;
	case GuiControlType::SLIDER: control = new GuiSlider({ 0, 0, 0, 0 }, "0"); break;
	case GuiControlType::TEXT: control = new GuiString(); break;
	default: break;
	}

	if (control != nullptr) controls.push_back(control);
}

void GuiManager::DestroyGuiControl(suint index)
{
	controls.erase(controls.begin() + index);
}

void GuiManager::CreateTexture(const char* path)
{
	Point dimensions = {};
	SDL_Texture* tex = texture->Load(path, &dimensions);
	textures.push_back(new Texture(tex, dimensions));
}

void GuiManager::DestroyTesture(suint index)
{
	texture->UnLoad(textures.at(index)->texture);
	textures.erase(textures.begin() + index);
}

TextureSwitcher GuiManager::ChangeTexture(suint controlIndex)
{
	return TextureSwitcher(controls.at(controlIndex), &textures);
}

void GuiManager::DisableAllButtons()
{
	suint size = controls.size();
	for (suint i = 0; i < size; ++i)
	{
		controls[i]->state = GuiControlState::DISABLED;
	}
}

void GuiManager::SelectButtonsLogic()
{

	if (app->input->GetKey(selectKey) == KEY_DOWN || app->input->GetControl(L3) == KEY_DOWN)
	{
		idSelection++;
		DisableAllButtons();
	}

	/*switch (s->GetCurrScene())
	{
	case MAIN_MENU:
		if (idSelection == 0) s->newGameButton->buttonFocus = true;
		else if (idSelection == 1) s->continueButton->buttonFocus = true;
		else if (idSelection == 2) s->optionsButton->buttonFocus = true;
		else if (idSelection == 3) s->exitButton->buttonFocus = true;
		else if (idSelection == 4) idSelection = -1;
		break;

	case PAUSE_MENU:
		if (idSelection == 0) s->backToGameButton->buttonFocus = true;
		else if (idSelection == 1) s->saveGameButton->buttonFocus = true;
		else if (idSelection == 2) s->optionsPauseButton->buttonFocus = true;
		else if (idSelection == 3) s->backToMenuButton->buttonFocus = true;
		else if (idSelection == 4) idSelection = -1;
		break;

	case OPTIONS_MENU:
		if (idSelection == 0) s->optionsMenu->dFullScreenCheckBox->checkBoxFocus = true;
		else if (idSelection == 1) s->optionsMenu->fullScreenCheckBox->checkBoxFocus = true;
		else if (idSelection == 2) s->optionsMenu->vSyncCheckBox->checkBoxFocus = true;
		else if (idSelection == 3) s->optionsMenu->musicVolumeSlider->sliderFocus = true;
		else if (idSelection == 4) s->optionsMenu->fxVolumeSlider->sliderFocus = true;
		else if (idSelection == 5) s->optionsMenu->returnMenuButton->buttonFocus = true;
		else if (idSelection == 6) idSelection = -1;
		break;
	}*/
}

bool GuiManager::CleanUp()
{
	return true;
}

