#include "timer.h"
#include <GLFW/glfw3.h>
#include <iostream>

Timer::Timer(double interval,int timelimit, double imposterInterval,double screenInterval) {
    prev = 0;
    prevImposter = 0;
    this->startTime = glfwGetTime();
    this->interval = interval;
    this->timeLimit = timelimit;
    this->imposterInterval = imposterInterval;
    this->screenInterval = screenInterval;

}

bool Timer::processTick() {
    double cur = glfwGetTime();
    if (cur - prev >= interval) {
        prev = cur;
        return true;
    } else
        return false;
}

bool Timer::imposterTime() {
    double cur = glfwGetTime();
    if (cur - prevImposter >= imposterInterval) {
        prevImposter = cur;
        return true;
    } else
        return false;
}

bool Timer::inTimeLimit() {

    double cur = glfwGetTime();

    if ((cur) <= timeLimit) {
        return true;
    } else
    {
        return false;
    }
}

int Timer::getTimeLeft(){

    double cur = glfwGetTime();

    return int(timeLimit - int(cur));

}

void Timer::startScreen()
{
    screen =  glfwGetTime();
}


bool Timer::ScreenTime(){

    double cur = glfwGetTime();

    if ((cur - screen) <= screenInterval) {
        return true;
    } else
    {
        return false;
    }
}