#include "GameScene.h"

GameScene::GameScene()	{
	shape = nullptr;
}

GameScene::~GameScene()	{
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()	{
	Debug::Info("GameScene created", "GameScene.cpp", __LINE__); //Info message to say we loaded the GameScene

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(6);
	
	////original triangle
	//v.position = glm::vec3(0.0f, 0.5f, 0.0f);
	//vertexList.push_back(v);
	//v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	//vertexList.push_back(v);
	//v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	//vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.0f); //top left
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);//bottom left
	v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);//bottom right
	v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	//2nd triangle
	v.position = glm::vec3(0.5f, 0.5f, 0.0f);//top right
	v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);//top left
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);//bottom right
	v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	//note that despite the object being a square, since the window is a rectangle its being distorted.

	Model* model = new Model(ShaderHandler::GetInstance()->GetShader("colourShader"));
	model->AddMesh(new Mesh(vertexList));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)	{
}

void GameScene::Render()	{
	shape->Render();
}
