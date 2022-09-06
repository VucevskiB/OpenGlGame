#include <Block.hpp>
#include "OBJ_Loader.h"

Block::Block(unsigned int texture, Shader& shader,  Mesh& mesh) {
	this->texture = texture;
	this->shader = &shader;

	this->cubeMesh = &mesh;

	//this->cubeMesh->move(this->Position);
	this->cubeMesh->setOrigin(glm::vec3(1.0f, 1.0f, 1.0f));


	this->quad = Quad();

	
	
}
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


Block::Block(){}

void Block::Draw() {


	//Activate texture for each mesh
	//this->overrideTextureDiffuse->bind(0);
	//this->overrideTextureSpecular->bind(1);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//shader->use();

	//glBindVertexArray(this->cubeMesh->VAO);



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