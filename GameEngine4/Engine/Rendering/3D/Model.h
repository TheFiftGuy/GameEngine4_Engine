#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model	{
public:
	Model(GLuint shaderProgram_);
	~Model();

	void Render();
	void AddMesh(Mesh* mesh_);

private:
	std::vector<Mesh*> meshes;
	GLuint shaderProgram;

};

#endif