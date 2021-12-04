#pragma once
#include <string>
#include <vector>
#include <utility>


struct Player {
	std::string name;
	std::string color;
	int score = 0;
};

using board_t = std::vector<std::vector<std::pair<char, Player*>>>;

void initBoard(board_t& board, const size_t boardSize);
void showBoard(const board_t& board, const size_t boardSize);
