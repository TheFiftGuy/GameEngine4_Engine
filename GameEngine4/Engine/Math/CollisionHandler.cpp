#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
vector<GameObject*> CollisionHandler::prevCollisions = vector<GameObject*>();
OctSpacialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler() {
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler() {
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()	{
	if(collisionInstance.get() == nullptr) { //teacher question
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_)	{
	prevCollisions.clear();
	scenePartition = new OctSpacialPartition(worldSize_);
}

void CollisionHandler::OnDestroy() {
	delete scenePartition;
	scenePartition = nullptr;
	
	for (auto *entry: prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}

void CollisionHandler::AddObject(GameObject* go_)	{
	if (scenePartition != nullptr) { //teacher question (same)
		scenePartition->AddObject(go_);
	}
}

void CollisionHandler::MouseUpdate(vec2 mousePosition_, int buttonType_)	{
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_, CoreEngine::GetInstance()->GetScreenWidth(), 
								CoreEngine::GetInstance()->GetScreenHeight(), CoreEngine::GetInstance()->GetCamera());
	
	if (scenePartition != nullptr) { //teacher question (why not if(scene) )
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}

		for (auto* c : prevCollisions) {
			if (c != hitResult && c != nullptr) {
				c->SetHit(false, buttonType_);
			}
			c = nullptr;
		}
		prevCollisions.clear();

		if (hitResult) {
			prevCollisions.push_back(hitResult);
		}
	}
}



