#pragma once
#include "Commands.h"


// Represents the "tr" command. Inherits IOCommand properties. 
class TRC : public IOCommand {
public:

    // Constructor. Calls inherited IOCommand constructor. 
    // Requires input stream to read from and output stream to store the command output.
    TRC(const std::shared_ptr<std::istream>& in, const std::shared_ptr<std::ostream>& out,
        const std::string& what, const std::string& with) : IOCommand(in, out), what(what), with(with) {

        if (what.empty()) throw semantic_error("Error - what argument empty");
    }

    // Redefined. Executes the "tr" command. Replaces all instaces of what argument in input using with argument. 
    void executeCommand() const override;

private:

    // Stores substring to be replaced in input.
    std::string what;
    
    // Stores string that the "what" substing will be replaced with.
    std::string with;
};

