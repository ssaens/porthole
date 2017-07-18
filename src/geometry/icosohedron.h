//
// Created by Dillon Yao on 5/6/17.
//

#ifndef UNISIM_GEOMETRY_H
#define UNISIM_GEOMETRY_H

#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include "mesh.h"

const float PHI = 1.61803398875f;

const int NUM_ICOSOHEDRON_VERTICES = 12;
const glm::vec3 ICOSOHEDRON_VERTICES[12] = {
        glm::vec3(-1.0f, PHI, 0.0f),
        glm::vec3(1.0f, PHI, 0.0f),
        glm::vec3(-1.0f, -PHI, 0.0f),
        glm::vec3(1.0f, -PHI, 0.0f),

        glm::vec3(0.0f, -1.0f, PHI),
        glm::vec3(0.0f, 1.0f, PHI),
        glm::vec3(0.0f, -1.0, -PHI),
        glm::vec3(0.0f, 1.0f, -PHI),

        glm::vec3(PHI, 0.0f, -1.0f),
        glm::vec3(PHI, 0.0f, 1.0f),
        glm::vec3(-PHI, 0.0f, -1.0f),
        glm::vec3(-PHI, 0.0, 1.0f)
};

const int NUM_ICOSOHEDRON_INDICES = 60;
const uint32_t ICOSOHEDRON_INDICES[60] = {
        0, 11, 5,
        0, 5, 1,
        0, 1, 7,
        0, 7, 10,
        0, 10, 11,

        1, 5, 9,
        5, 11, 4,
        11, 10, 2,
        10, 7, 6,
        7, 1, 8,

        3, 9, 4,
        3, 4, 2,
        3, 2, 6,
        3, 6, 8,
        3, 8, 9,

        4, 9, 5,
        2, 4, 11,
        6, 2, 10,
        8, 6, 7,
        9, 8, 1
};

class Vec3KeyFuncs {
public:
    size_t operator()(const glm::vec3 &k) const {
        return std::hash<float>()(k.x) ^ std::hash<float>()(k.y) ^ std::hash<float>()(k.z);
    }

    bool operator()(const glm::vec3 &a, const glm::vec3 &b) const {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

inline glm::vec3 midpoint(glm::vec3 v1, glm::vec3 v2) {
    return glm::normalize(0.5f * (v1 + v2));
}

void generate_icososphere_mesh(size_t num_subdivisions, std::vector<uint32_t>& indices, std::vector<glm::vec3>& vertices) {
    std::vector<uint32_t> new_indices;
    new_indices.reserve(256);

    std::unordered_map<glm::vec3, uint32_t, Vec3KeyFuncs, Vec3KeyFuncs> vertex_lookup;
    indices.resize(NUM_ICOSOHEDRON_INDICES);

    for (uint32_t i = 0; i < NUM_ICOSOHEDRON_INDICES; ++i) {
        indices[i] = ICOSOHEDRON_INDICES[i];
    }
    vertices.resize(NUM_ICOSOHEDRON_VERTICES);
    for (uint32_t i = 0; i < NUM_ICOSOHEDRON_VERTICES; ++i) {
        vertices[i] = glm::normalize(ICOSOHEDRON_VERTICES[i]);
        vertex_lookup[glm::normalize(ICOSOHEDRON_VERTICES[i])] = i;
    }

    for (size_t i = 0; i < num_subdivisions; ++i) {
        for (size_t j = 0; j < indices.size(); j += 3) {
            glm::vec3 v1 = vertices[indices[j]];
            glm::vec3 v2 = vertices[indices[j + 1]];
            glm::vec3 v3 = vertices[indices[j + 2]];

            glm::vec3 mp12 = midpoint(v1, v2);
            glm::vec3 mp23 = midpoint(v2, v3);
            glm::vec3 mp13 = midpoint(v1, v3);

            uint32_t mp12_ind, mp23_ind, mp13_ind;

            auto iter = vertex_lookup.find(mp12);
            if (iter != vertex_lookup.end()) {
                mp12_ind = iter->second;
            } else {
                mp12_ind = (uint32_t) vertices.size();
                vertices.push_back(mp12);
                vertex_lookup[mp12] = mp12_ind;
            }

            iter = vertex_lookup.find(mp23);
            if (iter != vertex_lookup.end()) {
                mp23_ind = iter->second;
            } else {
                mp23_ind = (uint32_t) vertices.size();
                vertices.push_back(mp23);
                vertex_lookup[mp23] = mp23_ind;
            }

            iter = vertex_lookup.find(mp13);
            if (iter != vertex_lookup.end()) {
                mp13_ind = iter->second;
            } else { // Not in the map
                mp13_ind = (uint32_t) vertices.size();
                vertices.push_back(mp13);
                vertex_lookup[mp13] = mp13_ind;
            }

            new_indices.push_back(indices[j]);
            new_indices.push_back(mp12_ind);
            new_indices.push_back(mp13_ind);

            new_indices.push_back(mp12_ind);
            new_indices.push_back(indices[j + 1]);
            new_indices.push_back(mp23_ind);

            new_indices.push_back(mp13_ind);
            new_indices.push_back(mp23_ind);
            new_indices.push_back(indices[j + 2]);

            new_indices.push_back(mp12_ind);
            new_indices.push_back(mp23_ind);
            new_indices.push_back(mp13_ind);
        }
        indices.swap(new_indices);
        new_indices.clear();
    }
}

#endif //UNISIM_GEOMETRY_H
