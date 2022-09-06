#include "Chunk.hpp"

Chunk::Chunk(std::vector< std::vector< std::vector<int> > > data, int startX, int startZ) {
	this->data = data;
	this->startX = startX;
	this->startZ = startZ;
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
