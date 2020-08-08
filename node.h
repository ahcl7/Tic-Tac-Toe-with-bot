#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <vector>

class Node {
public:
	State state;
	std::vector<Node*> childs;
	double score;
	Node();
	Node(State& _state);
};

namespace TreeNode {
	void init();
	Node* createTree(Node* node); // return the root tree
	Node* move(Node* node, int x, int y);
	int getBestMove(Node* node);
}

#endif