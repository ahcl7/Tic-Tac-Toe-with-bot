#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED


#include <bitset>

struct State {
	std::bitset<9> x, o;
	int getHash() {
		return x.to_ulong() << 9 | o.to_ulong();
	}
	State() {};
	State(int _x, int _o): x(std::bitset<9> (_x)), o(std::bitset<9> (_o)) {};
	State(std::bitset<9> _x, std::bitset<9> _o): x(_x), o(_o){};
};

#endif