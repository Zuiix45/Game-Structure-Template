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

void Buffers::setVertexData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    if (vertices.size() == 0 || indices.size() == 0) {
        logError("Vertices or indices are nullptr", VERTEX_OR_INDEX_NULLPTR);
        return;
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * sizeof(Vertex), &vertices[0]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexCount * sizeof(unsigned int), &indices[0]);
}

void Buffers::drawElements() const {
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
