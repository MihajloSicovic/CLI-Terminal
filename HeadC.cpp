#include "HeadC.h"
#include "Exceptions.h"
#include <string>
#include <cctype>
using namespace std;

void HeadC::executeCommand() const {
	if (!in || !out) return;
	
	switch (selectOption()) {
	case n:
		if (opt.length() < 3 || opt.length() > 7)
			throw command_error("Error - head option character count out of bounds");

		for (int i = 2; i < opt.length(); i++)
			if (!isdigit(opt[i])) throw command_error("Error - option argument is numbers only");

		int cnt = stoi(opt.substr(2, opt.length() - 2));
		getNLines(cnt);

		break;
	}
}

HeadC::EOptions HeadC::selectOption() const {
	if (opt.substr(0, 2) == "-n") return n;

	throw command_error("Error - \"" + opt + "\" option for the command doesn't exist");
}

void HeadC::getNLines(int count) const {
	int i = 0;
	string line, output = "";

	while (getline(*in, line)) {
		if (i < count) {
			output += line + (in->eof() || i == count - 1 ? "" : "\n");
			i++;
		}
	}

	*out << output;
}
