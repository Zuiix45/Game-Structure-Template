#include "Buffers.h"

#include "DefaultShaders.h"

#include <glad/glad.h>
#include <glm/gtx/matrix_transform_2d.hpp>

Buffers::Buffers() {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_ebo);
    glGenBuffers(1, &m_vbo);
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

Mesh::Mesh(const char* vertexShaderSource, const char* fragmentShaderSource) {
    m_vertices.push_back({{0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}});
    m_vertices.push_back({{0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}});
    m_vertices.push_back({{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}});
    m_vertices.push_back({{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}});
    m_indices = {0, 1, 3, 1, 2, 3};

    m_buffers = new Buffers();

    m_buffers->bind();
    m_buffers->setVertexData(m_vertices, m_indices);
    m_buffers->unbind();

    std::string vertexSource = vertexShaderSource;
    std::string fragmentSource = fragmentShaderSource;

    if (vertexSource == "") vertexSource = defaultVertexShaderSource;
    if (fragmentSource == "") fragmentSource = defaultFragmentShaderSource;

    m_shaders = new Shaders(vertexSource, fragmentSource);
}

void Mesh::draw() const {
    m_shaders->activate();

    glm::mat3 model = glm::mat3(1.0f);
    model = glm::translate(model, glm::vec2(0.3f, 0.2f));
    model = glm::rotate(model, glm::radians(45.0f));
    model = glm::scale(model, glm::vec2(0.5f, 0.5f));

    m_shaders->setUniform("u_Model", (GLfloat*)&model, SHADER_MAT3);

    m_buffers->bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    m_buffers->unbind();
}
