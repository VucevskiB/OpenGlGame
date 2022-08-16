#pragma once
#include <Tile.hpp>

#include <vector>

class TileMap {
private:
	std::vector<Tile> tiles;
	std::vector<glm::vec3> tiles_position;


public:

	TileMap();

	void AddTile(Tile tile, glm::vec3 position);

	void Draw();

	void GenerateMap();

	void ReleaseData();


};