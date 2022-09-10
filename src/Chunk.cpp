#include "Chunk.hpp"

Chunk::Chunk(std::vector< std::vector< std::vector<int> > > data, int startX, int startZ, Shader& shader) {
	this->data = data;
	this->startX = startX;
	this->startZ = startZ;
	this->shader = &shader;

	generateBlocks();
}
void Chunk::generateBlocks() {
	std::vector<Vertex> chunk_data;

	for (int x = 0; x < Chunk::LIMIT; x++) {
		std::vector< std::vector<Block> > line;

		for (int z = 0; z < Chunk::LIMIT; z++) {
			std::vector<Block> column;


			for (int y = 0; y < Chunk::LIMIT * 2; y++) {

				if (getData(x, y, z) == 0) {
					continue;
				}

				//get soroundings
				std::bitset<6> sides;
				sides.set();

				if (getData(x, y, z + 1) != 0) {
					sides.reset(0);
				}

				if (getData(x, y, z - 1) != 0) {
					sides.reset(1);
				}

				if (getData(x + 1, y, z) != 0) {
					sides.reset(2);
				}
				if (getData(x - 1, y, z) != 0) {
					sides.reset(3);
				}
				if (getData(x, y + 1, z) != 0) {
					sides.reset(4);
				}
				if (getData(x, y - 1, z) != 0) {
					sides.reset(5);
				}

				glm::vec3 position = glm::vec3(x + getStartX(), y, z + getStartZ());

				//Block block = Block(sides, *shader, position);

				//column.push_back(block);

				//std::vector<Vertex> data = getBlockData(sides, position);
				BLOCK_TYPE blockType;
				if (sides[4]) {
					blockType = GRASS;
				}
				else {
					blockType = DIRT;
				}

				std::vector<Vertex> data = BlockData::getBlockData(sides, position, blockType);

				chunk_data.insert(chunk_data.end(), data.begin(), data.end());

			}
			//line.push_back(column);
		}
		//blocks.push_back(line);

	}

	this->mesh = new Mesh(chunk_data.data(), chunk_data.size(), NULL, 0, glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f));
}

std::vector<Vertex> Chunk::getBlockData(std::bitset<6> sides, glm::vec3 position) {
	Cube cube = Cube();

	std::vector<Vertex> collection;

	//set position
	for (int i = 0; i < cube.vertices.size(); i++) {
		cube.vertices[i].position += position;
	}

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

Chunk::Chunk(){

	data = {};
}
Chunk::~Chunk() {
	data.clear();
}

int Chunk::getData(int x, int y, int z) {
	if (x >= LIMIT || y >= LIMIT || z >= LIMIT || x < 0 || y < 0 || z < 0) {
		return 0;
	}

	return data[x][z][y];
}
int Chunk::getStartX() {
	return startX;
}

bool Chunk::isNull() {
	return data.empty();
}

int Chunk::getStartZ() {
	return startZ;
}

void Chunk::Draw() {

	mesh->render(shader);

	return;
	for (int x = 0; x < blocks.size(); x++) {
		
		for (int z = 0; z < blocks[x].size(); z++) {
		
			for (int y = 0; y < blocks[x][z].size(); y++) {

					blocks[x][z][y].Draw();

			}
		}

	}
}
