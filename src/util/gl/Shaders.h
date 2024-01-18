#pragma once

#include <string>

#define SHADER_FLOAT 2
#define SHADER_VEC2 3
#define SHADER_VEC3 4
#define SHADER_VEC4 5
#define SHADER_MAT2 6
#define SHADER_MAT3 7
#define SHADER_MAT4 8

class Shaders {
public:
    /**
     * @brief Constructs a Shaders object with the given vertex and fragment shader sources.
     * 
     * @param vertexShaderSource The source code of the vertex shader.
     * @param fragmentShaderSource The source code of the fragment shader.
     */
    Shaders(std::string vertexShaderSource, std::string fragmentShaderSource);
    ~Shaders();
    
    /**
     * @brief Activates the shader program.
     * 
     */
    void activate();

    /**
     * Sets the value of a uniform variable in the OpenGL shader program.
     *
     * @param name The name of the uniform variable. (Must match the name in the shader)
     * @param value A pointer to the value to be set
     * @param type The type of the uniform variable. (SHADER_INT, SHADER_FLOAT, SHADER_VEC2, SHADER_VEC3, SHADER_VEC4, SHADER_MAT2, SHADER_MAT3, SHADER_MAT4)
     */
    void setUniform(const char *name, float* value, int type); // change glFloat if necessary

    /**
     * Sets the value of a uniform variable in the OpenGL shader program.
     *
     * @param name The name of the uniform variable. (Must match the name in the shader)
     * @param value The value to be set
     */
    void setUniformInt(const char *name, int value);

private:
    unsigned int m_ShaderProgram;
    unsigned int m_VertexShader;
    unsigned int m_FragmentShader;

    std::string m_VertexShaderSource;
    std::string m_FragmentShaderSource;

    /**
     * @brief Compiles the shaders used by the renderer.
     * 
     * This function is responsible for compiling the shaders used by the renderer.
     * It prepares the shaders for rendering by the OpenGL pipeline.
     */
    void CompileShaders();
};
