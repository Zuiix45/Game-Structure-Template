#include "Handler.h"

#include "Logger.h"
#include "Files.h"

#include "../util/gl/Shaders.h"
#include "../util/gl/Buffers.h"
#include "../util/gl/DefaultShaders.h"

#include <map>
#include <glad/glad.h>

namespace {
    std::multimap<unsigned int, unsigned int> layers; // layer, id
    std::map<unsigned int, Object*> objectMap; // id, object
    std::map<unsigned int, Shaders*> shaderMap; // id, shaders
    std::map<unsigned int, Sprite*> spriteMap; // id, sprite
    std::map<std::string, std::string> imagePathMap; // name, path

    Buffers* buffers;

    std::string addTextureUniformsToShader(std::string shaderSource, int textureCount) {
        std::string textureUniforms = "";
        std::string applyTextures = "";

        // create required lines to add shader source
        for (int i = 0; i < textureCount; i++) {
            textureUniforms += "uniform sampler2D u_Texture_" + std::to_string(i) + ";\n";
            applyTextures += "texture(u_Texture_" + std::to_string(i) + ", v_TexCoord) * ";
        }

        int mainFuncPos = shaderSource.find("void main() {");
        int outColorPos = shaderSource.find_last_of("FragColor");
        
        int nextNL = shaderSource.find("\n", outColorPos);
        int prevNL = shaderSource.rfind("\n", outColorPos);

        // delete FragColor line
        shaderSource.erase(prevNL, nextNL - prevNL);

        int nl = shaderSource.find("\n", mainFuncPos);

        // insert new lines
        shaderSource.insert(nl, "\n    FragColor = " + applyTextures + "v_Color;");
        shaderSource.insert(mainFuncPos, textureUniforms + "\n");

        return shaderSource;
    }
}

void handler::init(const char* placeholderImagePath) {
    buffers = new Buffers(4, 6);

    saveImagePath("placeholder", placeholderImagePath);
}

unsigned int handler::createObject(unsigned int layer, Object* object) {
    unsigned int id = objectMap.size();

    layers.insert(std::pair<unsigned int, unsigned int>(layer, id));

    objectMap.insert(std::pair<unsigned int, Object*>(id, object));
    shaderMap.insert(std::pair<unsigned int, Shaders*>(id, new Shaders("", ""))); // use default shaders

    return id;
}

Object* handler::deleteObject(unsigned int id) {
    Object* object = objectMap[id];

    // delete id from layers
    for (auto it = layers.begin(); it != layers.end(); it++) {
        if (it->second == id) {
            layers.erase(it);
            break;
        }
    }

    delete objectMap[id];
    objectMap.erase(id);

    delete shaderMap[id];
    shaderMap.erase(id);

    return object;
}

Object* handler::getObject(unsigned int id) {
    return objectMap[id];
}

void handler::setLayer(unsigned int id, unsigned int layer) {
    // delete id from layers
    for (auto it = layers.begin(); it != layers.end(); it++) {
        if (it->second == id) {
            layers.erase(it);
            break;
        }
    }

    layers.insert(std::pair<unsigned int, unsigned int>(layer, id));
}

void handler::drawAllObjects(int windowWidth, int windowHeight) {
    for (auto it = layers.begin(); it != layers.end(); it++) {
        Object* object = objectMap[it->second];
        Shaders* shaders = shaderMap[it->second];

        // activate textures
        if (spriteMap[it->second] != nullptr)
            spriteMap[it->second]->activateTextures();

        // set shader uniforms
        shaders->activate();
        glm::mat4 model = object->getModelMatrix(windowWidth, windowHeight);
        shaders->setUniform("u_Model", (float*)&model, SHADER_MAT4);

        buffers->bind();
        buffers->setVertexData(object->getVertices(), object->getIndices());
        buffers->drawElements();
        buffers->unbind();
    }
}

void handler::changeShaders(unsigned int id, const char* vertexShaderSource, const char* fragmentShaderSource) {
    delete shaderMap[id];

    std::string fragmentShaderSourceStr = std::string(fragmentShaderSource);
    std::string vertexShaderSourceStr = std::string(vertexShaderSource);
    fragmentShaderSourceStr = addTextureUniformsToShader(fragmentShaderSourceStr, spriteMap[id]->getTextureCount());

    shaderMap[id] = new Shaders(vertexShaderSourceStr, fragmentShaderSourceStr);
}

void handler::bindSpriteToObject(unsigned int id, Sprite* sprite) {
    spriteMap[id] = sprite;
    changeShaders(id, defaultVertexShaderSource, defaultFragmentShaderSource);
}

void handler::bindSpriteToObject(unsigned int id, const char* image_name, bool flip) {
    bindSpriteToObject(id, new Sprite(getImagePath(image_name).c_str(), flip));
}

Sprite* handler::getSprite(unsigned int id) {
    return spriteMap[id];
}

void handler::saveImagePath(const char* name, const char* path) {
    if (!files::isFileExist(path)) {
        logger::logError("Image file does not exist: " + std::string(path), 0);
        return;
    }

    imagePathMap[std::string(name)] = files::normalizePath(path);
}

std::string handler::getImagePath(const char* name) {
    if (imagePathMap.find(std::string(name)) == imagePathMap.end()) {
        logger::logError("Image path not found: " + std::string(name), 0);
        return imagePathMap["placeholder"];
    }

    return imagePathMap[name];
}
