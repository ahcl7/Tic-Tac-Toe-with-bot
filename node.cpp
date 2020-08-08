#include <map>
#include <bitset>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "state.h"
#include "node.h"
#include "evaluate.h"

Node::Node() {

}

Node::Node(State& _state): state(_state) {}



const int NUMBER_OF_STATE = 1 << (2 * 9);
Node* nodes[NUMBER_OF_STATE];


void TreeNode::init() {
	memset(nodes, 0, sizeof(nodes));

}
Node* TreeNode::createTree(Node* node) {
	if (Eval::isStopState(node->state)) {
		node->score = Eval::evaluate(node->state);
		return node;
	}
	std::vector<Node*> childs;
	bool turn = ((node->state.x.count() + node->state.o.count()) & 1);
	std::bitset<9> xo[2] = {node->state.x, node->state.o};

	if (!turn) node->score = -Eval::MAX_SCORE;
	else node->score = Eval::MAX_SCORE;

	int bf = node->state.getHash();
	for(int i = 0 ; i < 9; i++) {
		if (!xo[turn].test(i) && !xo[turn ^ 1].test(i)) {
			xo[turn].set(i);
			State newState = State(xo[0], xo[1]);
			int hash = newState.getHash();
			assert(hash < (1 << 18));
			if (nodes[hash]) {
				childs.push_back(nodes[hash]);
			} else {
				Node* p = new Node(newState);
				nodes[hash] = p;
				childs.push_back(p);
				createTree(childs.back());
			}
			if (!turn) node->score = std::max(node->score, childs.back()->score);
			else node->score = std::min(node->score, childs.back()->score);
			xo[turn].reset(i);
		}
	}
	node->childs = childs;
	return node;
}

Node* TreeNode::move(Node* node, int x, int y) {
	bool turn = ((node->state.x.count() + node->state.o.count()) & 1);
	State newState = State(node->state.x, node->state.o);
	if (!turn) newState.x |= (1 << (x * 3 + y));
	else newState.o |= (1<< (x * 3 + y));
	int hash = newState.getHash();
	return nodes[hash];
}

int TreeNode::getBestMove(Node* node) {
	bool turn = ((node->state.x.count() + node->state.o.count()) & 1);
	std::vector<int> poss;
	for(auto& p:node->childs) {
		if (p->score == node->score) {
			std::bitset<9> tmp = p->state.x ^ node->state.x ^ p->state.o ^ node->state.o;
			for(int i = 0 ; i < 9; i++) {
				if (tmp.test(i)) poss.push_back(i);
			}
		}
	}

	srand(time(0));
	return poss[rand()%((int) poss.size())];
	assert(false);
	return 0;
}