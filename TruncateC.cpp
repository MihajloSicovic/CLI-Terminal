#include "TruncateC.h"
#include "Exceptions.h"
#include <fstream>
using namespace std;


void TruncateC::executeCommand() const {
    ifstream file(argument);

    if (file.is_open()) {
        file.close();
        ofstream truncatedFile(argument, ios_base::trunc);
        truncatedFile.close();
    }
}
