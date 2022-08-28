#include <TileMap.hpp>

TileMap::TileMap() {

}

void TileMap::AddTile(Tile tile, glm::vec3 position) {
	tile.SetPosition(position);
	this->tiles.push_back(tile);

	block_tile = tile;
}

void TileMap::Draw() {
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
}

void TileMap::GenerateMap() {

	double value[20][20];

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			double nx = x / 20.0f ,
				ny = y / 20.0f ;
			value[y][x] = std::round(noise(nx, ny) * 10);

			tiles_position.push_back(glm::vec3(x*2, value[y][x]*2 ,y * 2));
		}
	}
	std::cout << value;
}

double TileMap::noise(double nx, double ny) { // if using libnoise
  // Rescale from -1.0:+1.0 to 0.0:1.0
	return perlin.octave2D_01(nx, ny, 4) / 2.0;
}

void TileMap::ReleaseData() {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].Realese();
	}
	tiles.clear();
}

