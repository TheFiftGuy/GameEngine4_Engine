#include "OctSpacialPartition.h"

int OctNode::childNum = 0;

OctNode::OctNode(vec3 position_, float size_, OctNode* parent_) : octBounds(nullptr), parent(nullptr), children(), objectList(vector<GameObject*>()) {
	objectList.reserve(10);
	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + vec3(size_);

	size = size_;

	parent = parent_;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		children[i] = nullptr;
	}
}

OctNode::~OctNode()	{
	delete octBounds;
	octBounds = nullptr;

	if(!objectList.empty()) {
		for (auto obj : objectList) {
			obj = nullptr; //scenegraph deletes obj pointer
		}
		objectList.clear();
	}

	for (int i = 0; i < CHILDREN_NUMBER; i++) { //teacher question
		if(children[i] != nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth_)	{
	if(depth_ > 0 && this) {
		float half = size / 2.0f;
		children[static_cast<int>(OctChildren::OCT_TLF)] = 
			new OctNode(vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);

		{} //add code for the other 8 children
		childNum += 8;
	}

	//recursive call
	if(depth_ > 0 && this) {
		for (int i = 0; i < CHILDREN_NUMBER; i++) {
			children[i]->Octify(depth_ - 1);
		}
	}
}

OctNode* OctNode::GetParent()	{
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos_)	{
	return children[static_cast<int>(childPos_)];
}

void OctNode::AddCollisionObject(GameObject* obj_)	{
	objectList.push_back(obj_);
}

int OctNode::GetObjectCount() const	{
	return objectList.size();
}

bool OctNode::IsLeaf() const	{
	if (children[0] == nullptr) { //teacher question
		return true;
	}
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const	{
	return octBounds;
}

int OctNode::GetChildCount() const	{
	return childNum;
}


//---------------------------------------------------------------------------------------------------------
//OctSpacialPartition

OctSpacialPartition::OctSpacialPartition(float worldSize_)
{
}

OctSpacialPartition::~OctSpacialPartition()
{
}

void OctSpacialPartition::AddObject(GameObject* obj_)
{
}

GameObject* OctSpacialPartition::GetCollision(Ray ray_)
{
	return nullptr;
}

void OctSpacialPartition::AddObjectToCell(OctNode* cell_, GameObject* obj_)
{
}

void OctSpacialPartition::PrepareCollisionQuery(OctNode* cell_, Ray ray_)
{
}
