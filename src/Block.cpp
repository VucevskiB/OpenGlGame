#include <Block.hpp>
#include "OBJ_Loader.h"

Block::Block(unsigned int texture, Shader& shader,  Mesh& mesh) {
	this->texture = texture;
	this->shader = &shader;

	this->cubeMesh = &mesh;

	//this->cubeMesh->move(this->Position);
	this->cubeMesh->setOrigin(glm::vec3(1.0f, 1.0f, 1.0f));

	
}

Block::Block(){}

void Block::Draw() {


	//Activate texture for each mesh
	//this->overrideTextureDiffuse->bind(0);
	//this->overrideTextureSpecular->bind(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader->use();

	glBindVertexArray(this->cubeMesh->VAO);


	cubeMesh->setRotation(glm::vec3(0, 0, 0));
	cubeMesh->setPosition(glm::vec3(0, 0, 0));
	cubeMesh->render(shader);

	cubeMesh->setRotation(glm::vec3(0, 0, 0));
	cubeMesh->setPosition(glm::vec3(0, 0, -1));
	cubeMesh->render(shader);

	cubeMesh->setRotation(glm::vec3(0, 90, 0));
	cubeMesh->setPosition(glm::vec3(0.5, 0, 0.5));
	cubeMesh->render(shader); 

	cubeMesh->setRotation(glm::vec3(0, -90, 0));
	cubeMesh->setPosition(glm::vec3(-0.5, 0, 0.5));
	cubeMesh->render(shader);

	cubeMesh->setRotation(glm::vec3(90, 0, 0));
	cubeMesh->setPosition(glm::vec3(0, -0.5, -0.5));
	cubeMesh->render(shader);

	cubeMesh->setRotation(glm::vec3(90, 0, 0));
	cubeMesh->setPosition(glm::vec3(0, -0.5, 0.5));
	cubeMesh->render(shader);
		/*
	cubeMesh->setRotation(glm::vec3(0, -90, 0));
	cubeMesh->render(shader); //Activates shader also

	cubeMesh->setRotation(glm::vec3(0, 0, 90));
	cubeMesh->render(shader); //Activates shader also

	cubeMesh->setRotation(glm::vec3(0, 0, -90));
	cubeMesh->render(shader); //Activates shader also
	*/

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Block::Realese() {
	//cubeMesh->~Mesh();
}

void Block::SetPosition(glm::vec3 pos) {
	this->Position = pos;


	cubeMesh->setPosition(this->Position);
	cubeMesh->setOrigin(this->Position);

}