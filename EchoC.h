#pragma once
#include "Commands.h"


// Represents the "echo" command. Inherits IOCommand properties. 
class EchoC : public IOCommand {
public:

    // Constructor. Calls inherited IOCommand constructor. 
    // Requires input stream to read from and output stream to store the command output.
    EchoC(const std::shared_ptr<std::istream>& in, const std::shared_ptr<std::ostream>& out) : IOCommand(in, out) {}

    // Redefined. Executes the "echo" command. Copies input stream and prints it to the output stream. 
    void executeCommand() const override;
};

