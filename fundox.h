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
	int row;
	int col;
	bool isVertical;
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

bool searchWord(std::string path, std::string word);

int readWord(std::string& word, Player& player, const std::string& dictionary);
void readDirection(Turn& turn);
void readPosition(Turn& turn);
bool connectWords(board_t& board, const Turn& turn, const std::string path, Player& player);







