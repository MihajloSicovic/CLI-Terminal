#include "Readers.h"
#include <iostream>
#include <istream>
#include <stdexcept>
using namespace std;


#pragma region Class ConsoleReader
bool ConsoleReader::getLine(string& line) const noexcept {
	cin.clear();
	getline(cin, line, '\n');
	line = line.substr(0, 512);

	stringstream testLineEmptiness(line);
	string word;

	return testLineEmptiness >> word ? true : false;
}

bool ConsoleReader::isDone() const noexcept {
	return false;
}
#pragma endregion


#pragma region Class StreamReader
StreamReader::StreamReader(istream* const& stream) : stream(stream) {
	if (!stream) throw invalid_argument("Error - stream cannot be null");

	if (stream->rdbuf() == cin.rdbuf()) {
		string line, commands;
		while (getline(*stream, line, '\n')) commands += line + '\n';

		this->stream = new stringstream(commands);
	}
}

bool StreamReader::getLine(string& line) const noexcept {
	getline(*stream, line, '\n');
	line = line.substr(0, 512);
	
	stringstream testLineEmptiness(line);
	string word;

	return testLineEmptiness >> word ? true : false;
}

bool StreamReader::isDone() const noexcept {
	return stream->eof();
}
#pragma endregion
