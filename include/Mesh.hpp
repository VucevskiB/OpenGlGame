#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<iostream>
#include<vector>

#include"Vertex.hpp"
#include"Primitives.hpp"
#include "Shader.hpp"

class Mesh
{
private:
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices = 0;

	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void initVAO();

	void updateUniforms(Shader* shader);


	void updateModelMatrix();

public:
	inline static GLuint VAO;


	Mesh();

	Mesh(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices,
		glm::vec3 position,
		glm::vec3 origin ,
		glm::vec3 rotation,
		glm::vec3 scale);
	

	Mesh(
		Primitive* primitive,
		glm::vec3 position ,
		glm::vec3 origin ,
		glm::vec3 rotation ,
		glm::vec3 scale );

	Mesh(const Mesh& obj);
	

	~Mesh();

	//Accessors

	//Modifiers
	void setPosition(const glm::vec3 position);


	void setOrigin(const glm::vec3 origin);


	void setRotation(const glm::vec3 rotation);


	void setScale(const glm::vec3 setScale);


	//Functions

	void move(const glm::vec3 position);


	void rotate(const glm::vec3 rotation);


	void scaleUp(const glm::vec3 scale);


	void update();

	void render(Shader* shader);
};