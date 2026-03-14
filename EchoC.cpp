#include "EchoC.h"
#include <string>
using namespace std;


void EchoC::executeCommand() const {
	if (!in || !out) return;

	*out << string(std::istreambuf_iterator<char>(*in), std::istreambuf_iterator<char>());
}
