#pragma once

#include "Shaders.h"

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
};

class Buffers {
public:
    /**
     * @brief This class provides functionality for managing vertex and index buffers.
     * It allows creating buffers with a specified number of vertices and indices.
     * It also allows setting the vertex data and indices for every Instance.
     * 
     * @param vertexCount The number of vertices to allocate.
     * @param indexCount The number of indices to allocate.
     */
    Buffers(int vertexCount, int indexCount);

    /**
     * @brief Delete All Buffer objects.
     */
    ~Buffers();

    /**
     * Binds the buffer object.
     */
    void bind() const;

    /**
     * @brief Unbinds the buffer object.
     *
     * This function unbinds the buffer object, allowing other buffer objects to be bound in its place.
     */
    void unbind() const;

    /**
     * Sets the vertex data and indices for the buffer.
     * 
     * @param vertices The vector of vertices to set.
     * @param indices The vector of indices to set.
     */
    void setVertexData(Vertex* vertices, int* indices);

    /**
     * @brief Draws the elements using the buffer data.
     */
    void drawElements() const;

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;

    int vertexCount;
    int indexCount;
};
