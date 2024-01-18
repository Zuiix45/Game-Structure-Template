#pragma once

#include "Shaders.h"

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec2 position;
    glm::vec4 color;
    glm::vec2 texCoord;
};

class Buffers {
public:
    Buffers();

    void bind() const;
    void unbind() const;

    void setVertexData(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
};

/* Temp Class*/
class Mesh {
public:
    Mesh(const char* vertexShaderSource = "", const char* fragmentShaderSource = "");

    void draw() const;

private:
    Shaders* m_shaders;

    Buffers* m_buffers;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};
