#include <Tile.hpp>
#include "OBJ_Loader.h"

Tile::Tile(glm::vec3 position, unsigned int texture, Shader& shader, const char* objFile) {
	Position = position;
	this->texture = texture;
	this->shader = &shader;
	
	std::vector<Vertex> mesh = loadOBJ(objFile);
	this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)));
	

	for (auto& i : this->meshes)
	{
		i->move(this->Position);
		i->setOrigin(glm::vec3(0.f, 0.f, 0.f));
	}
}
Tile::Tile(){}

void Tile::Draw() {

	for (auto& i : this->meshes)
	{
		//Activate texture for each mesh
		//this->overrideTextureDiffuse->bind(0);
		//this->overrideTextureSpecular->bind(1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		i->render(shader); //Activates shader also
	}
}

void Tile::Realese() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Tile::SetPosition(glm::vec3 pos) {
	this->Position = pos;

	for (auto& i : this->meshes)
	{
		i->setPosition(this->Position);
	}
}