#include "Physics.h"

#include "Logger.h"

#include <map>
#include <vector>

class HitBox {
public:
    HitBox(float bounds[4]) {
        this->bounds = bounds;
    }

    float* getBounds() {
        return bounds;
    }

private:
    float* bounds;
};

class Collision {
public:
    Collision(unsigned int hitBox1, unsigned int hitBox2) {
        this->hitBox1 = hitBox1;
        this->hitBox2 = hitBox2;
    }

    void checkCollision(std::map<unsigned int, HitBox*> hitBoxes) {
        float* bounds1 = hitBoxes[hitBox1]->getBounds();
        float* bounds2 = hitBoxes[hitBox2]->getBounds();

        if (bounds1[0] < bounds2[0] + bounds2[2] &&
            bounds1[0] + bounds1[2] > bounds2[0] &&
            bounds1[1] < bounds2[1] + bounds2[3] &&
            bounds1[1] + bounds1[3] > bounds2[1]) {
            colliding = true;
        } else {
            colliding = false;
        }
    }

    bool isColliding() {
        return colliding;
    }

    unsigned int getHitBox1() {
        return hitBox1;
    }

    unsigned int getHitBox2() {
        return hitBox2;
    }

private:
    unsigned int hitBox1;
    unsigned int hitBox2;

    bool colliding;
};

namespace {
    std::map<unsigned int, Collision*> connectedCollisions;
    std::map<unsigned int, HitBox*> hitBoxes;
}

unsigned int physics::createHitBox(float bounds[4]) {
    unsigned int id = hitBoxes.size();
    hitBoxes[id] = new HitBox(bounds);
    return id;
}

unsigned int physics::listenCollisions(unsigned int hitBox1, unsigned int hitBox2) {
    unsigned int id = connectedCollisions.size();
    connectedCollisions[id] = new Collision(hitBox1, hitBox2);
    return id;
}

void physics::checkCollisions() {
    for (auto it = connectedCollisions.begin(); it != connectedCollisions.end(); ++it) {
        it->second->checkCollision(hitBoxes);
    }
}

bool physics::isColliding(unsigned int collision) {
    if (connectedCollisions.find(collision) == connectedCollisions.end()) {
        logError("Collision Object does not exist", 0);
        return false;
    }

    return connectedCollisions[collision]->isColliding();
}

void physics::destroyHitBox(unsigned int hitBox) {
    std::vector<unsigned int> collisionsToRemove;

    for (auto it = connectedCollisions.begin(); it != connectedCollisions.end(); ++it) {
        if (it->second->getHitBox1() == hitBox || it->second->getHitBox2() == hitBox) {
            collisionsToRemove.push_back(it->first);
        }
    }

    for (int i = 0; i < collisionsToRemove.size(); i++) {
        connectedCollisions.erase(collisionsToRemove[i]);
    }

    hitBoxes.erase(hitBox);
}
