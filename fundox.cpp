#include "fundox.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <random>
#include <time.h>
#include <algorithm>

using namespace std;

//set colors
const std::string dfltColor = "\033[0m";
const std::string bgGrey = "\033[47m";
const std::string red = "\033[31m";
const std::string blue = "\033[34m";
const std::string green = "\033[92m";
const std::string magenta = "\033[95m";
const std::string black = "\033[30m";
const vector<string> colors = { red, blue, green, magenta };

const int NUM_MAX_ATTEMPTS = 3;
const size_t BOARD_SIZE = 13;

void initBoard(board_t& board, const size_t boardSize) {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j].first = ' ';
			board[i][j].second = nullptr;
		}
	}
}
void showBoard(const board_t& board, const size_t boardSize) {
	string letters = "ABCDEFGHIJKLM";
	cout << "\n    a b c d e f g h i j k l m" << endl;
	for (int i = 0; i < boardSize; i++) {
		cout << " " << letters[i] << " " << bgGrey << " ";
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j].second != nullptr)
				cout << board[i][j].second->color;
			cout << board[i][j].first << " ";
		}
		cout << dfltColor << endl;
	}
}

void setBag(ifstream& extractFile, vector<char>& bag)
{
	char letter;
	int num_occurences;

	while (extractFile >> letter >> num_occurences)
		for (int i = 1; i <= num_occurences; i++)
			bag.push_back(letter);

	srand(time(NULL));
	random_device rd;
	mt19937 g(rd());

	shuffle(bag.begin(), bag.end(), g);
}

void setRack(vector<char>& bag, vector<char>& rack) {
	int i;
	const int RACK_SIZE = rack.size();
	for (i = 0; i < 7 - RACK_SIZE; i++) {
		rack.push_back(bag[bag.size() - i - 1]);
	}
	sort(rack.begin(), rack.end());
	bag.resize(bag.size() - i);
}
void showRack(const vector<char>& rack) {
	cout << endl;
	for (int i = 0; i < BOARD_SIZE + 3 - rack.size(); i++)
		cout << " ";
	cout << bgGrey << black << " ";
	for (int i = 0; i < rack.size(); i++)
		cout << rack[i] << " ";
	cout << dfltColor << endl << endl;
}

bool valid(const string& inputType, const string errorMessage = "", const char terminator = '\n') {
	if (cin.fail()) {
		if (cin.eof()) {
			cin.clear();
		}
		else {
			cin.clear();
			cin.ignore(1000, terminator);
		}
	}
	else if (inputType == "cin") {
		bool correctTerminator = cin.peek() == terminator;
		cin.ignore(10000, terminator);
		if (correctTerminator)
			return true;
	}
	else {
		return true;
	}
	cout << errorMessage;
	return false;
}

void readNumPlayers(int& numPlayers) {
	int i = 0;
	while (i < 3) {
		cout << "Please insert the number of players (2-4): ";
		cin >> numPlayers;
		if (valid("cin") && numPlayers >= 2 && numPlayers <= 4)
			return;
		cout << "The number must be an integer between 2 and 4!" << endl;
		i++;
	}
}
void readNamePlayers(vector<Player>& players, const int& index) {
	while (true) {
		cout << colors[index] << "Player " << index + 1 << ": ";
		getline(cin, players[index].name); //fiz getline para poder ser mais que um nome (suposto?)
		cout << dfltColor;
		if (valid("getline", "Please insert a valid name\n")) {
			if (players[index].name.size() == 0) {
				cout << "Your name will be Player" << index + 1 << endl;
				players[index].name = "Player" + to_string(index + 1);
			}
			return;
		}
	}
}

bool searchWord(string path, string word) {
	bool found = false;
	ifstream wordsFile;
	wordsFile.open(path);

	if (!wordsFile.is_open()) {
		cout << "Error! File '" << path << "' not found.\n";
		exit(1);
	}

	for (int i = 0; i < word.length(); i++)
		word[i] = tolower(word[i]);

	while (!wordsFile.eof() && !found) {
		string entry;
		wordsFile >> entry;
		if (entry == word)
			found = true;
	}
	wordsFile.close();

	return found;
}

