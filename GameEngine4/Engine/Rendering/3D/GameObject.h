#ifndef GAMEOBJECT_H
#define GAMEOBJECT

#include "Model.h"

class GameObject	{
public:
	GameObject(Model* model_);
	~GameObject();

	void Render(Camera* camera_);

private:
	Model* model;

};

#endif // !