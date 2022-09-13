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

	for (int i = 0; i < 36; i++) {
		Chunk chunk = chunks[i];

		if (chunk.isNull()) {
			continue;
		}

		chunk.Draw();
	}
	
}
void TileMap::InitChunks() {
	for (int x = 0; x < 6; x++) {
		for (int z = 0; z < 6; z++) {
			chunks.push_back(GenerateMap(x * 16 - 48, z * 16 - 48));
		}
	}
}

void TileMap::CheckValidChunks(int playerX, int playerZ) {
	for (int i = 0; i < 36; i++) {

		if (chunks[i].isNull()) {
			continue;
		}

		if (chunks[i].getStartX() + Chunk::LIMIT * 3 < playerX) {
			//delete
			chunks[i].DeleteMesh();
			chunks[i] = GenerateMap(chunks[i].getStartX() + Chunk::LIMIT * 6, chunks[i].getStartZ());
			break;
		}
		if (chunks[i].getStartX() - Chunk::LIMIT*3  > playerX) {
			//delete
			chunks[i].DeleteMesh();
			chunks[i] = GenerateMap(chunks[i].getStartX() - Chunk::LIMIT * 6, chunks[i].getStartZ());
			break;
		}
		if (chunks[i].getStartZ() + Chunk::LIMIT * 3 < playerZ) {
			//delete
			chunks[i].DeleteMesh();
			chunks[i] = GenerateMap(chunks[i].getStartX(), chunks[i].getStartZ() + Chunk::LIMIT * 6);
			break;
		}
		if (chunks[i].getStartZ() - Chunk::LIMIT * 3 > playerZ) {
			//delete
			chunks[i].DeleteMesh();
			chunks[i] = GenerateMap(chunks[i].getStartX(), chunks[i].getStartZ() - Chunk::LIMIT * 6);
			break;
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
			e = std::pow(e, 3);
			value[y][x] = std::round(e * 20) / 20.0f + 1;

			//value[y][x] = std::round(noise(nx ,ny ) * 10); // this value is height

			//tiles_position.push_back(glm::vec3(x*2, value[y][x]*2 ,y * 2));

			std::vector<int> column;
			for (int i = 0; i < 32; i++) {
				if (i < value[y][x]) {
					if (i < value[y][x] - 2) {
						column.push_back(3); // stone
					}
					else { 
						if ((i + 1) >= value[y][x]) {
							column.push_back(1); // grass
						}
						else {
							column.push_back(2); // dirt
						}
					}
				}
				else { // empty/ water
					column.push_back(0); // vazduh
				}

			}

			line.push_back(column);
		}

		data.push_back(line);
	}

	return Chunk(data, chunkX, chunkZ, *shader);
	//std::cout << value;
	
}
template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

void TileMap::checkClick(glm::vec3 start, glm::vec3 direction, int click) {
	glm::vec3 ray_pos = start;

	for (int i = 0; i < 10; i++) {
		ray_pos = ray_pos + direction;


		int x = std::round(ray_pos.x);
		int y = std::round(ray_pos.y);
		int z = std::round(ray_pos.z);

		Chunk* chunk =  getChunk(x, z);

		//chunk->getData(x, y, z);
		int x_chunk = x - chunk->getStartX();
		int z_chunk = z - chunk->getStartZ();

		if (chunk->getData(x_chunk, y, z_chunk) != 0) {

			if (click == 0) {
				chunk->deleteBlock(x_chunk, y, z_chunk);
				break;
			}
			else {

				glm::vec3 before = ray_pos - direction;
				x = std::round(before.x);
				y = std::round(before.y);
				z = std::round(before.z);

				x_chunk = x - chunk->getStartX();
				z_chunk = z - chunk->getStartZ();

				chunk->placeBlock(x_chunk, y, z_chunk);
				break;
			}


		}
	}
}

Chunk* TileMap::getChunk(int x, int z) {

	for (int i = 0; i < chunks.size(); i++) {
		if (chunks[i].getStartX() <= x && x < chunks[i].getStartX() + 16) {
			if (chunks[i].getStartZ() <= z && z < chunks[i].getStartZ() + 16) {
				return &chunks[i];
			}
		}
	}
}


double TileMap::noise(double nx, double ny) { // if using libnoise
  // Rescale from -1.0:+1.0 to 0.0:1.0

	return perlin.noise2D_01(nx, ny) ;
}
double TileMap::ridgenoise(double nx, double ny) {
	return 2 * (std::abs(perlin.noise2D_01(nx, ny)) );
}

void TileMap::ReleaseData() {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].Realese();
	}
	tiles.clear();
}

