#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace  glm;

class Model	{
public:
	Model(GLuint shaderProgram_, vec3 position_ = vec3(), float angle_ = 0.0f, vec3 rotation_ = vec3(0.0f,1.0f,0.0f), 
		vec3 scale_ = vec3(1.0f));
	
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	vec3 GetPosition() const;
	float GetAngle() const;
	vec3 GetRotation() const;
	vec3 GetScale() const;
	
	void SetPosition(vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(vec3 rotation_);
	void SetScale(vec3 scale_);
	

private:
	std::vector<Mesh*> meshes;
	GLuint shaderProgram;

	vec3 position;
	float angle;
	vec3 rotation;
	vec3 scale;
	mat4 GetTransform() const;

};

#endif