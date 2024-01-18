#include "Shaders.h"

#include "../../sys/Logger.h"

#include <glad/glad.h>

Shaders::Shaders(std::string vertexShaderSource, std::string fragmentShaderSource) {
    m_VertexShaderSource = vertexShaderSource;
    m_FragmentShaderSource = fragmentShaderSource;

    CompileShaders();
}

Shaders::~Shaders() {
    glDeleteProgram(m_ShaderProgram);
}

void Shaders::activate() {
    glUseProgram(m_ShaderProgram);
}

void Shaders::setUniform(const char *name, float* value, int type) {
    int location = glGetUniformLocation(m_ShaderProgram, name);
    
    switch (type) {
        case SHADER_FLOAT:
            glUniform1f(location, ((GLfloat*)value)[0]);
            break;
        case SHADER_VEC2:
            glUniform2fv(location, 1, (GLfloat*)value);
            break;
        case SHADER_VEC3:
            glUniform3fv(location, 1, (GLfloat*)value);
            break;
        case SHADER_VEC4:
            glUniform4fv(location, 1, (GLfloat*)value);
            break;
        case SHADER_MAT2:
            glUniformMatrix2fv(location, 1, GL_FALSE, (GLfloat*)value);
            break;
        case SHADER_MAT3:
            glUniformMatrix3fv(location, 1, GL_FALSE, (GLfloat*)value);
            break;
        case SHADER_MAT4:
            glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)value);
            break;
        default:
            logError("Invalid uniform type", 0);
            break;
    }
}

void Shaders::setUniformInt(const char *name, int value) {
    int location = glGetUniformLocation(m_ShaderProgram, name);
    glUniform1i(location, value);
}

void Shaders::CompileShaders() {
    // Create shaders
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (m_VertexShader == 0 || m_FragmentShader == 0) {
        logError("Failed to create shaders", 0);
        return;
    }

    // Compile shaders
    const char* vertexShaderSource = m_VertexShaderSource.c_str();
    const char* fragmentShaderSource = m_FragmentShaderSource.c_str();

    glShaderSource(m_VertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(m_FragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(m_VertexShader);
    glCompileShader(m_FragmentShader);

    GLint status;

    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint log_length = 0;
        glGetShaderiv(m_VertexShader, GL_INFO_LOG_LENGTH, &log_length);

        GLchar log[log_length];

        glGetShaderInfoLog(m_VertexShader, log_length, &log_length, log);

        for (int i = 0; i < log_length; i++) {
            if (log[i] == '\n') log[i] = ' ';
        }

        std::string errorMsg = "Vertex shader compilation failed: " + std::string(log);

        logError(errorMsg, glGetError());
        return;
    }

    glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint log_length = 0;
        glGetShaderiv(m_FragmentShader, GL_INFO_LOG_LENGTH, &log_length);

        GLchar log[log_length];

        glGetShaderInfoLog(m_FragmentShader, log_length, &log_length, log);

        for (int i = 0; i < log_length; i++) {
            if (log[i] == '\n') log[i] = ' ';
        }

        std::string errorMsg = "Fragment shader compilation failed: " + std::string(log);

        logError(errorMsg, glGetError());
        return;
    }

    // Create shader program
    m_ShaderProgram = glCreateProgram();
    
    if (m_ShaderProgram == 0) {
        logError("Failed to create shader program", glGetError());
        return;
    }

    // Link shader program and attach shaders
    glAttachShader(m_ShaderProgram, m_VertexShader);
    glAttachShader(m_ShaderProgram, m_FragmentShader);

    glLinkProgram(m_ShaderProgram);
    
    glDetachShader(m_ShaderProgram, m_VertexShader);
    glDetachShader(m_ShaderProgram, m_FragmentShader);

    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        logError("Failed to link shader program", glGetError());
        return;
    }

    // Delete shaders
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}
