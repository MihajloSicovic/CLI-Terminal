#pragma once
#include <memory>
#include <list>

class Command;


// Represents a pipestream of commands that allows executing commands in a sequence. 
class Pipe {
public:

	// Constructor.
	Pipe();

	// Adds the given commands to pipestream. Destroys reference to command outside of pipe to claim ownership.
	void addCommand(std::unique_ptr<Command> cmd) const;

	// Executes pipestream. Executes commands in series, linking the output of the previous 
	// executed command to the input of the command in execution.
	void execute() const;

	// Returns the number of commands stored in pipe.
	size_t getSize() const noexcept { return commands.size(); }

private:

	// Keeps track of the commands added to the pipestream.
	mutable std::list<std::unique_ptr<Command>> commands;

	// Represents the shared output between commands.
	std::shared_ptr<std::ostream> innerOut;

	// Represents the shared input between commands.
	std::shared_ptr<std::stringstream> innerIn;
};

