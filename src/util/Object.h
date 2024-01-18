#pragma once

#include "gl/Shaders.h"
#include "gl/Buffers.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    Object(float x, float y, float width, float height, float angle);

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    float getAngle() const;

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

private:
    float x, y, width, height, angle;

    glm::vec4 topLeftcolor;
    glm::vec4 topRightcolor;
    glm::vec4 bottomLeftcolor;
    glm::vec4 bottomRightcolor;
};
