#include "TextRendering.h"

#include "Logger.h"
#include "Files.h"

#include "../util/renderer/Shaders.h"
#include "../util/renderer/DefaultShaders.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glad/glad.h>

struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

namespace {
    FT_Library ft;

    std::map<std::string, std::string> fontPathMap; // font name -> font path
    std::map<unsigned int, std::map<char, Character>> fontMap; // font ID -> font

    bool isInitialized;

    glm::vec2 rendererPosition;
    glm::vec4 rendererColor;
    float rendererScale;

    std::unique_ptr<Shaders> shaders;

    unsigned int VAO, VBO;

    int windowWidth, windowHeight;
}

void fonts::init(const std::string& fontsDirectory, const std::string& defaultFontName, unsigned int defaultFontSize) {
    if (FT_Init_FreeType(&ft)) {
        logError("Failed to initialize FreeType library", FREETYPE_INITIALIZATION_FAILED);
        bool isInitialized = false;
    }

    rendererPosition = glm::vec2(0.0f, 0.0f);
    rendererColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    rendererScale = 1.0f;

    windowWidth = 0;
    windowHeight = 0;

    std::vector<std::string> fontPaths = files::getAllFilePaths(fontsDirectory);

    for (const std::string& fontPath : fontPaths) {
        std::string nPath = files::normalizePath(fontPath);
        std::string fontName = files::extractFileName(nPath);
        fontName = fontName.substr(0, fontName.find_last_of('.'));
        fontPathMap[fontName] = nPath;
    }

    shaders = std::make_unique<Shaders>(defaultTextVertexShaderSource, defaultTextFragmentShaderSource);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    isInitialized = true;

    fonts::loadFont(defaultFontName, defaultFontSize);
}

unsigned int fonts::loadFont(const std::string& name, unsigned int size) {
    if (!isInitialized) return 0;

    if (fontPathMap[name].empty()) {
        logError("Font not found: " + name, FONT_NOT_FOUND);
        return 0;
    }

    std::string path = fontPathMap[name];

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face)) {
        logError("Failed to load font: " + name, FONT_LOADING_ERROR);
        return 0;
    }

    FT_Set_Pixel_Sizes(face, 0, size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned int id = fontMap.size() + 1;

    for (unsigned char c = 0; c < 128; c++) {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            logError("Failed to load Glyph: " + c, GLYPH_LOADING_ERROR);
            continue;
        }

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };

        fontMap[id].insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    // destroy FreeType once we're finished
    FT_Done_Face(face);

    return id;
}

void fonts::destroy() {
    FT_Done_FreeType(ft);
}

/////////////////////

void text::setRendererX(float x) { rendererPosition.x = x; }
void text::setRendererY(float y) { rendererPosition.y = y; }
void text::setRendererScale(float scale) { rendererScale = scale; }
void text::setRendererColor(float r, float g, float b, float a) { rendererColor = glm::vec4(r, g, b, a); }

void text::setWindowDimensions(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

void text::renderText(unsigned int fontID, const std::string& text) {
    if (!isInitialized || fontID == 0 || fontMap[fontID].empty()) return;

    glm::vec4 color = { rendererColor.r/255.0f, rendererColor.g/255.0f, rendererColor.b/255.0f, rendererColor.a };
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), 0.0f);

    shaders->activate();
    shaders->setUniform("projection", (float*)&projection, SHADER_MAT4);
    shaders->setUniform("textColor", (float*)&color, SHADER_VEC4);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    float x = rendererPosition.x;
    float y = rendererPosition.y;
    float scale = rendererScale;

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = fontMap[fontID][*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y + (fontMap[fontID]['H'].bearing.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
