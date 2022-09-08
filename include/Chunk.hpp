#pragma once

#include <vector>
#include <Block.hpp>

class Chunk {
private:
	std::vector< std::vector< std::vector<int> > > data;
	std::vector< std::vector< std::vector<Block> > > blocks;

	int startX;
	int startZ;
	Shader* shader;
	Mesh* mesh;

public:
	Chunk();
	Chunk(std::vector< std::vector< std::vector<int> > > data, int startX, int startZ, Shader& shader);
	~Chunk();
	int getData(int x, int y, int z);

	int getStartX();
	int getStartZ();

	bool isNull();

	std::vector<Vertex> getBlockData(std::bitset<6> sides, glm::vec3 position);

	void generateBlocks();

	void Draw();

	static const int LIMIT = 16;
};