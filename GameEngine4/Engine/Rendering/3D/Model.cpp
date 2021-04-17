#include "Model.h"

Model::Model(const string& objPath_, const string& matPath_, GLuint shaderProgram_) : meshes(vector<Mesh*>()), modelInstances(vector<mat4>())
{
	shaderProgram = shaderProgram_;
	meshes.reserve(10);
	modelInstances.reserve(5);
	obj = new LoadOBJModel();
	obj->LoadModel(objPath_, matPath_);
	LoadModel();
}

Model::~Model()	{
	if (!meshes.empty()) {
		for (auto *m : meshes) {
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}

	if(!modelInstances.empty()) {
		modelInstances.clear();
	}
	
	delete obj;
	obj = nullptr;
}

void Model::Render(Camera* camera_)	{
	glUseProgram(shaderProgram);
	for (auto *m : meshes) {
		m->Render(camera_, modelInstances);
	}
}

void Model::AddMesh(Mesh* mesh_)	{
	meshes.push_back(mesh_);
}

unsigned int Model::CreateInstance(vec3 position_, float angle_, vec3 rotation_, vec3 scale_)	{
	modelInstances.push_back(CreateTransform(position_, angle_, rotation_, scale_));
	
	return modelInstances.size() - 1;
}

void Model::UpdateInstance(unsigned int index_, vec3 position_, float angle_, vec3 rotation_, vec3 scale_)	{
	modelInstances[index_] = CreateTransform(position_, angle_, rotation_, scale_);
}

mat4 Model::GetTransform(unsigned int index_) const	{
	return modelInstances[index_];
}

GLuint Model::GetShaderProgram() const	{
	return shaderProgram;
}

BoundingBox Model::GetBoundingBox() const	{
	return boundingBox;
}

mat4 Model::CreateTransform(vec3 position_, float angle_, vec3 rotation_, vec3 scale_) const	{
	mat4 model;
	model = translate(model, position_);
	model = rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);
	return model;
}

void Model::LoadModel()	{
	for (auto t : obj->GetSubMeshes()) {
		meshes.push_back(new Mesh(t, shaderProgram));
	}

	boundingBox = obj->GetBoundingBox();
	
	delete obj;
	obj = nullptr;
}

