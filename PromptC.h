#pragma once
#include "Commands.h"


// Represents the "prompt" command. Inherits ArgCommand properties. 
class PromptC : public ArgCommand {
public:

    // Constructor. Calls inherited ArgCommand constructor. 
    // Requires argument which represents the new command prompt of the CLI.
    explicit PromptC(const std::string& argument) : ArgCommand(argument) {}

    // Redefined. Executes the "prompt" command. 
    // Changes command prompt of the CLI to the given argument. 
    void executeCommand() const override;
};

