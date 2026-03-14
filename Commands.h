#pragma once
#include <iostream>
#include <queue>
#include <stdexcept>
#include "Exceptions.h"

enum ETokens;

// Enumerator. Holds all commands types.
enum ECommands {echoC, promptC, timeC, dateC, touchC, truncateC, rmC, wcC, trC, headC, batchC};


// Abstract generalization of all command types. All command types should inherit this.
class Command {
public:

    // Destructor. Command instance is deleted after derived classes.
    virtual ~Command() {}

    // Executes command. To be redefined in derived	classes.
	virtual void executeCommand() const = 0;

    // Throws exception if called. To be redefined in derived classes.
    virtual bool inIsDefault() const;

    // Throws exception if called. To be redefined in derived classes.
    virtual void setIn(const std::shared_ptr<std::istream>& in);

    // Throws exception if called. To be redefined in derived classes.
    virtual bool outIsDefault() const;

    // Throws exception if called. To be redefined in derived classes.
    virtual void setOut(const std::shared_ptr<std::ostream>& out);
};


// Helper class that assists in the process of creating an object of Command class type. Factory DP.
class CommandFactory {
public:

    // Static method. Returns conversion of the command name string to ECommands enumerator.
    static ECommands SelectCommand(const std::string& commandName);

    // Factory method. Returns new instance of command type initialized with the given parameters.
    static Command* MakeCommand(ECommands command,
        const std::shared_ptr<std::istream>& in, const std::shared_ptr<std::ostream>& out,
        const std::string& opt, const std::string& argument,
        const std::string& what, const std::string& with);

    // Static method. Fills reference queue with the expected input tokens for the given command.
    static void GetExpectedTokens(ECommands command, std::queue<ETokens>& expectedTokens) noexcept;
};


// Abstract generalization of all command types that require an input.
class InCommand : virtual public Command {
public:

    // Redefined. Returns true if input is set to cin. Otherwise, returns false.
    bool inIsDefault() const noexcept override;

    // Redefined. Setter. Sets in field of class.
    void setIn(const std::shared_ptr<std::istream>& in) noexcept override;

protected:

    // Destructor. InCommand instance is deleted after derived classes.
    virtual ~InCommand() {}

    // Constructor. Requires input stream that the command reads from.
    explicit InCommand(const std::shared_ptr<std::istream>& in) : in(in) {
        if (!in) throw std::invalid_argument("Error - input cannot be null");
    }

    // Stores reference to input stream of the command.
    std::shared_ptr<std::istream> in;
};


// Abstract generalization of all command types that have an output.
class OutCommand : virtual public Command {
public:

    // Redefined. Returns true if output is set to cout. Otherwise, returns false.
    bool outIsDefault() const noexcept override;

    // Redefined. Setter. Sets out field of class.
    void setOut(const std::shared_ptr<std::ostream>& out) noexcept override;

protected:

    // Destructor. OutCommand instance is deleted after derived classes.
    virtual ~OutCommand() {}

    // Constructor. Requires output stream that the command writes to.
    explicit OutCommand(const std::shared_ptr<std::ostream>& out) : out(out) {
        if (!out) throw std::invalid_argument("Error - output cannot be null");
    }

    // Stores reference to output stream of the command.
    std::shared_ptr<std::ostream> out;
};


// Abstract generalization of all command types that require an input and have an output.
class IOCommand : public InCommand, public OutCommand {
protected:

    // Destructor. IOCommand instance is deleted after derived classes.
    virtual ~IOCommand() {}

    // Constructor. Calls inherited InCommand and OutCommand constructor. 
    // Requires input stream that the command reads from and output stream that the command writes to.
    IOCommand(const std::shared_ptr<std::istream>& in, const std::shared_ptr<std::ostream>& out) :
        InCommand(in), OutCommand(out) {}
};


// Abstract generalization of all command types that have execution options.
class OptCommand : virtual public Command {
protected:

    // Destructor. OptCommand instance is deleted after derived classes.
    virtual ~OptCommand() {}

    // Constructor. Requires option string that determines command execution.
    explicit OptCommand(const std::string& opt) : opt(opt) {
        if (opt.empty()) throw semantic_error("Error - option empty");
    }

    // Stores option string of the command.
    std::string opt;
};


// Abstract generalization of all command types that require a mandatory argument.
class ArgCommand : virtual public Command {
protected:

    // Destructor. ArgCommand instance is deleted after derived classes.
    virtual ~ArgCommand() {}

    // Constructor. Requires argument string that provides mandatory argument for command.
    explicit ArgCommand(const std::string& argument) : argument(argument) {
        if (argument.empty()) throw semantic_error("Error - argument empty");    
    }

    // Stores argument string of the command.
    std::string argument;
};
