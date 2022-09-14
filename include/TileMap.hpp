#pragma once
#include <Block.hpp>
#include "PerlinNoise.hpp"
#include "Chunk.hpp"
#include <vector>
#include <bitset>
#include <string>

class TileMap {
private:
	std::vector<Block> tiles;
	std::vector<glm::vec3> tiles_position;


	//TEMP
	unsigned int texture;
	Shader* shader;

	Block block_tile;

	const siv::PerlinNoise::seed_type seed = 123456u;
	const siv::PerlinNoise perlin{ seed };

	int height = 10;
	 int width = 10;

	 std::vector<Chunk> chunks;

	 std::vector<Chunk> generatedChunks;

	 Chunk GenerateMap(int chunkX, int chunkZ);


public:

	TileMap();

	void SetShader(unsigned int texture, Shader& shader);

	void Draw();
	void ReleaseData();

	void CheckValidChunks(int playerX, int playerZ);

	double noise(double nx, double ny);

	void InitChunks();

	double ridgenoise(double nx, double ny);

	void checkClick(glm::vec3 start, glm::vec3 direction, int click);

	Chunk* getChunk(int x, int z);


};