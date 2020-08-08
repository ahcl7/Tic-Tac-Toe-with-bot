#include "state.h"
#include <iostream>
#include "node.h"
#include "evaluate.h"
#include "assert.h"
#include <bitset>

// using namespace std;

void displayBoard(int* board[3]) {
	for(int i = 0 ; i < 3; i++) {
		std::cout << '|';
		for(int j = 0 ; j < 3; j++) {
			if (board[i][j] == 0) std::cout <<"  " << " | ";
			else if (board[i][j] == 1) std::cout << " x" << " | ";
			else std::cout << " o" << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	
}

void testEvaluate() {
	std::bitset<9> x("001000100");
	std::bitset<9> o("010100000");
	State state = State(x, o);
	assert(Eval::evaluate(state) == Eval::MAX_SCORE);
	std::cout << "Correct!";

}
int main() {

	// testEvaluate();
	// return 0;
	int* board[3];
	for(int i = 0 ; i < 3; i++) {
		board[i] = new int[3];
		for(int j = 0 ; j < 3; j ++) {
			board[i][j] = 0;
		}
	}

	State initState = State(0, 0);
	Node* root = new Node(initState);

	std::cout << "Computer calculating..." << std::endl;
	TreeNode::init();
	TreeNode::createTree(root);
	
	std::cout << "Setup done!" << std::endl;
	while (!Eval::isStopState(root->state)) {

		std::cout << "You play: ";
		int x , y;
		std::cin >> x >> y;
		board[x][y] = 2;
		root = TreeNode::move(root, x, y);
		displayBoard(board);
		if (Eval::isStopState(root->state)) {
			std::cout << "You win!";
			return 0;
		}
		int k = TreeNode::getBestMove(root);
		board[k / 3][k % 3] = 1;
		std::cout << "Computer play:" << std::endl;
		displayBoard(board);
		root = TreeNode::move(root, k / 3, k % 3);
		if (Eval::isStopState(root->state)) {
			std::cout << "Computer win!";
			return 0;
		}
		
	}

	std::cout << "Game draw!";

	return 0;
}