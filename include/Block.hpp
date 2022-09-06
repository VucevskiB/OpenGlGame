#ifndef BLOCK_H
#define BLOCK_H

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader.hpp>

#include <vector>
#include <Vertex.hpp>
#include <OBJLoader.hpp>
#include "Mesh.hpp"
#include <bitset>

const float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f,  0.0f, -0.5f,  0.0f,  0.0f,  -1.0f,     0.0f,  0.0f,  
    0.5f,   0.0f, -0.5f,  0.0f,  0.0f,  -1.0f,     0.0f,  0.0f,  
    0.5f,  0.5f,  -0.5f,  0.0f,  0.0f,  -1.0f,     0.0f,  0.0f,  
    0.5f,  0.5f,  -0.5f,  0.0f,  0.0f,  -1.0f,     0.0f,  0.0f,
    -0.5f, 0.5f,  -0.5f,  0.0f,  0.0f,  -1.0f,     0.0f,  0.0f,
    -0.5f, 0.0f, -0.5f,  0.0f,  0.0f,  -1.0f,      0.0f,  0.0f,
                                                          
    -0.5f, 0.0f, 0.5f,   0.0f,  0.0f,  1.0f,       0.0f,  0.0f,
    0.5f,  0.0f, 0.5f,   0.0f,  0.0f,  1.0f,       0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,   0.0f,   0.0f, 1.0f,      0.0f,  0.0f,  
    0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,      0.0f,  0.0f,  
    -0.5f, 0.5f,  0.5f,   0.0f,  0.0f,  1.0f,      0.0f,  0.0f,
    -0.5f, 0.0f, 0.5f,   0.0f,  0.0f,  1.0f,       0.0f,  0.0f,
                                                          
    -0.5f, 0.5f,  0.5f,   -1.0f, 0.0f,  0.0f,      0.0f, 0.0f,  
    -0.5f, 0.5f, -0.5f,   -1.0f, 0.0f,  0.0f,      0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,  -1.0f, 0.0f,  0.0f,       0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,  -1.0f, 0.0f,  0.0f,       0.0f, 0.0f,
    -0.5f, 0.0f, 0.5f,   -1.0f, 0.0f,  0.0f,       0.0f, 0.0f,
    -0.5f, 0.5f,  0.5f,   -1.0f, 0.0f,  0.0f,      0.0f, 0.0f,

    0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,     0.0f,  0.0f,  
    0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,     0.0f,  0.0f,  
    0.5f,  0.0f, -0.5f,   1.0f,  0.0f,  0.0f,      0.0f,  0.0f,
    0.5f,  0.0f, -0.5f,   1.0f,  0.0f,  0.0f,      0.0f,  0.0f,
    0.5f,  0.0f, 0.5f,    1.0f,  0.0f,  0.0f,      0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,     0.0f,  0.0f,

    -0.5f, 0.0f, -0.5f,   0.0f,  -1.0f, 0.0f,      0.0f,  0.0f,
    0.5f,  0.0f, -0.5f,   0.0f,  -1.0f, 0.0f,      0.0f,  0.0f,
    0.5f,  0.0f, 0.5f,    0.0f,  -1.0f, 0.0f,      0.0f,  0.0f,
    0.5f,  0.0f, 0.5f,    0.0f,  -1.0f, 0.0f,      0.0f,  0.0f,
    -0.5f, 0.0f, 0.5f,    0.0f,  -1.0f, 0.0f,      0.0f,  0.0f,
    -0.5f, 0.0f, -0.5f,   0.0f,  -1.0f, 0.0f,      0.0f,  0.0f,

    -0.5f, 0.5f,  -0.5f,   0.0f,  1.0f,  0.0f,      0.0f,  1.0f,  
    0.5f,  0.5f,  -0.5f,   0.0f,  1.0f,  0.0f,      1.0f,  1.0f,  
    0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,      1.0f,  0.0f,  
    0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,      1.0f,  0.0f,  
    -0.5f, 0.5f,  0.5f,    0.0f,  1.0f,  0.0f,      0.0f,  0.0f,
    -0.5f, 0.5f,  -0.5f,   0.0f,  1.0f,  0.0f,       0.0f,  1.0f };


class Block {
public:
    glm::vec3 Position;

    Block();

    Block(unsigned int texture, Shader& shader, Mesh& mesh);
    void Draw();
    void Realese();
    void initVAO();

    void SetPosition(glm::vec3 pos);
    void setActiveSides(std::bitset<6> sides);

private:
    unsigned int texture;

    Shader* shader;

    Mesh* cubeMesh;

    std::bitset<6> sides;

    Quad quad;

};

#endif