#include "GameObject.h"

GameObject::GameObject(Model* model_, vec3 position_) : model(nullptr), modelInstance(0), angle(0.0f), rotation(vec3(0.0f, 1.0f, 0.0f)),
	scale(vec3(1.0f)), hit(false)
{
	model = model_;
	position = position_;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);

		//temp code
		cout << "Min: " << to_string(boundingBox.minVert) << ", Max: " << to_string(boundingBox.maxVert) << std::endl;
		//temp end
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

BoundingBox GameObject::GetBoundingBox() const	{
	return boundingBox;
}

bool GameObject::GetHit() const	{
	return hit;
}

void GameObject::SetPosition(vec3 position_)	{
	position = position_;
	if(model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_)	{
	angle = angle_;
	if(model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(vec3 rotation_)	{
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(vec3 scale_)	{
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
		boundingBox.minVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
		boundingBox.maxVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
	}
}

void GameObject::SetName(string name_)	{
	name = name_;
}

void GameObject::SetHit(bool hit_, int buttonType_)	{
	hit = hit_;
	if(hit) {
		cout << name << " was hit" << std::endl;
	}
}
