#pragma once

#include "../sys/Timer.h"

#include "renderer/Shaders.h"
#include "renderer/Buffers.h"

#include "Animation.h"

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <optional>
#include <memory>

enum class ObjectType {
    STATIC, // only drawable object
    SUB_ENTITY, // not movable but updatable object
    ENTITY, // movable and updatable object
    HITBOX // hitbox object
};

/**
 * @class Object
 * @brief This class provides a convenient way to represent objects in a 2D space.
 * It stores the object's position (x, y), size (width, height), and rotation angle (Degree).
 */
class Object {
public:
    /**
     * @brief Constructs an Object with the specified parameters.
     * 
     * @param x The x-coordinate of the object's position. Default value is 0.
     * @param y The y-coordinate of the object's position. Default value is 0.
     * @param width The width of the object. Default value is 0.
     * @param height The height of the object. Default value is 0.
     * @param angle The rotation angle of the object in degrees. Default value is 0.
     */
    Object(float x = 0, float y = 0, float width = 0, float height = 0, float angle = 0);

    /**
     * @brief Destroys the Object instance.
     */
    ~Object();

    /**
     * @brief Draws the object on the screen. Do not override this function unless you know what you are doing.
     * 
     * @param windowWidth The width of the window.
     * @param windowHeight The height of the window.
     */
    virtual void draw(int windowWidth, int windowHeight);

    /**
     * @brief Gets the x-coordinate of the object's position.
     * 
     * @return The x-coordinate of the object's position.
     */
    float getX() const;

    /**
     * @brief Gets the y-coordinate of the object's position.
     * 
     * @return The y-coordinate of the object's position.
     */
    float getY() const;

    /**
     * @brief Gets the width of the object.
     * 
     * @return The width of the object.
     */
    float getWidth() const;

    /**
     * @brief Gets the height of the object.
     * 
     * @return The height of the object.
     */
    float getHeight() const;

    /**
     * @brief Gets the rotation angle of the object in degrees.
     * 
     * @return The rotation angle of the object in degrees.
     */
    float getAngle() const;

    /**
     * @brief Gets the bounds of the object as an array of floats.
     * The array contains the x-coordinate, y-coordinate, width, and height of the object, in that order.
     * 
     * @return The bounds of the object as an array of floats.
     */
    float* getBounds() const;

    /**
     * @brief Gets the color of the object at the specified corner.
     * 
     * @param vertexIndex The index of vertex in the vertex list.
     * @return The color of the object as a glm::vec4.
     */
    glm::vec4 getColor(unsigned int vertexIndex) const;

    /**
     * @brief Sets the x-coordinate of the object's position.
     * 
     * @param x The new x-coordinate of the object's position.
     */
    void setX(float x);

    /**
     * @brief Sets the y-coordinate of the object's position.
     * 
     * @param y The new y-coordinate of the object's position.
     */
    void setY(float y);

    /**
     * @brief Sets the width of the object.
     * 
     * @param width The new width of the object.
     */
    void setWidth(float width);

    /**
     * @brief Sets the height of the object.
     * 
     * @param height The new height of the object.
     */
    void setHeight(float height);

    /**
     * @brief Sets the rotation angle of the object in degrees.
     * 
     * @param angle The new rotation angle of the object in degrees.
     */
    void setRotation(float angle);

    /**
     * @brief Sets the color of the object.
     * 
     * @param r The red component of the color (0.0 - 255.0).
     * @param g The green component of the color (0.0 - 255.0).
     * @param b The blue component of the color (0.0 - 255.0).
     * @param a The alpha component of the color (0.0 - 1.0).
     * @param vertexIndex The index of vertex in the vertex list.
     */
    void setColor(float r, float g, float b, float a, unsigned int vertexIndex);

    void setAllColors(float r, float g, float b, float a = 1.0f);

    /**
     * @brief loads all sprites and creates the animation of the object.
     * 
     * @param paths The paths to the animation frames.
     * @param fps The frames per second of the animation.
     * @param speed The speed of the animation.
     * @param flip Whether to flip the animation frames horizontally.
     */
    void loadAnimation(std::vector<std::string> paths, int fps, double speed, bool flip);

    /**
     * Sets loaded key frames to the animation.
     *
     * @param keyframes A vector of unsigned integers representing the id of loaded key frames.
     * @param fps The frames per second of the animation.
     * @param speed The speed of the animation.
     */
    void setAnimation(std::vector<unsigned int> keyframes, int fps, double speed);

    /**
     * @brief Checks if the animation of the object is valid.
     * 
     * @return True if the animation is valid, false otherwise.
     */
    bool isAnimationValid();

    /**
     * @brief Closes the animation of the object.
     */
    void closeAnimation();

    /**
     * @brief Opens the animation of the object.
     */
    void openAnimation();

    /**
     * @brief Sets the buffers of the object.
     * 
     * @param mBuffers The buffers to set.
     */
    void setBuffers(std::shared_ptr<Buffers> mBuffers);

    /**
     * @brief Sets the shaders of the object.
     * 
     * @param vertexShaderSource The source code of the vertex shader.
     * @param fragmentShaderSource The source code of the fragment shader.
     */
    void setShaders(const char* vertexShaderSource, const char* fragmentShaderSource);

    /**
     * @brief Shows the object.
     */
    void show();

    /**
     * @brief Hides the object.
     */
    void hide();

    /**
     * @brief Checks if the object is visible.
     * 
     * @return True if the object is visible, false otherwise.
     */
    bool isVisible() const;

    /**
     * @brief Gets the type of the object.
     * 
     * @return The type of the object.
     */
    ObjectType getType() const;

protected:
    /**
     * @brief Gets the model matrix of the object.
     * 
     * @param windowWidth The width of the window.
     * @param windowHeight The height of the window.
     * @return The model matrix of the object as a glm::mat4.
     */
    virtual glm::mat4 getModelMatrix(int windowWidth, int windowHeight) const;

    virtual void createVertexData();
    virtual void createIndexData();

    std::vector<Vertex> vertices; /**< The vertices of the object. */
    std::vector<unsigned int> indices; /**< The indices of the object. */

    float x; /**< The x-coordinate of the object's position. */
    float y; /**< The y-coordinate of the object's position. */
    float width; /**< The width of the object. */
    float height; /**< The height of the object. */
    float angle; /**< The rotation angle of the object in degrees. */

    unsigned int startTimerID; /**< The timer ID that counts the time since the object was created. */

    std::optional<std::unique_ptr<Animation>> animation; /**< The animation of the object. */

    bool visible; /**< Whether the object is visible or not. */

    std::optional<std::shared_ptr<Buffers>> buffers; /**< The buffers of the object. */
    std::optional<std::shared_ptr<Shaders>> shaders; /**< The shaders of the object. */

    bool animationClosed; /**< Whether the animation of the object is closed or not. */

    ObjectType type; /**< The type of the object. */
};
