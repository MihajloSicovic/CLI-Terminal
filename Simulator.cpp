#include "Simulator.h"
#include "Files.h"
#include "Commands.h"
#include "Exceptions.h"
#include "Readers.h"
#include "Pipe.h"
#include "LexChecker.h"
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;


#pragma region Class Simulator
Simulator::~Simulator() {
	delete reader;
}

bool Simulator::process() const noexcept {
	string line;

	bool gotLine = reader->getLine(line);
	if (gotLine) {
		try {
			unique_ptr<Pipe> pipe = PipeBuilder::BuildPipe(line);
			pipe->execute();
		}
		catch (const exception& e) {
			*errorStream << e.what() << endl;
		}
	}

	return gotLine;
}

bool Simulator::isFinished() const noexcept {
	return reader->isDone();
}
#pragma endregion


#pragma region Class Console
Console* Console::Instance() {
	static Console console;
	return &console;
}

bool Console::process() const noexcept {
	cout << commandPrompt << ' ';

	bool executed = Simulator::process();
	if (executed) cout << endl;

	return executed;
}

Console::Console(const string& sign) : commandPrompt(sign), Simulator(new ConsoleReader(), &cout) {}
#pragma endregion


#pragma region Class PipeBuilder
unique_ptr<Pipe> PipeBuilder::BuildPipe(string line) {
	LexicalChecker::CheckValidity(line);

	unique_ptr<Pipe> pipe(new Pipe());

	size_t lastSep = 0;
	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] == '|') {
			try {
				pipe->addCommand(CommandBuilder::BuildCommand(line.substr(lastSep, i - lastSep)));
			}
			catch (const pipe_error&) {
				throw;
			}
			catch (const cli_exception& e) {
				e.add_context("[Command #" + to_string(pipe->getSize() + 1) + "]");
			}
			lastSep = i + 1;
		}

		if (line[i] == '<') line.insert(line.cbegin() + i++, ' ');

		if (line[i] == '>') {
			size_t prev = i ? i - 1 : 0;
			if (line[prev] != '>' && !isspace(line[prev])) line.insert(line.cbegin() + i++, ' ');
		}

		if (line[i] == '"') {
			i++;
			while (i < line.length() && line[i] != '"') i++;
		}
	} 

	try {
		pipe->addCommand(CommandBuilder::BuildCommand(line.substr(lastSep, line.length() - lastSep)));
	}
	catch (const pipe_error&) {
		throw;
	}
	catch (const cli_exception& e) {
		if (lastSep) e.add_context("[Command #" + to_string(pipe->getSize() + 1) + "]");
		else throw;
	}

	return pipe;
}
#pragma endregion


#pragma region Class CommandBuilder
unique_ptr<Command> CommandBuilder::BuildCommand(const string& line) {
	if (line.empty()) throw pipe_error("Error - command in pipe not defined");

	stringstream commandLine(line);
	string token = TokenParser::CreateToken(commandLine);

	queue<ETokens> expectedTokens;
	ECommands com = CommandFactory::SelectCommand(token);

	CommandFactory::GetExpectedTokens(com, expectedTokens);

	shared_ptr<istream> in(new istream(cin.rdbuf()));
	shared_ptr<ostream> out(new ostream(cout.rdbuf()));
	string opt, arg, what, with;

	while (!expectedTokens.empty()) {
		ETokens nextToken = expectedTokens.front();
		expectedTokens.pop();

		streampos prevPos = commandLine.tellg();
		token = TokenParser::CreateToken(commandLine);

		if (!token.empty() && (token.front() == '<' || token.front() == '>')) { 
			commandLine.seekg(prevPos);
			break;
		}

		TokenParser::ProcessToken(nextToken, token, in, out, opt, arg, what, with);
	}	

	if (!what.empty()) what = what.substr(1, what.length() - 2);
	if (!with.empty()) with = with.substr(1, with.length() - 2);
	unique_ptr<Command> cmd(CommandFactory::MakeCommand(com, in, out, opt, arg, what, with));
	ProcessRedirects(commandLine, cmd);
	return cmd;
}


