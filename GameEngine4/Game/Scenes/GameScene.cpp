#include "GameScene.h"

GameScene::GameScene()	{
}

GameScene::~GameScene()	{
}

bool GameScene::OnCreate() {
	Debug::Info("GameScene created", "GameScene.cpp", __LINE__); //Info message to say we loaded the GameScene

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(vec3(0.0f, 0.0f, 2.0f), 
																				0.1f, 0.5f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));
	CollisionHandler::GetInstance()->OnCreate();
	
	Model* diceModel = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("defaultShader"));
	Model* appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("defaultShader"));

	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, vec3(-2.0f, 0.0f, -2.0f)));
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, vec3(1.5f, 0.0f, 0.0f)), "Apple");

	diceModel = nullptr;
	appleModel = nullptr;
	
	return true;
}

void GameScene::Update(const float deltaTime_)	{
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render()	{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
