#pragma once
#include <vector>
#include "Primitives.hpp"
#include "Vertex.hpp"
#include <bitset>
#include <deque>

enum BLOCK_TYPE {
	GRASS,
	DIRT,
	STONE,
	WATER,
	SAND
};

static class BlockData {
private:

public:
	static std::deque<Vertex> getBlockData(std::bitset<6> sides, glm::vec3 position, BLOCK_TYPE blockType) {
		Cube cube = Cube();

		std::deque<Vertex> collection;

		//set position
		for (int i = 0; i < cube.vertices.size(); i++) {
			cube.vertices[i].position += position;

			if (blockType == WATER) {
				cube.vertices[i].position -= glm::vec3(0, 0.2f, 0);
			}
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
		if (blockType == WATER) {
			sides.reset();
			sides.set(4);
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
			if (blockType == WATER) {
				collection.emplace_back(Vertex(cube.vertices[cube.indices[i]]));

			}
			else {
				collection.emplace_front(Vertex(cube.vertices[cube.indices[i]]));
			}
		}

		return collection;
	}
};