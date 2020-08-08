#include <bitset>
#include <string.h>
#include <iostream>

#include "state.h"
#include "node.h"
#include "evaluate.h"
#include "assert.h"

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



void youMove(Node*& root, int** board, int turn) {
	if (Eval::isStopState(root->state)) return;
	std::cout << "You play: ";
	int x , y;
	std::cin >> x >> y;
	board[x][y] = turn;
	root = TreeNode::move(root, x, y);
	displayBoard(board);
	if (Eval::getWinner(root->state)) {
		std::cout << "You win!";
		exit(0);
	}
}

void computerMove(Node*& root, int** board, int turn) {
	if (Eval::isStopState(root->state)) return;
	int k = TreeNode::getBestMove(root);
	board[k / 3][k % 3] = turn;
	std::cout << "Computer play:" << std::endl;
	displayBoard(board);
	root = TreeNode::move(root, k / 3, k % 3);
	if (Eval::getWinner(root->state)) {
		std::cout << "Computer win!";
		exit(0);
	}
}


int main() {
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


	std::cout << "Do you want to play first?" << std::endl;

	std::string s;
	std::cin >> s;

	bool first = false;
	if (s == "Y" || s == "y" || s == "yes" || s == "YES") first = true;
	while (!Eval::isStopState(root->state)) {
		if (first) {
			youMove(root, board, 1);
			computerMove(root, board, 2);
		} else {
			computerMove(root, board, 1);
			youMove(root, board, 2);
		}
	}

	std::cout << "Game draw!";

	return 0;
}