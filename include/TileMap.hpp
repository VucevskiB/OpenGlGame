#pragma once
#include <Tile.hpp>
#include "PerlinNoise.hpp"

#include <vector>

class TileMap {
private:
	std::vector<Tile> tiles;
	std::vector<glm::vec3> tiles_position;

	Tile block_tile;

	const siv::PerlinNoise::seed_type seed = 123456u;
	const siv::PerlinNoise perlin{ seed };

	 int height = 10;
	 int width = 10;

public:

	TileMap();

	void AddTile(Tile tile, glm::vec3 position);

	void Draw();

	void GenerateMap();

	void ReleaseData();

	double noise(double nx, double ny);


};