#include <TileMap.hpp>

TileMap::TileMap() {

}
void TileMap::AddTile(Tile tile, glm::vec3 position) {
	tile.SetPosition(position);
	this->tiles.push_back(tile);
}

void TileMap::Draw() {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].Draw();
	}
}

void TileMap::GenerateMap() {

}

void TileMap::ReleaseData() {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].Realese();
	}
	tiles.clear();
}

