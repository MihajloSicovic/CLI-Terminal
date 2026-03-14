#include "LexChecker.h"
#include "Exceptions.h"
#include <cctype>
using namespace std;


bool LexicalChecker::errorOccured = false;
const set<char> LexicalChecker::specialCommandChar{ '"', '<', '>', '|', '-', '.', ':', '\\', '/' };
vector<char> LexicalChecker::charValid{};
string LexicalChecker::description;


void LexicalChecker::CheckValidity(const string& line) {
	charValid = vector<char>(line.length());
	fill(charValid.begin(), charValid.end(), ' ');
	errorOccured = false;
	description = "";
	size_t consecutiveLessThanChar = 0, consecutiveMoreThanChar = 0;
	bool firstWord = false, indent = true;

	for (size_t i = 0; i < line.length(); i++) {
		if (isspace(line[i])) {
			if (firstWord) firstWord = false;
			charValid.at(i) = line[i];
			continue;
		}
		else if (indent) {
			indent = false;
			firstWord = true;
			if (line[i] == '<' || line[i] == '>') MarkError(i, " (illegal characters)");
		}

		if (line[i] == '|') {
			indent = true;
			firstWord = false;
		}

		if (line[i] == '<') {
			firstWord = false;
			consecutiveLessThanChar++;
			if (consecutiveLessThanChar > 1) MarkError(i, " (too many consecutive '<' characters)");
		}
		else consecutiveLessThanChar = 0;

		if (line[i] == '>') {
			firstWord = false;
			consecutiveMoreThanChar++;
			if (consecutiveMoreThanChar == 2 && line[i - 1] != '>') MarkError(i, " (divided '>' characters)");
			if (consecutiveMoreThanChar > 2) MarkError(i, " (too many consecutive '>' characters)");
		}
		else consecutiveMoreThanChar = 0;

		if (firstWord && !isalpha(line[i])) MarkError(i, " (illegal characters)");

		if (isalnum(line[i])) {
			continue;
		}

		if (specialCommandChar.find(line[i]) == specialCommandChar.end()) MarkError(i, " (illegal characters)");

		if (line[i] == '"') {
			for (size_t j = (i ? i - 1 : 0); j > 0 && !isspace(line[j]) && line[j] != '|'; j--) 
				MarkError(j, " (are you missing a space?)");

			i++;
			while (i < line.length() && line[i] != '"') i++;
			i++;

			for (; i < line.length() && !isspace(line[i]) && line[i] != '|'; i++) {
				if (line[i] == '<' || line[i] == '>') {
					i--;
					break;
				}

				MarkError(i, " (are you missing a space?)");
			}
		}
	}

	if (errorOccured) {
		string unexpectedCharacters;
		for (char c : charValid)
			unexpectedCharacters += c;

		throw lexical_error("Error - unexpected characters" + description + ":\n" + 
			line + '\n' + unexpectedCharacters);
	}

	// wc& -w "Lorem ipsum dolor sit amet" +?
	// wc& -w *"Lorem ipsum dolor sit amet" +?
	// wc& -w *"Lorem ipsum dolor sit amet" 
	// wc -w "Lorem ipsum dolor sit amet"<<out.txt 
	// wc -w "Lorem ipsum dolor sit amet">>>out.txt 
	// wc -w "Loremt">output.txt
	// wc -w "Loremt"> > > >output.txt
}

void LexicalChecker::MarkError(size_t i, const string& newDescription) {
	if (charValid.at(i) == '^') return;

	if (errorOccured && description != newDescription) description = "";
	else description = newDescription;

	charValid.at(i) = '^';
	errorOccured = true;
}
