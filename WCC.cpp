#include "WCC.h"
#include "Exceptions.h"
using namespace std;


void WCC::executeCommand() const {
	if (!in || !out) return;

	switch (selectOption()) {
	case w:
		*out << wordCount();
		break;
	case c:
		*out << charCount();
		break;
	}
}

WCC::EOptions WCC::selectOption() const {
	if (opt == "-w") return w;
	if (opt == "-c") return c;

	throw command_error("Error - \"" + opt + "\" option for the command doesn't exist");
}

int WCC::charCount() const {
	char c;
	int count = 0;
	while (in->get(c)) {
		count++;
	}

	return count;
}

int WCC::wordCount() const {
	string word;
	int count = 0;
	while (*in >> word) {
		count++;
	}

	return count;
}
