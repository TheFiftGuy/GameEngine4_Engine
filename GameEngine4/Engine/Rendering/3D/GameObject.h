#ifndef GAMEOBJECT_H
#define GAMEOBJECT

#include "Model.h"

class GameObject	{
public:
	GameObject(Model* model_);
	~GameObject();

	void Render();

private:
	Model* model;

};

#endif // !