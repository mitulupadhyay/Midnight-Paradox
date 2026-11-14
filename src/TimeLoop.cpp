// TimeLoop.cpp - clock, loop counter and the daily reset.

#include "Declarations.cpp"

TimeLoop::TimeLoop() {
    currentLoop = 1;
    minutesSinceMidnight = 8 * 60;   // 8:00 AM
    victimAlive = true;
}

int TimeLoop::getCurrentLoop() const {
    return currentLoop;
}

void TimeLoop::setTime(int hour, int minute) {
    minutesSinceMidnight = hour * 60 + minute;
}

void TimeLoop::advanceMinutes(int minutes) {
    minutesSinceMidnight += minutes;
    if (minutesSinceMidnight >= 24 * 60) {
        minutesSinceMidnight = minutesSinceMidnight % (24 * 60);
    }
}

string TimeLoop::getTimeString() const {
    int hour24 = minutesSinceMidnight / 60;
    int minute = minutesSinceMidnight % 60;

    string suffix = "AM";
    if (hour24 >= 12) {
        suffix = "PM";
    }

    int hour12 = hour24 % 12;
    if (hour12 == 0) {
        hour12 = 12;               // midnight shows as 12, noon shows as 12
    }

    string minuteText = to_string(minute);
    if (minute < 10) {
        minuteText = "0" + minuteText;
    }

    return to_string(hour12) + ":" + minuteText + " " + suffix;
}

bool TimeLoop::isVictimAlive() const {
    return victimAlive;
}

// Has the clock reached (or passed) the given time today? Used for deadlines.
bool TimeLoop::hasReached(int hour, int minute) const {
    return minutesSinceMidnight >= (hour * 60 + minute);
}

void TimeLoop::setVictimAlive(bool alive) {
    victimAlive = alive;
}

// The daily reset: a new loop at 8:00 AM; world state resets, the notebook does not.
void TimeLoop::resetDay() {
    currentLoop = currentLoop + 1;
    minutesSinceMidnight = 8 * 60;
    victimAlive = true;
}
