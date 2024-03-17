#pragma once

#include "../util/Object.h"

class Hitbox : public Object {
    public:
        Hitbox(unsigned int parentID, float relativeX, float relativeY, float width, float height, float angle = 0);

        void draw(int windowWidth, int windowHeight) override;

        void syncCoordsWithParent();
        void syncAngleWithParent();

    private:
        void createVertexData() override;
        void createIndexData() override;

        unsigned int _parentID;

        float _relativeX, _relativeY;

        int showKeyCode;
};