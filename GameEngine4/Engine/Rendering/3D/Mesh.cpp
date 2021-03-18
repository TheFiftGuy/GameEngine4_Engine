#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertexList_, GLuint textureID_, GLuint shaderProgram_) : VAO(0), VBO(0), vertexList(std::vector<Vertex>()),
shaderProgram(0), textureID(0), viewLoc(0), projectionLoc(0), textureLoc(0), viewPos(0), lightPos(0), lightAmbient(0),
lightDiffuse(0), lightColour(0)
{
	vertexList = vertexList_;
	shaderProgram = shaderProgram_;
	textureID = textureID_;
	GenerateBuffers();
}

Mesh::~Mesh()	{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	vertexList.clear();
}

void Mesh::Render(Camera* camera_, glm::mat4 transform_)	{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(camera_->GetView()));
	
	//glUniform3f(viewPos, camera_->GetPosition().x, camera_->GetPosition().y, camera_->GetPosition().z);
	glUniform3fv(viewPos, 1, value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPos, 1, value_ptr(camera_->GetLightSourceList().front()->GetPosition()));
	glUniform1f(lightAmbient, camera_->GetLightSourceList().front()->GetAmbient());
	glUniform1f(lightDiffuse, camera_->GetLightSourceList().front()->GetDiffuse());
	glUniform3fv(lightColour, 1, value_ptr(camera_->GetLightSourceList().front()->GetLightColour()));
	
	
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(camera_->GetPerspective()));
	
	glBindVertexArray(VAO);
	
	glEnable(GL_DEPTH_TEST);
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(transform_));

	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());

	glBindVertexArray(0);
}

void Mesh::GenerateBuffers()	{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates) );

	//Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour) );

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	//UNFINISHED
	viewPos = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPos = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbient = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColour");
}
