#include "RMC.h"
#include <cstdio>
using namespace std;


void RMC::executeCommand() const {
	remove(argument.c_str());
}
