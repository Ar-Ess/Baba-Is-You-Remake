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
	gui->CreateTexture("Assets/Textures/UI/button_set_1.png", GuiControlType::BUTTON);
	gui->CreateTexture("Assets/Textures/UI/button_set_2.png", GuiControlType::BUTTON);
	gui->CreateTexture("Assets/Textures/UI/button_set_3.png", GuiControlType::BUTTON);
	gui->CreateGuiControl(GuiControlType::BUTTON, { 200, 200 }).AddGuiString("PLAY", 0, {255, 255, 255, 255}).AlignTo(Align::CENTER);

	gui->CreateGuiControl(GuiControlType::SLIDER, { 500, 400 }, {1, 1}, false, 1).AddGuiString("VOLUME", 0, { 255, 255, 255, 255 }).AlignTo(Align::BOTTOM_LEFT);

	return true;
}

bool MainMenuScene::Update(float dt)
{
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
