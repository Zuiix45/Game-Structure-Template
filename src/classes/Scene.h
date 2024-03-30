#pragma once

#include <map>

class Scene {
public:
    Scene();

    virtual void update(double elapsedTime) = 0;
    virtual void events() = 0;

    /**
     * @brief Returns the elapsed time since the last execution of this object in the last frame.
     * It is used for calculating elapsed time for "update" function.
     * WARNING: This function is called automatically per frame by the engine.
     * 
     * @return double elapsed time in milliseconds
     */
    double getFrameTime();

    void addOBject(unsigned int layer, unsigned int objID);

    std::multimap<unsigned int, unsigned int> getRenderingQueue();

protected:
    std::multimap<unsigned int, unsigned int> renderingQueue; /**< This will sort the queue by layers */

private:
    double loopTimer;
};