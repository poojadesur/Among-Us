#ifndef TIMER_H
#define TIMER_H


class Timer {
public:
    Timer() {
        prev = 0;
        prevImposter = 0;
    }
    Timer(double interval, int timelimit, double imposterInterval, double screenInterval);
    double startTime;
    double interval;
    int timeLimit;
    bool processTick();
    bool inTimeLimit();
    int getTimeLeft();

    double imposterInterval;
    bool imposterTime();

    double screenInterval;
    bool ScreenTime();
    void startScreen();
    double screen;

private:
    double prev;
    double prevImposter;
};

#endif // TIMER_H
