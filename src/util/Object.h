#pragma once

#include "../sys/Timer.h"
#include "../sys/Events.h"

#include "gl/Shaders.h"
#include "gl/Buffers.h"

#include "Sprite.h"

#include <glm/glm.hpp>
#include <map>
#include <vector>

#define TOP_LEFT_CORNER 0
#define TOP_RIGHT_CORNER 1
#define BOTTOM_LEFT_CORNER 2
#define BOTTOM_RIGHT_CORNER 3
#define ALL_CORNERS 4

class Object {
public:
    /**
     * @brief This class provides a convenient way to represent objects in a 2D space.
     * It stores the object's position (x, y), size (width, height), and rotation angle(Degree).
     */
    Object(float x = 0, float y = 0, float width = 0, float height = 0, float angle = 0);

    virtual void update(float deltaTime) {};
    virtual void events() {};

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    float getAngle() const;

    float* getBounds() const;

    /**
     * @brief Get the color of the object at the specified corner.
     * 
     * @param corner The corner index.
     * @return The color of the object as a glm::vec4.
     */
    glm::vec4 getColor(unsigned int corner) const;

    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);

    /**
     * @brief Sets the rotation of the object.
     * 
     * @param angle The rotation angle in degrees.
     */
    void setRotation(float angle);

    /**
     * Sets the color of the object.
     * 
     * @param r The red component of the color (0.0 - 255.0).
     * @param g The green component of the color (0.0 - 255.0).
     * @param b The blue component of the color (0.0 - 255.0).
     * @param a The alpha component of the color (0.0 - 1.0). Default value is 1.0.
     * @param corner The corner(s) to apply the color to. Default value is ALL_CORNERS(4).
     */
    void setColor(float r, float g, float b, float a = 1.0f, unsigned int corner = ALL_CORNERS);

    /**
     * @brief Sets the Animation for the object.
     * 
     * @param animation A pointer to the Animation object.
     * 
     * @return A pointer to the old Animation object.
     */
    Animation* setAnimation(Animation* animation);

    /**
     * @brief Returns the Animation associated with the object.
     * 
     * @return Pointer to the Animation.
     */
    Animation* getAnimation() const;

    /**
     * @brief This function calculates and returns the model matrix for the object based on its current position, rotation, and scale.
     * The model matrix is a glm::mat4 object that represents the transformation applied to the object in the world space.
     * 
     * @param windowWidth The width of the window in pixels.
     * @param windowHeight The height of the window in pixels.
     * @return The model matrix for the object.
     */
    glm::mat4 getModelMatrix(int windowWidth, int windowHeight) const;

    /**
     * @brief Get the vertices of the object. 
     * The vertices are in the order of top left, top right, bottom left, bottom right. 
     * 
     * @return std::vector<Vertex> The vertices of the object.
     */
    std::vector<Vertex> getVertices() const;

    /**
     * @brief Returns the indices of the object.
     * 
     * @return std::vector<unsigned int> The indices of the object.
     */
    std::vector<unsigned int> getIndices() const;

    void show();
    void hide();

    bool isVisible() const;

protected:
    float x, y, width, height, angle;

    glm::vec4 topLeftColor;
    glm::vec4 topRightColor;
    glm::vec4 bottomLeftColor;
    glm::vec4 bottomRightColor;

private:
    unsigned int startTimerID; // counts the time since the object was created

    Animation* animation;

    bool visible;
};