int readWord(string& word, Player& player, const string& dictionary) {
	cout << player.color << player.name << "'s turn" << dfltColor << endl;
	int attempts = 0;
	while (attempts < NUM_MAX_ATTEMPTS) {
		cout << "Word: ";
		cin >> word;
		if (!valid("cin", "Please insert a valid word.\n")) {
			attempts++;
		}
		else {
			if (word == "P") {
				return 1;
			}
			else if (word == "G") {
				return 2;
			}
			else {
				if (!searchWord(dictionary, word)) {
					attempts++;
					cout << "The inserted word isn't in the dictionary, please insert a valid word.\n";
				}
				else
					return 3;
			}
		}
	}
	cout << "Maximum number of attempts reached. You lost your turn!\n";
	return 1;
}
void readDirection(Turn& turn) {
	char direction;
	while (true) {
		cout << "Direction(H / V) : ";
		cin >> direction;
		if (valid("cin")) {
			if (direction == 'v' || direction == 'V') {
				turn.isVertical = true;
				return;
			}
			else if (direction == 'h' || direction == 'H') {
				turn.isVertical = false;
				return;
			}
		}
		cout << "The input must be H/h for horizontal or v/V for vertical!\n";
	}
}
void readPosition(Turn& turn) {
	char sep;
	string line;
	while (true) {
		cout << "Position of 1st letter (ROW column): " << endl;
		getline(cin, line);
		if (valid("getline") && line.size() == 3) {
			if (line[1] == ' ') {
				cout << "line[0] = " << line[0] << endl;
				turn.row = int(line[0] - 'A');
				cout << "turn.row = " << turn.row << endl;
				cout << "line[2] = " << line[2] << endl;
				turn.col = int(line[2] - 'a');
				cout << "turn.col = " << turn.col << endl;
				if (0 <= turn.row && BOARD_SIZE > turn.row && 0 <= turn.col && BOARD_SIZE > turn.col)
					return;
				cout << "Error. Example of valid input:\nA b" << endl;
			}
		}
		else {
			cout << "Error. Example of valid input:\nA b" << endl;
		}
	}
}

vector<char> checkExistingLetters(string word, board_t& board, int row, int col, bool& isVertical, vector<char> rack, bool& validPosition) {
	bool spaceExists = false;
	for (int i = 0; i < word.size(); i++)
		word[i] = toupper(word[i]);

	for (int i = 0; i < word.size(); i++) {
		if (row == BOARD_SIZE || col == BOARD_SIZE) {
			cout << "Your word doesn't fit on the board. You lost your turn.\n";
			validPosition = false;
			break;
		}

		if (word[i] != board[row][col].first) {
			if (board[row][col].first == ' ') {
				vector<char>::iterator pos = find(rack.begin(), rack.end(), word[i]);
				if (pos != rack.end()) {
					spaceExists = true;
					rack.erase(pos);
				}
				else {
					cout << "You don't have enough letters on the rack. You lost your turn.\n";
					validPosition = false;
					break;
				}
			}
			else {
				cout << "Your word doesn't fit on the board. You lost your turn! - sobreposition\n";
				validPosition = false;
				break;
			}
		}
		if (isVertical)
			row++;
		else
			col++;
	}
	validPosition = (validPosition && spaceExists);
	return rack;
}

void testHalfLine(int& perpendicularIndex, int* &row, int* &col, board_t& board, string& testedWord, vector<Player**> changeColor, bool changeWordColor, int step) {
	while (perpendicularIndex >= 0 && perpendicularIndex < BOARD_SIZE) {
		cout << "testHaf\n";
		cout << "perpendicularIndex = " << perpendicularIndex << endl;
		cout << "row: " << *row << " col: " << *col << endl;
		if (board[*row][*col].first == ' ') {
			break;
		}
		else {
		testedWord.push_back(board[*row][*col].first);
		if (changeWordColor)
			changeColor.push_back(&(board[*row][*col].second));
		perpendicularIndex += step;
		}
	}
}
bool getLine(int& perpendicularIndex, int* &row, int* &col, board_t& board, const string wordPart, vector<Player**> changeColor, bool changeWordColor) {
	string testedWord;
	perpendicularIndex--;
	testHalfLine(perpendicularIndex, row, col, board, testedWord, changeColor, changeWordColor, -1);
	if (testedWord.length()!=0)
		reverse(testedWord.begin(), testedWord.end());
	testedWord += wordPart;
	perpendicularIndex += testedWord.length() + 1;
	testHalfLine(perpendicularIndex, row, col, board, testedWord, changeColor, changeWordColor, 1);
	cout << "testedWord |" << testedWord << "|\n";
	return testedWord.length() == 1;
}
bool connectWords(board_t& board, const Turn& turn, const string path, Player& player) {
	vector<Player**> changeColor;
	string testedWord;
	bool changeWordColor, isConnected = true;
	int perpendicularIndex, paralelIndex;
	int initialParalelIndex, initialPerpendicularIndex;
	int* row;
	int* col;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].first != ' ') {
				isConnected = false;
				break;
			}
		}
	}

	if (turn.isVertical) {
		initialPerpendicularIndex = turn.row;
		initialParalelIndex = turn.col;
		row = &perpendicularIndex;
		col = &paralelIndex;
	}
	else {
		initialParalelIndex = turn.row;
		initialPerpendicularIndex = turn.col;
		row = &paralelIndex;
		col = &perpendicularIndex;
	}
	

	paralelIndex = initialParalelIndex;
	perpendicularIndex = initialPerpendicularIndex;
	if (getLine(initialPerpendicularIndex, row, col, board, turn.word, changeColor, true)) {
		isConnected = true;
	}

	for (int i = 0; i < turn.word.length(); i++) {
		perpendicularIndex = initialPerpendicularIndex + i;
		paralelIndex = initialParalelIndex;
		changeWordColor = board[*row][*col].first == ' ';

		string letter = { turn.word[i] };
		if (getLine(paralelIndex, col, row, board, letter, changeColor, changeWordColor)) {
			isConnected = true;
		}
	}
	return isConnected;
}


