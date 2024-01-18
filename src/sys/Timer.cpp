#include "Timer.h"

#include <map>
#include <chrono>
#include <thread>

namespace {
    std::map<unsigned int, std::chrono::steady_clock::time_point> timerMap;  // Map to store timer IDs and time points
    unsigned int totalCreated = 0;
}

unsigned int timer::createTimer() {
    std::chrono::steady_clock::time_point timePoint;
    unsigned int id = totalCreated + 1;  // Generate a unique ID

    timePoint = std::chrono::steady_clock::now();  // start recording time

    timerMap.insert(std::pair<unsigned int, std::chrono::steady_clock::time_point>(id, timePoint));  // Insert the ID and time point into the map

    totalCreated++;

    return id;
}

void timer::resetTimer(unsigned int id) {
    timerMap[id] = std::chrono::steady_clock::now();
}

void timer::killTimer(unsigned int id) {
    timerMap.erase(id);
}

double timer::getTimeDiff(unsigned int id) {
    auto now = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(now - timerMap[id]).count() * .000001;  // Calculate the time difference in milliseconds

    return diff;
}

void timer::delay(double milliseconds) {
    double ns = milliseconds * 1000000.0;

    auto start = std::chrono::steady_clock::now();

    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();

        if ((ns - diff) <= 0)
            break;
    }
}
