//#include "fundox.h"
//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//
//using namespace std;
//
//const int BOARD_SIZE = 13;
//
//bool connectWords(board_t& board, const Turn& turn, const string path, Player& player)
//{
//	vector<Player**> changeColor;
//	string testedWord;
//	int perpendicularIndex, paralelIndex;
//	int initialParalelIndex, initialPerpendicularIndex;
//	int* row;
//	int* col;
//
//
//	
//	if (turn.isVertical) {
//		initialParalelIndex = turn.row;
//		initialPerpendicularIndex = turn.col;
//		row = &perpendicularIndex;
//		col = &paralelIndex;
//	}
//	else {
//		initialParalelIndex = turn.col;
//		initialPerpendicularIndex = turn.row;
//		row = &perpendicularIndex;
//		col = &paralelIndex;
//	}
//	
//
//	for (int i = 0; i < turn.word.length(); i++) {
//		perpendicularIndex = i;
//		paralelIndex = initialParalelIndex - 1;
//		while (paralelIndex >= 0) {
//			if (board[*row][*col].first != ' ') {
//				testedWord.push_back(board[*row][*col].first);
//				paralelIndex--; //calhou coco porque não tenho forma de saber qual é o perpendicular e o horizon
//				//ver cores (n tenho cabeça agora)
//			}
//			else {
//				break;
//			}
//		}
//		if (testedWord.length() != 0) {
//			reverse(testedWord.begin(), testedWord.end());
//		}
//		testedWord.push_back(turn.word[i]);
//		while (paralelIndex < BOARD_SIZE) {
//			if (board[*row][*col].first != ' ') {
//				testedWord.push_back(board[*row][*col].first);
//				paralelIndex++; //calhou coco porque não tenho forma de saber qual é o perpendicular e o horizon
//				//ver cores (n tenho cabeça agora)
//			}
//			else {
//				break;
//			}
//		}
//		if (testedWord.length() > 0)
//			if (!searchWord(path, testedWord))
//				return false;
//
//		for (int i = 0; i < turn.word.length(); i++){
//			paralelIndex = initialParalelIndex + i;
//
//			board[*row][*col].first = turn.word[i];
//			board[*row][*col].second = &player;
//		}
//
//		return true;
//	}