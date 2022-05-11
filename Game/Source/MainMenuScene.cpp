#include "MainMenuScene.h"
#include "GuiManager.h"

MainMenuScene::MainMenuScene(Render* render, Input* input, GuiManager* gui)
{
	this->render = render;
	this->input = input;
	this->gui = gui;
}

MainMenuScene::~MainMenuScene()
{
}

bool MainMenuScene::Start()
{
	gui->GuiSettings(true, SDL_SCANCODE_0, false, false);

	gui->CreateGuiControl(GuiControlType::IMAGE, { 0, 0 }, 3, false, { 5, 5 });

	gui->CreateGuiControl(GuiControlType::BUTTON, { 200, 200 })
		.AddGuiString("PLAY", 0, { 255, 255, 255, 255 }).AlignTo(Align::CENTER);

	gui->CreateGuiControl(GuiControlType::SLIDER, { 500, 400 }, 1, false, {1, 1})
		.AddGuiString("VOLUME", 0, { 255, 255, 255, 255 }).AlignTo(Align::TOP_RIGHT)
		->SliderSettings(50, false);

	gui->CreateGuiControl(GuiControlType::CHECKBOX, { 800, 100 }, 2, false, { 1, 1 })
		.AddGuiString("DEBUG", 0, { 255, 255, 255, 255 }).AlignTo(Align::CENTER_TOP);

	return true;
}

bool MainMenuScene::Update(float dt)
{
	gui->Update(dt);
	return true;
}

bool MainMenuScene::Draw(float dt)
{
	gui->Draw(dt);
	return true;
}

bool MainMenuScene::CleanUp()
{
	return true;
}

bool MainMenuScene::DebugDraw()
{
	return true;
}
