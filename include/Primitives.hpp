#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include<vector>
#include"Vertex.hpp"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Primitive();
	virtual ~Primitive();

	void set(const Vertex* vertices,
		const unsigned nrOfVertices,
		const GLuint* indices,
		const unsigned nrOfIndices);
	

	Vertex* getVertices();
	GLuint* getIndices();
	const unsigned getNrOfVertices();
	const unsigned getNrOfIndices();
};

class Triangle : public Primitive
{
public:
	Triangle();

};

class Quad : public Primitive
{
public:
	Quad();
};

class Pyramid : public Primitive
{
public:
	Pyramid();
};

class Cube : public Primitive
{
public:
	Cube();
	
};