#include "StartScene.h"

StartScene::StartScene(){
}

StartScene::~StartScene()	{
}

bool StartScene::OnCreate()	{
	Debug::Info("StartScene created", "StartScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCurrentScene(1);

	return true;
}

void StartScene::Update(const float deltaTime_)	{
}

void StartScene::Render()	{
}
