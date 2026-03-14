#pragma once
#include "Commands.h"


// Represents the "wcc" command. Inherits IOCommand and OptCommand properties. 
class WCC : public IOCommand, public OptCommand {
public:

	// Enumerator. Holds all command options for this command.
	enum EOptions {w, c};

	// Constructor. Calls inherited IOCommand and OptCommand constructor. 
	// Requires input stream to read from, output stream to store the command output
	// and execution option for the given instance of this command.
	WCC(const std::shared_ptr<std::istream>& in, const std::shared_ptr<std::ostream>& out, const std::string& opt) :
		IOCommand(in, out), OptCommand(opt) {}

	// Redefined. Executes the "wcc" command:
	// "-w": Counts words from the input and prints the count to the output. 
	// "-c": Counts characters from the input and prints the count to the output. 
	void executeCommand() const override;

private:

	// Returns conversion of the option string to EOptions enumerator.
	EOptions selectOption() const;

	// Helper function. Counts characters from the input. 
	int charCount() const;

	// Helper function. Counts words from the input. 
	int wordCount() const;
};

