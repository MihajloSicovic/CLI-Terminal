#include "TouchC.h"
#include "Exceptions.h"
#include <fstream>
using namespace std;


void TouchC::executeCommand() const {
    ifstream file(argument);

    if (file.is_open()) {
        file.close();
        throw command_error("Error - file already exists");
    }

    ofstream createdFile(argument);
    createdFile.close();
}
