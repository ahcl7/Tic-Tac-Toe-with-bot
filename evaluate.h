#ifndef EVALUEATE_H_INCLUDED
#define EVALUEATE_H_INCLUDED

#include "state.h"

namespace Eval {
	const double MAX_SCORE = 100;
	double evaluate(State state);
	bool isStopState(State state);
	int getWinner(State state);
}

#endif