#pragma once
#include <string>
#include <vector>
#include <utility>
#include <fstream>


typedef struct {
	std::string name;
	std::string color;
	int score;
} Player;

typedef struct {
	std::string word;
	char row;
	char col;
	char direction;
} Turn;

using board_t = std::vector<std::vector<std::pair<char, Player*>>>;

void initBoard(board_t& board, const size_t boardSize);
void showBoard(const board_t& board, const size_t boardSize);

void setBag(std::ifstream& extractFile, std::vector<char>& bag);

void setRack(std::vector<char>& bag, std::vector<char>& rack);
void showRack(const std::vector<char>& rack);

bool valid(const std::string& inputType, const std::string errorMessage, const char terminator);

void readNumPlayers(int& numPlayers);
void readNamePlayers(std::vector<Player>& players, const int& index);

int readWord(std::string& word, std::vector<Player>& players, int& index, int& passTurns, const std::string& dictionary);
void readDirection(char& direction);
void readPosition(char& row, char& col);







