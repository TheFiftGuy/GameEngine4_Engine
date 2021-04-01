#include "GameScene.h"

GameScene::GameScene()	{
	shape = nullptr;
	model = nullptr;
}

GameScene::~GameScene()	{
	model = nullptr;
	
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate() {
	Debug::Info("GameScene created", "GameScene.cpp", __LINE__); //Info message to say we loaded the GameScene

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(vec3(0.0f, 0.0f, 2.0f), 
																				0.1f, 0.5f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));
	model = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("defaultShader"));
	//model->SetScale(vec3(0.5f));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)	{
	shape->Update(deltaTime_);
}

void GameScene::Render()	{
	shape->Render(CoreEngine::GetInstance()->GetCamera());
}
