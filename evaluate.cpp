#include "evaluate.h"
#include "state.h"

double Eval::evaluate(State state) {
	int winner = Eval::getWinner(state);
	if (!winner) {
		return 0;
	}
	if (winner ^ 1) { // second player is winner
		return -Eval::MAX_SCORE;
	} else return Eval::MAX_SCORE;
}


int Eval::getWinner(State state) {
	bool stopped  = ((state.x & std::bitset<9>(07)) 	== 07);
	stopped      |= ((state.x & std::bitset<9>(070))    == 070);
	stopped 	 |= ((state.x & std::bitset<9>(0700))   == 0700);
	stopped 	 |= ((state.x & std::bitset<9>(0421))   == 0421);
	stopped 	 |= ((state.x & std::bitset<9>(0124))   == 0124);
	stopped 	 |= ((state.x & std::bitset<9>(0111))   == 0111);
	stopped 	 |= ((state.x & std::bitset<9>(0222))   == 0222);
	stopped 	 |= ((state.x & std::bitset<9>(0444))   == 0444);
	if (stopped) return 1;
	stopped 	 |= ((state.o & std::bitset<9>(07))     == 07);
	stopped 	 |= ((state.o & std::bitset<9>(070))    == 070);
	stopped 	 |= ((state.o & std::bitset<9>(0700))   == 0700);
	stopped 	 |= ((state.o & std::bitset<9>(0421))   == 0421);
	stopped 	 |= ((state.o & std::bitset<9>(0124))   == 0124);
	stopped 	 |= ((state.o & std::bitset<9>(0111))   == 0111);
	stopped 	 |= ((state.o & std::bitset<9>(0222))   == 0222);
	stopped 	 |= ((state.o & std::bitset<9>(0444))   == 0444);
	if (stopped) return 2;
	return false;
}

bool Eval::isStopState(State state) {
	int occupicity = state.x.count() + state.o.count();
	if (occupicity == 9 || Eval::getWinner(state)) return true;
	return 0;
}