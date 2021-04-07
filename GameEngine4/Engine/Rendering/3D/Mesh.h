#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};

class Mesh	 {
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();
	
	void Render(Camera* camera_, std::vector<mat4>& instances_);

private:
	void GenerateBuffers();
	GLuint VAO; //VertexArrayObject - tells the GPU how data was stored/ordered
	GLuint VBO; //VertextBufferObjects - contains the data
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projectionLoc;
	GLuint viewPos, lightPos, lightAmbient, lightDiffuse, lightSpecular, lightColour;

	GLuint matDiffuseMap, matShininess, matTransparency, matAmbient, matDiffuse, matSpecular;
};

#endif