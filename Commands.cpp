#include "CommandTypes.h"
#include "Exceptions.h"
#include "Simulator.h"
#include <sstream>
#include <istream>
using namespace std;

#pragma region Class CommandFactory
ECommands CommandFactory::SelectCommand(const string& commandName) {
	if (commandName == "echo") return echoC;
	if (commandName == "prompt") return promptC;
	if (commandName == "time") return timeC;
	if (commandName == "date") return dateC;
	if (commandName == "touch") return touchC;
	if (commandName == "truncate") return truncateC;
	if (commandName == "rm") return rmC;
	if (commandName == "wc") return wcC;
	if (commandName == "tr") return trC;
	if (commandName == "head") return headC;
	if (commandName == "batch") return batchC;

	throw unknown_command("Unknown command: \"" + commandName + "\"");
}

Command* CommandFactory::MakeCommand(ECommands command, const shared_ptr<istream>& in,
	const shared_ptr<ostream>& out, const string& opt, const string& argument,
	const string& what, const string& with) {

	switch (command) {
	case echoC:
		return new EchoC(in, out);
	case promptC:
		return new PromptC(argument);
	case timeC:
		return new TimeC(out);
	case dateC:
		return new DateC(out);
	case touchC:
		return new TouchC(argument);
	case truncateC:
		return new TruncateC(argument);
	case rmC:
		return new RMC(argument);
	case wcC:
		return new WCC(in, out, opt);
	case trC:
		return new TRC(in, out, what, with);
	case headC:
		return new HeadC(in, out, opt);
	case batchC:
		return new BatchC(in, out);
	}

	throw unknown_command("Error - unable to create command");
}

void CommandFactory::GetExpectedTokens(ECommands command, queue<ETokens>& expectedTokens) noexcept {
	switch (command) {
	case echoC:
		expectedTokens.push(argument);
		break;
	case promptC:
		expectedTokens.push(mandArg);
		break;
	case timeC:
		break;
	case dateC:
		break;
	case touchC:
		expectedTokens.push(filename);
		break;
	case truncateC:
		expectedTokens.push(filename);
		break;
	case rmC:
		expectedTokens.push(filename);
		break;
	case wcC:
		expectedTokens.push(option);
		expectedTokens.push(argument);
		break;
	case trC:
		expectedTokens.push(argWhat);
		expectedTokens.push(argWhat);
		expectedTokens.push(argWith);
		break;
	case headC:
		expectedTokens.push(option);
		expectedTokens.push(argument);
		break;
	case batchC:
		expectedTokens.push(argument);
		break;
	}
}
#pragma endregion


#pragma region Class Command
bool Command::inIsDefault() const {
	throw semantic_error("Error - command has no input stream");
}

void Command::setIn(const shared_ptr<istream>& in) {
	throw semantic_error("Error - command has no input stream");
}

bool Command::outIsDefault() const {
	throw semantic_error("Error - command has no output stream");
}

void Command::setOut(const shared_ptr<ostream>& out) {
	throw semantic_error("Error - command has no output stream");
}
#pragma endregion


#pragma region Class InCommand
bool InCommand::inIsDefault() const noexcept {
	return in->rdbuf() == cin.rdbuf();
}

void InCommand::setIn(const shared_ptr<istream>& in) noexcept {
	if (!in) throw invalid_argument("Error - input cannot be set to null");
	this->in = in;
}
#pragma endregion


#pragma region Class OutCommand
bool OutCommand::outIsDefault() const noexcept {
	return out->rdbuf() == cout.rdbuf();
}

void OutCommand::setOut(const shared_ptr<ostream>& out) noexcept {
	if (!out) throw invalid_argument("Error - output cannot be set to null");
	this->out = out;
}
#pragma endregion
