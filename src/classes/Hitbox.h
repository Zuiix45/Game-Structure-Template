#pragma once

#include "../util/Object.h"

/**
 * @brief This class represents a hitbox object.
 * Hitbox objects are virtual objects that are used to detect collision.
 * 
 */
class Hitbox : public Object {
    public:
        Hitbox(unsigned int parentID, float relativeX, float relativeY, float width, float height, float angle = 0);

        void draw(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) override;

        void syncCoordsWithParent();
        void syncAngleWithParent();

    private:
        void createVertexData() override;
        void createIndexData() override;

        unsigned int _parentID;

        float _relativeX, _relativeY;

        int showKeyCode;
};