#include "Pipe.h"
#include "Commands.h"
#include "Exceptions.h"
#include <sstream>
using namespace std;


Pipe::Pipe() : innerIn(new stringstream("")), innerOut(new stringstream("")) {}

void Pipe::addCommand(unique_ptr<Command> cmd) const {
	if (!cmd) throw invalid_argument("Error - cannot add null command to pipe");

	if (!commands.empty()) {
		try {
			if (!commands.back()->outIsDefault()) 
				throw pipe_error("Error - output for command #" + to_string(commands.size())
					+ " inside pipe already defined");
		}
		catch (const semantic_error&) {
			throw pipe_error("Error - command #" + to_string(commands.size())
				+ " inside pipe doesn't take an output");
		}

		commands.back()->setOut(innerOut);

		try {
			if (!cmd->inIsDefault())
				throw pipe_error("Error - input for command #" + to_string(commands.size() + 1)
					+ " inside pipe already defined");
		}
		catch (const semantic_error&) {
			throw pipe_error("Error - command #" + to_string(commands.size() + 1)
				+ " inside pipe doesn't take an input");
		}

		cmd->setIn(innerIn);
	}

	commands.push_back(move(cmd));
}

void Pipe::execute() const {
	for (auto const& cmd : commands) {
		cmd->executeCommand();
		innerIn->clear();
		*innerIn << innerOut->rdbuf();
		innerOut->clear();
	}
}
