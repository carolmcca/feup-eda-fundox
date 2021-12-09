#pragma once
#include <string>
#include <vector>
#include <utility>


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

bool valid(const std::string& inputType, const std::string errorMessage, const char terminator);

void readNumPlayers(int& numPlayers);
void readNamePlayers(std::vector<Player>& players, const int& index);

void readWord(std::string& word, const std::vector<Player>& players, const int& index);
void readDirection(char& direction);
void readPosition(char& row, char& col);

void setBag(const std::string file, std::vector<char>& bag); //Eduarda

void shuffle(std::vector<char>& bag); //Eduarda

void setRack(std::vector<char>& bag, std::vector<char>& rack); //Mariana

void bubbleSort(std::vector<char>& v); //Eduarda

void showRack(std::vector<char>& rack); //Mariana



