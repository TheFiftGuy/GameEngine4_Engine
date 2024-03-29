#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject	{
public:

	GameObject(Model* model_, vec3 position_ = vec3());
	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	vec3 GetPosition() const;
	float GetAngle() const;
	vec3 GetRotation() const;
	vec3 GetScale() const;
	string GetName() const;
	BoundingBox GetBoundingBox() const;
	bool GetHit() const;
	
	void SetPosition(vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(vec3 rotation_);
	void SetScale(vec3 scale_);
	void SetName(string name_);
	void SetHit(bool hit_, int buttonType_);

private:
	Model* model;
	unsigned int modelInstance;
	vec3 position;
	float angle;
	vec3 rotation;
	vec3 scale;
	string name;

	BoundingBox boundingBox;

	bool hit;
};

#endif