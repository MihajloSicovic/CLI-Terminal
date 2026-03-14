#pragma once
#include <sstream>


// Abstract generalization of all reader types.
class Reader {
public:

	// Destructor. Reader instance is deleted after derived classes.
	virtual ~Reader() {};

	// Loads line from input into argument line. Returns true if the line contains
	// at least one non-space character, otherwise returns false. To be redefined in derived classes.
	virtual bool getLine(std::string& line) const noexcept = 0;

	// Determines if the reading process from reader is done. To be redefined in derived classes.
	virtual bool isDone() const noexcept = 0;
};


// Represents reader type that reads from console input. Inherits Reader class properties.
class ConsoleReader : public Reader {
public:

	// Constructor.
	ConsoleReader() {};

	// Redefined. Gets line from console up to a limit of 512 characters. Returns true if successful.
	bool getLine(std::string& line) const noexcept override;

	// Redefined. Always returns false.
	bool isDone() const noexcept override;
};


// Represents reader type that reads from stream input. Inherits Reader class properties.
class StreamReader : public Reader {
public:

	// Constructor.
	// Requires input stream to read lines from.
	StreamReader(std::istream* const& stream);

	// Redefined. Gets line from stream. Returns true if successful.
	bool getLine(std::string& line) const noexcept override;

	// Redefined. Returns true when EOF stream flag is raised.
	bool isDone() const noexcept override;

private:

	// Stores input stream to read lines from.
	std::istream* stream;
};
