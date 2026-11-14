#pragma once
#include <string>

class TimeLoop {
private:
    int minutes;     // minutes since 00:00 (480 = 8:00 AM)
    int loopCount;   // current loop number (1, 2, 3 ...)
public:
    static const int START_TIME = 8 * 60;   // 8:00 AM
    static const int DAY_END    = 24 * 60;  // midnight

    TimeLoop();
    void advance(int mins);      // time aage badhao
    bool isMidnight() const;     // kya raat 12 baj gaye?
    void resetDay();             // 8:00 AM par wapas, loop +1
    int  getLoop() const;
    int  getHour() const;
    std::string getTimeString() const;  // "8:00 AM"
};