void CommandBuilder::ProcessRedirects(stringstream& line, const unique_ptr<Command>& cmd) {
	string token;
	bool redirected = false;

	while (line >> token) {
		if (token.front() == '<') {
			if (!cmd->inIsDefault()) throw semantic_error("Error - input stream already defined");

			redirected = true;
			if (token.length() < 2) {
				token = TokenParser::CreateToken(line);
				if (token.empty()) throw semantic_error("Error - file for redirect not specified");
			}
			else token = token.substr(1, token.length() - 1);

			shared_ptr<istream> newIn(FileManager::getInputFile(token));
			cmd->setIn(newIn);
		}
		else if (token.front() == '>') {
			if (!cmd->outIsDefault()) throw semantic_error("Error - output stream already defined");

			redirected = true;
			token = token.substr(1, token.length() - 1);

			if (token.empty() || token.front() != '>') {
				if (token.empty()) token = TokenParser::CreateToken(line);
				if (token.empty()) throw semantic_error("Error - file for redirect not specified");

				shared_ptr<ostream> newOut(FileManager::getOutputFile(token));
				cmd->setOut(newOut);
			}
			else {
				if (token.length() < 2) {
					token = TokenParser::CreateToken(line);
					if (token.empty()) throw semantic_error("Error - file for redirect not specified");
				}
				else token = token.substr(1, token.length() - 1);

				shared_ptr<ostream> newOut(FileManager::getOutputFile(token, ios_base::app));
				cmd->setOut(newOut);
			}
		}
		else {
			if (redirected) throw semantic_error("Error - redirects must be written at the end of the command");
			else throw semantic_error("Error - too many arguments");
		}
	}
}
#pragma endregion


#pragma region Class TokenParser
string TokenParser::CreateToken(stringstream& line) {
	string token;

	if (line >> token) {
		if (token.front() == '"') {
			while (token.back() != '"' || token.length() < 2) {
				char charInQuotation;
				if (line.get(charInQuotation)) token += charInQuotation;
				else throw syntax_error("Syntax error - missing closing quote");
			}
		}
		return token;
	}
	else return "";
}


void TokenParser::ProcessToken(ETokens tokenType, const string& token,
	shared_ptr<istream>& in, shared_ptr<ostream>& out,
	string& opt, string& arg, string& what, string& with) {
	
	switch (tokenType) {
	case commandName:
		break;
	case option:
		if (token.empty()) throw semantic_error("Error - no option provided");
		if (token.front() != '-') throw syntax_error("Syntax error - option must start with '-' character");
		opt = token;
		break;
	case argument:
		if (token.empty()) break;
		else if (token.front() == '"') 
			in.reset(new stringstream(token.substr(1, token.length() - 2)));
		else in.reset(FileManager::getInputFile(token));
		break;
	case filename:
		if (token.empty()) throw semantic_error("Error - no file name provided");
		arg = token;
		break;
	case mandArg:
		if (token.empty()) throw semantic_error("Error - no argument provided");
		if (token.front() != '"') throw syntax_error("Syntax error - argument not in quotes");
		arg = token.substr(1, token.length() - 2);
		break;
	case argWhat:
		if (what.empty() && token.empty()) throw semantic_error("Error - no what argument provided");

		if (token.empty()) break;
		if (token.front() == '"') {
			if (what.empty()) what = token;
			else with = token;
		}
		else {
			if (!what.empty()) throw syntax_error("Syntax error - with argument not in quotes");
			if (in->rdbuf() != cin.rdbuf()) throw syntax_error("Syntax error - what argument not in quotes");
			else in.reset(FileManager::getInputFile(token));
		}
		break;
	case argWith:
		if (token.empty()) break;
		if (token.front() != '"') throw syntax_error("Syntax error - with argument not in quotes");
		if (!with.empty()) {
			in.reset(new stringstream(what.substr(1, what.length() - 2)));
			what = with;
		}
		with = token;
		break;
	}
}
#pragma endregion


