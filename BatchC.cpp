#include "BatchC.h"
#include "Simulator.h"
#include "Readers.h"
using namespace std;


void BatchC::executeCommand() const {
	if (!in || !out) return;

	Simulator sim(new StreamReader(in.get()), out.get());

	while (!sim.isFinished()) {
		sim.process();		
	}
}