int main() {
	board_t board(BOARD_SIZE, vector<pair<char, Player*>>(BOARD_SIZE)); //tabuleiro matriz de pares (letra, player)
	vector<char> bag;
	vector<char> rack;
	vector<Player> players;
	int numPlayers;
	int SCORE_MAX;
	string dictionaryPath, trash;
	vector<char> possibleRack; //same

	initBoard(board, BOARD_SIZE);

	// Extract maximum score and dictionary's path from file "CONFIG.txt" 
	ifstream extractFile("CONFIG.txt");
	if (!extractFile.is_open()) {
		cout << "File CONFIG.txt not found!" << endl;
		exit(1);
	}
	extractFile.ignore(14);
	extractFile >> SCORE_MAX;
	extractFile.ignore(14);
	getline(extractFile, dictionaryPath);
	getline(extractFile, trash);

	setBag(extractFile, bag);

	readNumPlayers(numPlayers);
	players.resize(numPlayers);

	for (int i = 0; i < numPlayers; i++) {
		readNamePlayers(players, i);
		players[i].color = colors[i];
	}

	int current = numPlayers - 1;
	int passTurns = 0, input;
	Turn turn;
	while (players[current].score < SCORE_MAX && passTurns / numPlayers < 3 && numPlayers > 1) {
		current = (current + 1) % numPlayers;
		setRack(bag, rack);
		showBoard(board, BOARD_SIZE);
		showRack(rack);

		input = readWord(turn.word, players[current], dictionaryPath);
		switch (input) {
		case 1:
			passTurns++;
			continue;
		case 2:
			players.erase(players.begin() + current); // Remove player
			current = (current - 1) % players.size();
			continue;
		case 3:
			passTurns = 0;
		}

		readPosition(turn);
		readDirection(turn);

		bool validPosition = true;
		possibleRack = checkExistingLetters(turn.word, board, turn.row, turn.col, turn.isVertical, rack, validPosition);
		if (validPosition && connectWords(board, turn, dictionaryPath, players[current])) {
			rack = possibleRack;
			for (int i = 0; i < turn.word.length(); i++) {
				if (turn.isVertical) {
					board[turn.row + i][turn.col] = pair<char, Player*>(toupper(turn.word[i]), &players[current]);
				}
				else
					board[turn.row][turn.col + i] = pair<char, Player*>(toupper(turn.word[i]), &players[current]);
			}
		}
		showRack(rack); //just for test
	}
	return 0;
}

//initialiar o tabuleiro (13x13)
//ler numero de pontos do ficheiro
//letras no bag
//desordenar o bag (rand de vetor de n�meros)
//rack (7) - ordem alfab�tica
//pedir o n de jogadores (com cor do jogador) - tem que estar enter 2 e 4
//inicializar vector players (vector com cores) 
//while()
//jogada - palavra, linha, coluna, horizontal/vertical (m ou M) - passar/desistir
//se todos passarem rack feita de novo (volta para o bag) - 
//usar as letras do tabuleiro passam para a cor do jogador e tira pontos ao outro
//repor rack
//fim do jogo: n de pontos/ todos os jogadores passam a vez em 3 rondas seguidas
