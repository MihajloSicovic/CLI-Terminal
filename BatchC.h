#pragma once
#include "Commands.h"


// Represents the "batch" command. Inherits IOCommand properties. 
class BatchC : public IOCommand {
public:

    // Constructor. Calls inherited IOCommand constructor. 
    // Requires input stream to read from and output stream to store the command output.
    BatchC(const std::shared_ptr<std::istream>& in, const std::shared_ptr<std::ostream>& out) : IOCommand(in, out) {}

    // Redefined. Executes the "batch" command. Executes lines from input as if they were command lines.
    void executeCommand() const override;
};

