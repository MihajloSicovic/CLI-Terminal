#include "TRC.h"
#include <string>
using namespace std;


void TRC::executeCommand() const {
	if (what.empty() || !in || !out) return;

	string output = string(std::istreambuf_iterator<char>(*in), std::istreambuf_iterator<char>());

	size_t start_pos = 0;
	while ((start_pos = output.find(what, start_pos)) != string::npos) {
		output.replace(start_pos, what.length(), with);
		start_pos += with.length();
	}

	*out << output;
}
