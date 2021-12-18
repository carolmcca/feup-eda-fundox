#pragma once
#include <string>
#include <vector>
#include <utility>
#include <fstream>


typedef struct {
	std::string name;
	std::string color;
	int score;
	bool gaveUp;
} Player;

typedef struct {
	std::string word;
	int row;
	int col;
	bool isVertical;
} Turn;

typedef enum {
	PASS,
	GIVEUP,
	PLAY
} TurnPlay;

using board_t = std::vector<std::vector<std::pair<char, Player*>>>;

/*void initBoard(board_t& board, const size_t boardSize);
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


void getHalfLine(int& index, int* &row, int* &col, board_t& board, std::string& testWord, std::vector<Player**> &changePlayer, bool changeColor, int step);
std::string getLine(int& index, int* &row, int* &col, board_t& board, const std::string wordPart, std::vector<Player**> &changePlayer, bool changeColor);
bool checkWordPlacement(board_t& board, const Turn& turn, const std::string path, Player& player, std::vector<Player**> &changePlayer);
*/






