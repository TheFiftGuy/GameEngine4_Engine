#include "GameObject.h"

GameObject::GameObject(Model* model_)	{
	model = nullptr;
	model = model_;

}

GameObject::~GameObject()	{
	if (model) {
		delete model;
	}
	model = nullptr;
}

void GameObject::Render()	{
	if (model) {
		model->Render();
	}
}
