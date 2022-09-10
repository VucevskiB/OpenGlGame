#pragma once
#include <vector>
#include "Primitives.hpp"
#include "Vertex.hpp"
#include <bitset>

enum BLOCK_TYPE {
	GRASS,
	DIRT,
	STONE
};

static class BlockData {
private:

public:
	static std::vector<Vertex> getBlockData(std::bitset<6> sides, glm::vec3 position, BLOCK_TYPE blockType) {
		Cube cube = Cube();

		std::vector<Vertex> collection;

		//set position
		for (int i = 0; i < cube.vertices.size(); i++) {
			cube.vertices[i].position += position;
		}

		int x = blockType % 8, y = blockType / 8;
		float spriteWidth = 32.0f;
		float sheetWidth = 256.0f;

		
		//set texCords
		for (int i = 0; i < cube.vertices.size(); i++) {
			glm::vec2 texCord = glm::vec2(cube.vertices[i].texcoord);
			texCord.x = ((x + texCord.x) * spriteWidth) / sheetWidth;
			texCord.y = ((y + texCord.y) * spriteWidth) / sheetWidth;

			cube.vertices[i].texcoord = texCord;
		}

		//set active sides
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
		for (int i = 0; i < cube.indices.size(); i++) {
			//collection.push_back(this->cube.vertices[this->cube.indices[i]]);
			collection.push_back(Vertex(cube.vertices[cube.indices[i]]));
		}

		return collection;
	}
};