#pragma once

class Scene {
public:
    Scene();

    virtual void update(double elapsedTime) = 0;
    virtual void events() = 0;

private:
};