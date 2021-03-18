#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 colour;
};

class Mesh	 {
public:
	Mesh(std::vector<Vertex>& vertexList_, GLuint textureID_, GLuint shaderProgram_);
	~Mesh();
	
	void Render(Camera* camera_, mat4 transform_);

private:
	void GenerateBuffers();
	GLuint VAO; //VertexArrayObject - tells the GPU how data was stored/ordered
	GLuint VBO; //VertextBufferObjects - contains the data
	std::vector<Vertex> vertexList;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc;
	GLuint viewPos, lightPos, lightAmbient, lightDiffuse,lightSpecular, lightColour;
};

#endif