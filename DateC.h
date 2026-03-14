#pragma once
#include "Commands.h"


// Represents the "date" command. Inherits OutCommand properties.
class DateC : public OutCommand {
public:

    // Constructor. Calls inherited OutCommand constructor. 
    // Requires output stream to store the command output.
    explicit DateC(const std::shared_ptr<std::ostream>& out) : OutCommand(out) {}

    // Redefined. Executes the "date" command. Prints current local date in "dd.mm.yyyy." format.
    void executeCommand() const override;
};

