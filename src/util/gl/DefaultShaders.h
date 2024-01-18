#pragma once

namespace {
    const char* defaultVertexShaderSource = R"(
        #version 330 core

        layout (location = 0) in vec3 a_Position;
        layout (location = 1) in vec4 a_Color;
        layout (location = 2) in vec2 a_TexCoord;

        out vec4 v_Color;
        out vec2 v_TexCoord;

        uniform mat4 u_Model;

        void main() {
            gl_Position = u_Model * vec4(a_Position, 1.0);

            v_Color = a_Color;
            v_TexCoord = a_TexCoord;
        }
    )";

    const char* defaultFragmentShaderSource = R"(
        #version 330 core

        in vec4 v_Color;
        in vec2 v_TexCoord;

        out vec4 FragColor;

        void main() {
            FragColor = v_Color;
        }
    )";
}
