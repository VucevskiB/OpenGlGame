#pragma once

#include <vector>

class Chunk {
private:
	std::vector< std::vector< std::vector<int> > > data;
	int startX;
	int startZ;
public:
	Chunk();
	Chunk(std::vector< std::vector< std::vector<int> > > data, int startX, int startZ);
	~Chunk();
	int getData(int x, int y, int z);

	int getStartX();
	int getStartZ();

	bool isNull();


	static const int LIMIT = 16;
};