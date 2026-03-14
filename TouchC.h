#pragma once
#include "Commands.h"


// Represents the "touch" command. Inherits ArgCommand properties. 
class TouchC : public ArgCommand {
public:

    // Constructor. Calls inherited ArgCommand constructor. 
	// Requires argument which represents the file name of the created file.
    explicit TouchC(const std::string& argument) : ArgCommand(argument) {}

    // Redefined. Executes the "touch" command. Creates file with the given name, 
    // and outputs exception if the file already exists.
    void executeCommand() const override;
};

