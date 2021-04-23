#include "SceneGraph.h"

unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
unordered_map<GLuint, vector<Model*>> SceneGraph::sceneModels = unordered_map<GLuint, vector<Model*>>();
map<string, GameObject*> SceneGraph::sceneGameObject = map<string, GameObject*>();


SceneGraph::SceneGraph() {
}

SceneGraph::~SceneGraph() {
	OnDestroy();
}


SceneGraph* SceneGraph::GetInstance()	{
	if(sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy()	{	
	if (!sceneGameObject.empty()) {
		for (auto object : sceneGameObject) {
			delete object.second;
			object.second = nullptr;
		}
		sceneGameObject.clear();
	}

	if(!sceneModels.empty()) {
		for(auto entry : sceneModels) {
			if(!entry.second.empty()) {
				for (auto *m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::AddModel(Model* model_)	{
	GLuint shader = model_->GetShaderProgram();
	if(sceneModels.find(shader) == sceneModels.end()) { //if it DID NOT find the shaderID in sceneModels
		sceneModels.insert(pair<GLuint, vector<Model*>>(shader, vector<Model*>()));
		sceneModels[shader].reserve(10);
	}
	sceneModels[shader].push_back(model_);
}

void SceneGraph::AddGameObject(GameObject* object_, string name_)	{
	if(name_.empty()) {
		string newName = "GameObject" + to_string(sceneGameObject.size() + 1);
		object_->SetName(newName);
		sceneGameObject[newName] = object_;
	}
	else if(sceneGameObject.find(name_) == sceneGameObject.end()) {
		object_->SetName(name_);
		sceneGameObject[name_] = object_;
	}
	else {
		string newName = "GameObject" + to_string(sceneGameObject.size() + 1);
		Debug::Error("Trying to add a GameObject with name: " + name_ + " , Name already exists. Name has been replaced by: " + newName + " .", "SceneGraph.cpp", __LINE__);
		object_->SetName(newName);
		sceneGameObject[newName] = object_;
	}

	CollisionHandler::GetInstance()->AddObject(object_);
}

GameObject* SceneGraph::GetGameObject(string name_)	{
	if(sceneGameObject.find(name_) != sceneGameObject.end()) {
		return  sceneGameObject[name_];
	}
	
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_)	{
	for (auto object : sceneGameObject) {
		object.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_)	{
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);
		for (auto m : entry.second) {
			m->Render(camera_);
		}
	}
}
