#pragma once
#include "Commands.h"


// Represents the "rm" command. Inherits ArgCommand properties. 
class RMC : public ArgCommand {
public:

    // Constructor. Calls inherited ArgCommand constructor. 
    // Requires argument which represents the file name of the created file.
    explicit RMC(const std::string& argument) : ArgCommand(argument) {}

    // Redefined. Executes the "rm" command. Removes file with the given name.
    void executeCommand() const override;
};

