#ifndef MODEL_H
#define MODEL_H

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"



class Model	{
public:
	Model(const string& objPath_, const string& matPath_, GLuint shaderProgram_);	
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);
	unsigned int CreateInstance(vec3 position_, float angle_, vec3 rotation_, vec3 scale_);
	void UpdateInstance(unsigned int index_, vec3 position_,float angle_, vec3 rotation_, vec3 scale_);
	mat4 GetTransform(unsigned int index_) const;	

private:
	mat4 CreateTransform(vec3 position_, float angle_, vec3 rotation_, vec3 scale_) const;
	void LoadModel();
	
	vector<Mesh*> meshes;
	GLuint shaderProgram;
	vector<mat4> modelInstances;
	LoadOBJModel* obj;
};

#endif