#include <TileMap.hpp>


TileMap::TileMap() {
}

void TileMap::AddTile(unsigned int texture, Shader& shader) {
	
	this->texture = texture;
	this->shader = &shader;
	
	//this->tiles.push_back(tile);

	//block_tile = tile;
}

//void TileMap::UpdateChunkData() {

//}

void TileMap::Draw() {
	/*
	std::bitset<6> sides;
	sides.set();

	sides.reset(0);
	block_tile.setActiveSides(sides);
	block_tile.SetPosition(glm::vec3(1.0f,1.0f,1.0f));
	block_tile.Draw();

	sides.set();

	sides.reset(1);
	block_tile.setActiveSides(sides);
	block_tile.SetPosition(glm::vec3(1.0f, 1.0f, 3.0f));
	block_tile.Draw();
	
	for (int i = 0; i < tiles_position.size(); i++) {
		for (int j = 0; j < 10; j++) {
			glm::vec3 pos = tiles_position[i];
			pos.y -= j*2;
			if (pos.y < -5) {
				break;
			}

			block_tile.SetPosition(pos);
			block_tile.Draw();
		}
		
	}
	*/

	
	for (int i = 0; i < 16; i++) {
		Chunk chunk = chunks[i];

		if (chunk.isNull()) {
			continue;
		}

		chunk.Draw();
	}
	
}
void TileMap::InitChunks() {
	for (int x = 0; x < 4; x++) {
		for (int z = 0; z < 4; z++) {
			chunks[x*4 + z] = GenerateMap(x * 16 - 32, z * 16 - 32);
		}
	}
}

void TileMap::CheckValidChunks(int playerX, int playerZ) {
	for (int i = 0; i < 16; i++) {

		if (chunks[i].isNull()) {
			continue;
		}

		if (chunks[i].getStartX() + Chunk::LIMIT * 2 < playerX) {
			//delete
			chunks[i] = GenerateMap(chunks[i].getStartX() + Chunk::LIMIT * 4, chunks[i].getStartZ());
			continue;
		}
		if (chunks[i].getStartX() - Chunk::LIMIT  > playerX) {
			//delete
			chunks[i] = GenerateMap(chunks[i].getStartX() - Chunk::LIMIT * 4, chunks[i].getStartZ());
			continue;
		}
		if (chunks[i].getStartZ() + Chunk::LIMIT * 2 < playerZ) {
			//delete
			chunks[i] = GenerateMap(chunks[i].getStartX(), chunks[i].getStartZ() + Chunk::LIMIT * 4);
			continue;
		}
		if (chunks[i].getStartZ() - Chunk::LIMIT > playerZ) {
			//delete
			chunks[i] = GenerateMap(chunks[i].getStartX(), chunks[i].getStartZ() - Chunk::LIMIT * 4);
			continue;
		}

	}
}

Chunk TileMap::GenerateMap(int chunkX, int chunkZ) {
	double value[16][16];

	std::vector< std::vector< std::vector<int> > > data;

	for (int y = 0; y < Chunk::LIMIT; y++) {

		std::vector< std::vector<int> > line;

		for (int x = 0; x < Chunk::LIMIT; x++) {
			double nx = (double)x / 16.0,
				ny = (double)y / 16.0;

			value[y][x] = std::round(noise(nx + chunkX/ Chunk::LIMIT, ny + chunkZ/Chunk::LIMIT) * 10); // this value is height

			//tiles_position.push_back(glm::vec3(x*2, value[y][x]*2 ,y * 2));

			std::vector<int> column;
			for (int i = 0; i < 16; i++) {
				if (i < value[y][x])
					column.push_back(1);
				else
					column.push_back(0);

			}

			line.push_back(column);
		}

		data.push_back(line);
	}

	return Chunk(data, chunkX, chunkZ, *shader);
	//std::cout << value;
	
}

double TileMap::noise(double nx, double ny) { // if using libnoise
  // Rescale from -1.0:+1.0 to 0.0:1.0
	return perlin.octave2D_01(nx, ny,4);
}

void TileMap::ReleaseData() {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].Realese();
	}
	tiles.clear();
}

