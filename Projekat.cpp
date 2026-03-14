// Projekat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Simulator.h"
using namespace std;

int main() {
    while (!Console::Instance()->isFinished()) {
        Console::Instance()->process();
    }
}
