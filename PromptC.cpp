#include "PromptC.h"
#include "Simulator.h"
using namespace std;


void PromptC::executeCommand() const {
	Console::Instance()->setCommandPrompt(argument);
}
