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
uniform mat4 u_View;

void main() {
    gl_Position = u_View * u_Model * vec4(a_Position, 1.0);

    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
}
    )";

    const char* defaultCameraVertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;

out vec4 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);

    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
}
    )";

    const char* defaultFragmentShaderSource = R"(
#version 330 core

in vec4 v_Color;
in vec2 v_TexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main() {
    FragColor = texture(u_Texture, v_TexCoord) * v_Color;
}
    )";

    const char* defaultNoTextureFragmentShaderSource = R"(
#version 330 core

in vec4 v_Color;

out vec4 FragColor;

void main() {
    FragColor = v_Color;
}
    )";

    const char* defaultTextVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
    )";

    const char* defaultTextFragmentShaderSource = R"(
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main() {    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = textColor * sampled;
}
    )";
} // namespace defaultShaders