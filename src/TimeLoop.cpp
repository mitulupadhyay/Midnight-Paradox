#include "TimeLoop.h"

TimeLoop::TimeLoop() : minutes(START_TIME), loopCount(1) {}

void TimeLoop::advance(int mins) { minutes += mins; }

bool TimeLoop::isMidnight() const { return minutes >= DAY_END; }

void TimeLoop::resetDay() {
    minutes = START_TIME;
    loopCount++;
}

int TimeLoop::getLoop() const { return loopCount; }
int TimeLoop::getHour() const { return (minutes / 60) % 24; }

std::string TimeLoop::getTimeString() const {
    int m = minutes % DAY_END;
    int h = m / 60, mi = m % 60;
    std::string ampm = (h >= 12) ? "PM" : "AM";
    int h12 = h % 12;
    if (h12 == 0) h12 = 12;
    std::string minStr = (mi < 10 ? "0" : "") + std::to_string(mi);
    return std::to_string(h12) + ":" + minStr + " " + ampm;
}
