#include "Timer.h"

#include <map>
#include <chrono>

#include <iomanip>
#include <sstream>
#include <glad/glad.h>

namespace {
    std::map<unsigned int, std::chrono::steady_clock::time_point> timerMap;  // Map to store timer IDs and time points

    unsigned int benchmarkTimerID;
    unsigned int frameTimeCalcTimerID;

    int totalRenderedFrames;

    double averageFrameTime;
    double benchmarkResult;
    double lastFrameDuration;
}

void timer::init() {
    benchmarkTimerID = 0;
    frameTimeCalcTimerID = createTimer();
    totalRenderedFrames = 0;
    averageFrameTime = 0;
}

unsigned int timer::createTimer() {
    std::chrono::steady_clock::time_point timePoint;
    unsigned int id = timerMap.size() + 1;  // Generate a unique ID

    timePoint = std::chrono::steady_clock::now();  // start recording time

    timerMap.insert(std::pair<unsigned int, std::chrono::steady_clock::time_point>(id, timePoint));  // Insert the ID and time point into the map

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

// Benchmark functions

void benchmark::startBenchmark() {
    if (benchmarkTimerID != 0) return;
    benchmarkTimerID = timer::createTimer();
}

void benchmark::endBenchmark() {
    benchmarkResult = timer::getTimeDiff(benchmarkTimerID);
    timer::killTimer(benchmarkTimerID);
    benchmarkTimerID = 0;
}

double benchmark::getLastFrameDuration(int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << lastFrameDuration;
    std::string str = ss.str();

    return std::stod(str);
}

double benchmark::getBenchmarkResult(int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << benchmarkResult;
    std::string str = ss.str();

    return std::stod(str);
}

void benchmark::countFrames() {
    totalRenderedFrames++;
    lastFrameDuration = timer::getTimeDiff(frameTimeCalcTimerID);
    averageFrameTime = (averageFrameTime * (totalRenderedFrames-1) + lastFrameDuration) / totalRenderedFrames;
    timer::resetTimer(frameTimeCalcTimerID);
}

double benchmark::getAverageFrameTime(int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << averageFrameTime;
    std::string str = ss.str();


    return std::stod(str);
}
