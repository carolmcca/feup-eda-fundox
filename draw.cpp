#include "draw.h"
#include <string>
#include <iostream>
#include "fundox.h"


using namespace std;

void showBoard(board_t board) {
	const int BOARD_SIDE = board.size();
	string letters = "ABCDEFGHIJKLM";
	cout << "    a b c d e f g h i j k l m" << endl;
	for (int i = 0; i < BOARD_SIDE; i++) {
		cout << " " << letters[i] << " " << bgGrey << " ";
		for (int j = 0; j < BOARD_SIDE; j++) {
			cout << board[i][j].second->color;
			cout << board[i][j].first << " ";
		}
		cout << defaultColor << endl;
	}
}