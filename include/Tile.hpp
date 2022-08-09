#ifndef TILE_H
#define TILE_H

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader.hpp>

#include <vector>
#include <Vertex.hpp>
#include <OBJLoader.hpp>
#include "Mesh.hpp"

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


class Tile {
public:
    glm::vec3 Position;


    Tile(glm::vec3 position,unsigned int texture, Shader& shader, const char* objFile);
    void Draw();
    void Realese();
    void initVAO();

    void SetPosition(glm::vec3 pos);

private:
    unsigned int texture;
    Shader* shader;
    GLuint VBO, VAO,  EBO;

    std::vector<Mesh*> meshes;

};

#endif