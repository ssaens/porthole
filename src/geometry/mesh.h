//
// Created by Dillon Yao on 5/7/17.
//

#ifndef UNISIM_MESH_H
#define UNISIM_MESH_H

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 n;
    glm::vec3 tex;
};

class Mesh {
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    void init();

public:
    uint32_t VAO, VBO, EBO;

    Mesh();

    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

    void set_geometry(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

    void render();
};

#endif //UNISIM_MESH_H
