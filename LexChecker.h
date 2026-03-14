#pragma once
#include <string>
#include <set>
#include <vector>


// Helper class. Checks if the command line follows lexical rules.
class LexicalChecker {
public:

	// Helper method. Throws error if a lexical rule is violated.
	static void CheckValidity(const std::string& line);

private:

	// Constructor.
	LexicalChecker() {}

	// Static method. Marks the error on position i of command line and sets the description of the error.
	static void MarkError(size_t i, const std::string& newDescription);

	// True if any character in line breaks the lexical rules.
	static bool errorOccured;

	// Set of all non-alphanumeric characters allowed to appear in command line.
	const static std::set<char> specialCommandChar;

	// Stores the positions of invalid characters in command line.
	static std::vector<char> charValid;

	// Stores the description of error that occured. If multiple occur simultaniously, defaults to empty.
	static std::string description;
};
