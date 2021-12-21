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

/**
 * @brief 
 * 
 */
typedef enum {
	PASS,
	GIVEUP,
	PLAY
} TurnPlay;

using board_t = std::vector<std::vector<std::pair<char, Player*>>>;


/**
 * @brief extracts the winning score and the dictionary's path from the file CONFIG.txt
 */
void readConfig(int& scoreMax, std::string& dictionaryPath, std::vector<char>& bag);

/**
* @brief initializes the game board (2D matrix of pairs of(" ", nullptr))
*/
void initBoard(board_t& board);
/**
* @brief displays the game board
*/
void showBoard(const board_t& board);

/**
* 
*/
void setBag(std::ifstream& extractFile, std::vector<char>& bag);

/**
* @brief defines the rack - extracts letters from the bag until the rack has 7 letters and orders them alphabeticaly
*/
void setRack(std::vector<char>& bag, std::vector<char>& rack, bool restore);
/**
* @brief displays the rack
*/
void showRack(const std::vector<char>& rack);

/**
* @brief checks if the input stream is OK
* @return true if the input is of the expected type and false otherwise
*/
bool valid(const std::string& inputType, const std::string errorMessage, const char terminator);
/**
* @brief searches for the word on the file indicated by path
* @return true if the word is on the file and false otherwise
*/
bool searchWord(const std::string& path, std::string word);

/**
* @brief reads the number of players from the keyboard, repeating endlessly untill the input is valid
*/
void readNumPlayers(int& numPlayers);
/**
* @brief reads the name of the players from the keyboard, repeating endlessly untill the input is valid
*		 (default name: PlayerX, being X the number of the player)
*/
void readNamePlayer(std::vector<Player>& players, const int& index);

/**
* @brief reads the played word from the keyboard 
* @return an enum type referent to the nature of the input
*/
TurnPlay readWord(std::string& word, const Player& player, const std::string& dictionary);
/**
* @brief reads the direction of the word (H / V) from the keyboard, repeating endlessly untill the input is valid
*/
void readDirection(Turn& turn);
/**
* @brief reads the position of the played word (ROW column) from the keyboard, repeating endlessly untill the input is valid
*/
void readPosition(Turn& turn);

/**
* @brief checks if the word uses letters of another and if each letter can be placed on the indicated position, that is if the word:
*         doesn't get out of the board limits
*			    doesn't overlap inconsistently with another one 
*			    is writable with the available letters			 
* @return rack without the letters that can be inserted on the board
*/
std::vector<char> checkExistingLetters(const board_t& board, Turn& turn, std::vector<char> rack, bool& validPosition, bool& isConnected);

/**
 * @brief appends to testWord the neighbor chars of (row, col) in the direction indicated by step (-1 to the left, +1 to the right)
 */
void getHalfLine(int& index, int*& row, int*& col, board_t& board, std::string& testWord, std::vector<Player**>& changePlayer, bool changeColor, int step);
/**
 * @brief creates a string (testWord) containing the word formed with the placement of the new char in (*row *col) 
 *			  the analisys direction is indirectly defined through the parameter index (indicates the direction through which the board is iterated)
 * 			  i.e. if the prependicularIndex is passed, the direction of testWord will be the same of played word 
 * @return string testWord
 */
std::string getLine(int& index, int*& row, int*& col, board_t& board, const std::string wordPart, std::vector<Player**>& changePlayer, bool changeColor);

/**
 * @brief checks the word formed in the same direction and all the words formed in the perpendicular direction to the played word. 
 * 			  checks whether or not the word continues through another on the board (isConnected) 
 * @return true if all the formed words are on the dictionary and false otherwise
 */
bool checkWordPlacement(board_t& board, const Turn& turn, const std::string path, Player& player, std::vector<Player**>& changePlayer, bool &isConnected);

/**
 * @brief searches throught the board and, when it finds a letter, adds one point to the score of the player associated with that letter
 */
void updateScores(const board_t& board, std::vector<Player>& players);
/**
 * @brief displays the players' scores
 */
void showScores(const std::vector<Player>& players);

