#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0), modelLoc(0), viewLoc(0), projectionLoc(0),
	viewPos(0), lightPos(0), lightAmbient(0), lightDiffuse(0), lightSpecular(0), lightColour(0),
	matDiffuseMap(0), matShininess(0), matTransparency(0), matAmbient(0), matDiffuse(0), matSpecular(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()	{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if(!subMesh.vertexList.empty()) {
		subMesh.vertexList.clear();
	}

	if(!subMesh.meshIndices.empty()) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<mat4>& instances_)	{
	glUniform1i(matDiffuseMap, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniform3fv(viewPos, 1, value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPos, 1, value_ptr(camera_->GetLightSourceList().front()->GetPosition()));
	glUniform1f(lightAmbient, camera_->GetLightSourceList().front()->GetAmbient());
	glUniform1f(lightDiffuse, camera_->GetLightSourceList().front()->GetDiffuse());
	glUniform1f(lightSpecular, camera_->GetLightSourceList().front()->GetSpecular());
	glUniform3fv(lightColour, 1, value_ptr(camera_->GetLightSourceList().front()->GetLightColour()));

	glUniform1f(matShininess, subMesh.material.shininess);
	glUniform1f(matTransparency, subMesh.material.transparency);
	glUniform3fv(matAmbient, 1, value_ptr(subMesh.material.ambient));
	glUniform3fv(matDiffuse, 1, value_ptr(subMesh.material.diffuse));
	glUniform3fv(matSpecular, 1, value_ptr(subMesh.material.specular));
	
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(camera_->GetPerspective()));
	
	glBindVertexArray(VAO);
	
	glEnable(GL_DEPTH_TEST);
	
	for (auto t : instances_) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(t));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()	{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates) );

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	viewPos = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPos = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbient = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightSpecular = glGetUniformLocation(shaderProgram, "light.specular");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColour");

	matDiffuseMap = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	matShininess = glGetUniformLocation(shaderProgram, "material.shininess");
	matTransparency = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmbient = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiffuse = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpecular = glGetUniformLocation(shaderProgram, "material.specular");
}
