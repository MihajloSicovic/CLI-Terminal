#pragma once
#include <iostream>
#include <string>

class Reader;
class Command;
class Pipe;

// Enumerator. Holds all token types from the command line.
enum ETokens {commandName, option, argument, filename, mandArg, argWhat, argWith};


// Abstact generalization of all command line simulators.
class Simulator {
public:

	// Destructor. Simulator instance is deleted after derived classes.
	virtual ~Simulator();

	// Constructor. Requires reader to read command lines from.
	Simulator(Reader* const& reader, std::ostream* const& errorStream) :
		reader(reader), errorStream(errorStream) {
		
		if (!reader) throw std::invalid_argument("Error - reader cannot be null");
		if (!errorStream) throw std::invalid_argument("Error - error stream cannot be null");
	}

	// Reads one line from reader and processes it. 
	// Returns true if the line is processed, otherwise returns false.
	// To be redefined in derived classes.
	virtual bool process() const noexcept;

	// Determines if the Console class runtime has finished.
	bool isFinished() const noexcept;

protected:

	// Points to Reader class to read command lines from.
	Reader* reader;

	// Points to stream for reporting errors.
	std::ostream* errorStream;
};


//	The entire command line interpreter (CLI), enables user interaction. Singleton. Singleton DP.
class Console : public Simulator {
public:

	// Copy constructor deleted. Singleton DP.
	Console(Console& copy) = delete;

	// Static method. Returns the singleton instance of this class. Singleton DP.
	static Console* Instance();

	// Initiates the interaction between the CLI and the user.
	bool process() const noexcept;

	// Setter. Sets commandPrompt attribute to new value.
	void setCommandPrompt(std::string newCommandPrompt) noexcept {
		this->commandPrompt = newCommandPrompt;
	}

private:

	// Constructor. Singleton DP. Calls inherited Simulator constructor.
	explicit Console(const std::string& sign = "$");

	// Stores the string that is printed when the console is ready for a new command input.
	std::string commandPrompt;
};


class PipeBuilder {
public:

	// Helper method. Creates and executes pipe for given line.
	static std::unique_ptr<Pipe> BuildPipe(std::string line);

private:

	// Constructor.
	PipeBuilder() {}
};


// Helper class. Helps Console class parse command line input.
class CommandBuilder {
public:

	// Helper method. Creates and executes command for given line.
	static std::unique_ptr<Command> BuildCommand(const std::string& line);

private:

	// Helper method. Reads command line for redirects and redirects input and output of command accordingly.
	static void ProcessRedirects(std::stringstream& line, const std::unique_ptr<Command>& cmd);

	// Constructor.
	CommandBuilder() {}
};


// Helper class. Helps CommandBuilder class parse command line token.
class TokenParser {
public:

	// Helper method. Creates the next token from given command line.
	static std::string CreateToken(std::stringstream& line);

	// Helper method. Updates command parameters based on the passed token.
	static void ProcessToken(ETokens tokenType, const std::string& token,
		std::shared_ptr<std::istream>& in, std::shared_ptr<std::ostream>& out,
		std::string& opt, std::string& arg, std::string& what, std::string& with);

private:

	// Constructor.
	TokenParser() {}
};
