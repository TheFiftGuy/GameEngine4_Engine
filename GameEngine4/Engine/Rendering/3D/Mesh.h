#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 colour;
};

class Mesh	 {
public:
	Mesh(std::vector<Vertex>& vertexList_);
	~Mesh();

	void Render();

private:
	void GenerateBuffers();
	GLuint VAO; //VertexArrayObject - tells the GPU how data was stored/ordered
	GLuint VBO; //VertextBufferObjects - contains the data
	std::vector<Vertex> vertexList;

};

#endif