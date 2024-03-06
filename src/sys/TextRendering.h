#pragma once

#include <string>

namespace text {
    void init(const std::string& fontsDirectory);
    
    unsigned int loadFont(const std::string& name, unsigned int size);

    void destroy();

    void setRendererX(float x);
    void setRendererY(float y);

    void setRendererScale(float scale);
    void setRendererColor(float r, float g, float b, float a = 1.0f);

    void setWindowDimensions(int width, int height);

    void renderText(unsigned int fontID, const std::string& text);
}