#include "Buffers.h"

#include "../../sys/Logger.h"

#include <glad/glad.h>

Buffers::Buffers(int vertexCount, int indexCount) 
            : vertexCount(vertexCount), indexCount(indexCount) {

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_ebo);
    glGenBuffers(1, &m_vbo);

    bind();

    // Allocate Vram for Buffer data
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    // Allocate Vram for Index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);

    unbind();
}

Buffers::~Buffers() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_ebo);
    glDeleteBuffers(1, &m_vbo);
}

void Buffers::bind() const {
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

void Buffers::unbind() const {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffers::setVertexData(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    if (vertices.size() != vertexCount) {
        logError("Vertex count mismatch: " + std::to_string(vertices.size()) + " != " + std::to_string(vertexCount), 0);
        return;
    }
    
    if (indices.size() != indexCount) {
        logError("Index count mismatch: " + std::to_string(indices.size()) + " != " + std::to_string(indexCount), 0);
        return;
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), &indices[0]);
}

void Buffers::drawElements() const {
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}