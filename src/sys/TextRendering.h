#pragma once

#include <string>

#define DEF_FONT 1

namespace fonts {
    void init(const std::string& fontsDirectory, const std::string& defaultFontName, unsigned int defaultFontSize);
    
    unsigned int loadFont(const std::string& name, unsigned int size);

    void destroy();
}

namespace text {
    void setRendererX(float x);
    void setRendererY(float y);

    void setRendererScale(float scale);
    void setRendererColor(float r, float g, float b, float a = 1.0f);

    void renderText(unsigned int fontID, const std::string& text); // TODO: fix memory allocation
}
