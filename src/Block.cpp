#include <Block.hpp>
#include "OBJ_Loader.h"

Block::Block(std::bitset<6> sides, Shader& shader,  glm::vec3 position) {
	this->shader = &shader;
	this->Position = position;

	//this->cubeMesh->move(this->Position);
	//this->cubeMesh->setOrigin(glm::vec3(1.0f, 1.0f, 1.0f));


	this->cube = Cube();

	std::vector<Vertex> collection;

	//set position
	for (int i = 0; i < this->cube.vertices.size(); i++) {
		this->cube.vertices[i].position += position;
	}

	//oderedi strani
	/*
	for (int i = 0; i < sides.size(); i++) {
		if (!sides[i]) {
			cube.indices.erase(cube.indices.begin() + 6 * i, cube.indices.begin() + 6 * (i + 1));
		}
	}
	*/

	if (!sides[4]) { // Top
		cube.indices.erase(cube.indices.begin() + 6 * 5, cube.indices.begin() + 6 * 6);
	}
	if (!sides[5]) { // Bottom
		cube.indices.erase(cube.indices.begin() + 6 * 4, cube.indices.begin() + 6 * 5);
	}
	if (!sides[2]) { // Right
		cube.indices.erase(cube.indices.begin() + 6 * 3, cube.indices.begin() + 6 * 4);
	}
	if (!sides[1]) { // Back
		cube.indices.erase(cube.indices.begin() + 6 * 2, cube.indices.begin() + 6 * 3);
	}
	if (!sides[3]) { // Left
		cube.indices.erase(cube.indices.begin() + 6 * 1, cube.indices.begin() + 6 * 2);
	}
	if (!sides[0]) { // Front
		cube.indices.erase(cube.indices.begin() + 6 * 0, cube.indices.begin() + 6 * 1);
	}


	//set all verticies without indicies
	for (int i = 0; i < this->cube.indices.size(); i++) {
		//collection.push_back(this->cube.vertices[this->cube.indices[i]]);
		collection.push_back(Vertex(this->cube.vertices[this->cube.indices[i]]));
	}



	this->cubeMesh = new Mesh(collection.data(), collection.size(), NULL, 0, glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f));


	//this->cubeMesh->setPosition(Position);

}
/*
void generateCube() {
	Vertex* data = Quad().getVertices();


	for (size_t i = 0; i < 4; i++)
	{
		Vertex vertex = data[i];

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));

		model = glm::rotate(model, (float)glm::radians(90.0), glm::vec3(0.f, 1.f, 0.f));

		model = glm::translate(model, glm::vec3(0.5, 0, 0.5));

		vertex.position = model * glm::vec4(vertex.position, 1.0f);

		//data[i*4] = pos + rotacija + pomestuvanje;
	}

	//Mesh test = Mesh(data);
}
*/


Block::Block(){}

void Block::Draw() {


	//Activate texture for each mesh
	//this->overrideTextureDiffuse->bind(0);
	//this->overrideTextureSpecular->bind(1);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//shader->use();

	

	//glBindVertexBuffer(cubeMesh->VBO);
	cubeMesh->render(shader);
	//glBindVertexArray(0);

	/*
	if (sides[0]) { // Front
		cubeMesh->setRotation(glm::vec3(0, 0, 0));
		cubeMesh->setPosition(glm::vec3(0, 0, 0));
		cubeMesh->render(shader);
	}

	if (sides[1]) { // Back
		cubeMesh->setRotation(glm::vec3(0, 0, 0));
		cubeMesh->setPosition(glm::vec3(0, 0, -1));
		cubeMesh->render(shader);
	}
	
	if (sides[2]) { // Right
		cubeMesh->setRotation(glm::vec3(0, 90, 0));
		cubeMesh->setPosition(glm::vec3(0.5, 0, 0.5));
		cubeMesh->render(shader);
	}

	if (sides[3]) { // Left
		cubeMesh->setRotation(glm::vec3(0, -90, 0));
		cubeMesh->setPosition(glm::vec3(-0.5, 0, 0.5));
		cubeMesh->render(shader);
	}

	if (sides[4]) { // Top
		cubeMesh->setRotation(glm::vec3(90, 0, 0));
		cubeMesh->setPosition(glm::vec3(0, -0.5, -0.5));
		cubeMesh->render(shader);
	}

	if (sides[5]) { // Bottom
		cubeMesh->setRotation(glm::vec3(90, 0, 0));
		cubeMesh->setPosition(glm::vec3(0, -0.5, 0.5));
		cubeMesh->render(shader);
	}
	*/

	//glBindVertexArray(0);
	//glUseProgram(0);
	//glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Block::Realese() {
	//cubeMesh->~Mesh();
}

void Block::SetPosition(glm::vec3 pos) {
	this->Position = pos;


	cubeMesh->setPosition(this->Position);
	cubeMesh->setOrigin(this->Position);

}
void Block::setActiveSides(std::bitset<6> sides) {
	this->sides = sides;
}