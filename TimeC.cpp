#include "TimeC.h"
using namespace std;


void TimeC::executeCommand() const {
    if (!out) return;

    time_t now = time(0);

    struct tm currTime;
    localtime_s(&currTime, &now);
    
    *out << currTime.tm_hour / 10 << currTime.tm_hour % 10 << ":";
    *out << currTime.tm_min / 10 << currTime.tm_min % 10 << ":";
    *out << currTime.tm_sec / 10 << currTime.tm_sec % 10;
}
