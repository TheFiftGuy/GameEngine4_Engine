#include "GameObject.h"

GameObject::GameObject(Model* model_) : model(nullptr), modelInstance(0), position(vec3()), angle(0.0f), rotation(vec3(0.0f,1.0f,0.0f)),
	 scale(vec3(1.0f))
{
	model = model_;
	if(model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}

}

GameObject::GameObject(Model* model_, vec3 position_) : model(nullptr), modelInstance(0), angle(0.0f), rotation(vec3(0.0f, 1.0f, 0.0f)),
	scale(vec3(1.0f))
{
	model = model_;
	position = position_;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::~GameObject()	{
	//model is deleted in the SceneGraph
	model = nullptr;
}

void GameObject::Update(const float deltaTime_)	{
	SetAngle(angle + 0.005f);
}

void GameObject::Render(Camera* camera_)	{
	if (model) {
		model->Render(camera_);
	}
}

vec3 GameObject::GetPosition() const	{
	return position;
}

float GameObject::GetAngle() const
{
	return angle;
}

vec3 GameObject::GetRotation() const
{
	return rotation;
}

vec3 GameObject::GetScale() const
{
	return scale;
}

string GameObject::GetName() const	{
	return name;
}

void GameObject::SetPosition(vec3 position_)	{
	position = position_;
	if(model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetAngle(float angle_)	{
	angle = angle_;
	if(model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetRotation(vec3 rotation_)	{
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetScale(vec3 scale_)	{
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetName(string name_)	{
	name = name_;
}
