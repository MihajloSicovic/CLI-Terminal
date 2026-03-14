#include "DateC.h"
using namespace std;


void DateC::executeCommand() const {
    if (!out) return;

    time_t now = time(0);

    struct tm currTime;
    localtime_s(&currTime, &now);

    *out << currTime.tm_mday / 10 << currTime.tm_mday % 10 << ".";
    *out << (currTime.tm_mon + 1) / 10 << (currTime.tm_mon + 1) % 10 << ".";
    *out << currTime.tm_year + 1900 << ".";
}
