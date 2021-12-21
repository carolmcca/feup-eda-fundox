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

///*
//* BRIEF: initializes the game board (2D matrix of pairs of(" ", nullptr))
//*/
//void initBoard(board_t& board);
//
///*
//* BRIEF: displays the game board
//*/
//void showBoard(const board_t& board);
//
///*
//* BRIEF: defines the rack - extracts letters from the bag until the rack has 7 letters and orders them alphabeticaly
//*/
//void setRack(std::vector<char>& bag, std::vector<char>& rack, bool restore);
//
///*
//* BREIF: displays the rack
//*/
//void showRack(const std::vector<char>& rack);
//
///*
//* BRIEF: checks if the input stream is OK
//* RETURN: true if the input is of the expected type and false otherwise
//*/
//bool valid(const std::string& inputType, const std::string errorMessage = "", const char terminator = '\n');
//
///*
//* BRIEF: reads the number of players from the keyboard, repeating endlessly if the input is invalid
//*/
//void readNumPlayers(int& numPlayers);
//
///*
//* BRIEF: reads the name of the players from the keyboard, repeating endlessly if the input is invalid
//		 (default name: PlayerX, being X the number of the player)
//*/
//void readNamePlayers(std::vector<Player>& players, const int& index);
//
///*
//* BRIEF: searches for the word on the file indicated by path
//* RETURN: true if the word is on the file and false otherwise
//*/
////bool searchWord(const std::string path, std::string word);
//
///*
//*BRIEF: reads the played word from the keyboard 
//*RETURN: PASS if the player passed or inserted an invalid word more than 3 times, PLAY if the player played or GIVEUP if the player gave up
//*/
//TurnPlay readWord(std::string& word, Player& player, const std::string& dictionary);
//
///*
//*BRIEF: reads the direction of the word (H / V) from the keyboard, repeating endlessly if the input is invalid
//*/
//void readDirection(Turn& turn);
//
///*
//*BRIEF: reads the position of the played word (ROW column) from the keyboard, repeating endlessly if the input is invalid
//*/
//void readPosition(Turn& turn);
//
///*
//*BRIEF: checks if each letter of the word can be placed on the indicated position
//*RETURN: rack without the letters that can be inserted on the board
//*/
//std::vector<char> checkExistingLetters(const board_t& board, Turn& turn, std::vector<char> rack, bool& validPosition, bool& isConnected);