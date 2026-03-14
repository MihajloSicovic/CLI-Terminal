#pragma once
#include <iostream>


// Abstract generalization of all CLI exceptions. All exception types should inherit this.
class cli_exception : public std::exception {
public:

	// Destructor. cli_exception instance is deleted after derived classes.
	virtual ~cli_exception() {}
	 
	// Gives additionial context to the error message and rethrows it. To be redifined in derived classes.
	virtual void add_context(const std::string& context) const = 0;

protected:

	// Constructor. Requires message that contains the description of the error that occured.
	explicit cli_exception(const std::string& message) : exception(message.c_str()) {}

	// Constructor. Requires message that contains the description of the error that occured.
	explicit cli_exception(const char* message) : exception(message) {}
};

// Represents errors that could occur when executing a command that don't require process termination.
// Inherits cli_exception class properties.
class command_error : public cli_exception {
public:

	// Constructor. Requires message that contains the description of the error that occured.
	explicit command_error(const std::string& message) : cli_exception(message.c_str()) {}

	// Constructor. Requires message that contains the description of the error that occured.
	explicit command_error(const char* message) : cli_exception(message) {}

	// Gives additionial context to the error message and throws exception of its own type.
	virtual void add_context(const std::string& context) const {
		throw command_error(context + ' ' + this->what());
	}
};


// Represents semantic errors that could occur when parsing a command line.
// Inherits cli_exception class properties.
class semantic_error : public cli_exception {
public:

	// Constructor. Requires message that contains the description of the error that occured.
	explicit semantic_error(const std::string& message) : cli_exception(message.c_str()) {}

	// Constructor. Requires message that contains the description of the error that occured.
	explicit semantic_error(const char* message) : cli_exception(message) {}

	// Gives additionial context to the error message and throws exception of its own type.
	virtual void add_context(const std::string& context) const {
		throw semantic_error(context + ' ' + this->what());
	}
};


// Represents syntax errors that could occur when parsing a command line.
// Inherits cli_exception class properties.
class syntax_error : public cli_exception {
public:

	// Constructor. Requires message that contains the description of the error that occured.
	explicit syntax_error(const std::string& message) : cli_exception(message.c_str()) {}

	// Constructor. Requires message that contains the description of the error that occured.
	explicit syntax_error(const char* message) : cli_exception(message) {}

	// Gives additionial context to the error message and throws exception of its own type.
	virtual void add_context(const std::string& context) const {
		throw syntax_error(context + ' ' + this->what());
	}
};


// Represents errors that could occur when constructing or executing a pipe stream.
// Inherits cli_exception class properties.
class pipe_error : public cli_exception {
public:

	// Constructor. Requires message that contains the description of the error that occured.
	explicit pipe_error(const std::string& message) : cli_exception(message.c_str()) {}

	// Constructor. Requires message that contains the description of the error that occured.
	explicit pipe_error(const char* message) : cli_exception(message) {}

	// Gives additionial context to the error message and throws exception of its own type.
	virtual void add_context(const std::string& context) const {
		throw pipe_error(context + ' ' + this->what());
	}
};


// Represents lexical errors that could be contained within the command string.
// Inherits cli_exception class properties.
class lexical_error : public cli_exception {
public:

	// Constructor. Requires message that contains the description of the error that occured.
	explicit lexical_error(const std::string& message) : cli_exception(message.c_str()) {}

	// Constructor. Requires message that contains the description of the error that occured.
	explicit lexical_error(const char* message) : cli_exception(message) {}

	// Gives additionial context to the error message and throws exception of its own type.
	virtual void add_context(const std::string& context) const {
		throw lexical_error(context + ' ' + this->what());
	}
};


// Represents errors that happen when the parsed command has unknown implementation.
// Inherits cli_exception class properties.
class unknown_command : public cli_exception {
public:

	// Constructor. Requires message that contains the description of the error that occured.
	explicit unknown_command(const std::string& message) : cli_exception(message.c_str()) {}

	// Constructor. Requires message that contains the description of the error that occured.
	explicit unknown_command(const char* message) : cli_exception(message) {}

	// Gives additionial context to the error message and throws exception of its own type.
	virtual void add_context(const std::string& context) const {
		throw unknown_command(context + ' ' + this->what());
	}
};
