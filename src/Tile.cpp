#include <Tile.hpp>
#include "OBJ_Loader.h"

Tile::Tile(glm::vec3 position, unsigned int texture, Shader& shader, const char* objFile) {
	Position = position;
	this->texture = texture;
	this->shader = &shader;
	/*
	VAO = -1;
	VBO = -1;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
		(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
		(void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	*/

	////

	objl::Loader Loader;
	//bool loadout = Loader.LoadFile(objFile);
	bool loadout = false;
	if (loadout) {
		std::vector<Vertex> mesh;
		auto loaded = Loader.LoadedMeshes[0].Vertices;

		for (int i = 0; i < loaded.size(); i++) {
			Vertex v;
			v.position = glm::vec3(loaded[i].Position.X, loaded[i].Position.Y, loaded[i].Position.Z);
			v.normal = glm::vec3(loaded[i].Normal.X, loaded[i].Normal.Y, loaded[i].Normal.Z);
			v.texcoord = glm::vec2(loaded[i].TextureCoordinate.X, loaded[i].TextureCoordinate.Y);
			mesh.push_back(v);
		}

		this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)));

	}

	
	std::vector<Vertex> mesh = loadOBJ(objFile);
	this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)));
	

	for (auto& i : this->meshes)
	{
		i->move(this->Position);
		i->setOrigin(this->Position);
	}
}


void Tile::Draw() {
	/*
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, Position);

	/// <summary>
	///  Transforamtion math idk
	/// </summary>

	shader->use();
	shader->setMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	if (this->nrOfIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
	else
		glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
		*/

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

}