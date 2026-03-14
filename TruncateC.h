#pragma once
#include "Commands.h"


// Represents the "truncate" command. Inherits ArgCommand properties. 
class TruncateC : public ArgCommand {
public:

    // Constructor. Calls inherited ArgCommand constructor. 
    // Requires argument which represents the file name of the created file.
    explicit TruncateC(const std::string& argument) : ArgCommand(argument) {}

    // Redefined. Executes the "truncate" command. 
    // Empties the contents of the file with the provided file name.
    void executeCommand() const override;
};

