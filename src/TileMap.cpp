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
		if (chunks[i].getStartX() - Chunk::LIMIT*2  > playerX) {
			//delete
			chunks[i] = GenerateMap(chunks[i].getStartX() - Chunk::LIMIT * 4, chunks[i].getStartZ());
			continue;
		}
		if (chunks[i].getStartZ() + Chunk::LIMIT * 2 < playerZ) {
			//delete
			chunks[i] = GenerateMap(chunks[i].getStartX(), chunks[i].getStartZ() + Chunk::LIMIT * 4);
			continue;
		}
		if (chunks[i].getStartZ() - Chunk::LIMIT * 2 > playerZ) {
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

			double nx = (double)(x + (double)chunkZ ) / 16.0f,
				ny = (double)(y + (double)chunkX ) / 16.0f;

			double e0 = 1 * ridgenoise(1 * nx, 1 * ny);
			double  e1 = 0.5 * ridgenoise(2 * nx, 2 * ny) * e0;
			double e2 = 0.25 * ridgenoise(4 * nx, 4 * ny) * (e0 + e1);
			double e = (e0 + e1 + e2) / (1 + 0.5 + 0.25);
			e = std::pow(e, 4);
			value[y][x] = std::round(e * 20) / 20.0f;

			//value[y][x] = std::round(noise(nx ,ny ) * 10); // this value is height

			//tiles_position.push_back(glm::vec3(x*2, value[y][x]*2 ,y * 2));

			std::vector<int> column;
			for (int i = 0; i < 32; i++) {
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

	return perlin.noise2D_01(nx, ny) / 2;
}
double TileMap::ridgenoise(double nx, double ny) {
	return 2 * (std::abs(perlin.noise2D_01(nx, ny)));
}

void TileMap::ReleaseData() {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].Realese();
	}
	tiles.clear();
}

