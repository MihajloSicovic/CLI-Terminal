#pragma once
#include "Commands.h"


// Represents the "time" command. Inherits OutCommand properties.
class TimeC : public OutCommand {
public:

    // Constructor. Calls inherited OutCommand constructor. 
    // Requires output stream to store the command output.
    explicit TimeC(const std::shared_ptr<std::ostream>& out) : OutCommand(out) {}

    // Redefined. Executes the "time" command. Prints current local time in "hh:mm:ss" format.
    void executeCommand() const override;
};

