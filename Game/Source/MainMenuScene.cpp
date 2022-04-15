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
	gui->CreateGuiControl(GuiControlType::BUTTON, { 200, 200 }).AddGuiString("PLAY", 0, {255, 255, 255, 255}).AlignTo(Align::CENTER);
	gui->CreateTexture("Assets/Textures/UI/button_set_2.png");
	gui->CreateTexture("Assets/Textures/UI/button_set_3.png");
	gui->CreateTexture("Assets/Textures/UI/button_set_4.png");
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
