#pragma once
#include "Commands.h"


// Represents the "head" command. Inherits IOCommand and OptCommand properties. 
class HeadC : public IOCommand, public OptCommand {
public:

	// Enumerator. Holds all command options for this command.
	enum EOptions { n };

	// Constructor. Calls inherited IOCommand and OptCommand constructor. 
	// Requires input stream to read from, output stream to store the command output
	// and execution option for the given instance of this command.
	HeadC(const std::shared_ptr<std::istream>& in, const std::shared_ptr<std::ostream>& out, const std::string& opt) :
		IOCommand(in, out), OptCommand(opt) {}

	// Redefined. Executes the "head" command:
	// "-ncount": Prints the first count lines of input stream. 
	void executeCommand() const override;
	
private:

	// Returns conversion of the option string to EOptions enumerator.
	EOptions selectOption() const;

	// Helper function. Writes the given amount of lines from input to output.
	void getNLines(int count) const;
};

