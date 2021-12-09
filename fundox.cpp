#include "fundox.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <random>

using namespace std;

//colors
const std::string dfltColor = "\033[0m";
const std::string bgGrey = "\033[47m";
const std::string red = "\033[31m";
const std::string blue = "\033[34m";
const std::string green = "\033[92m";
const std::string magenta = "\033[95m";
const vector<string> colors = { red, blue, green, magenta };

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
	cout << "    a b c d e f g h i j k l m" << endl;
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

void setRack(vector<char>& bag, vector<char>& rack)
{
	int i;
	const int RACK_SIZE = rack.size();
	for (i = 0; i < 7 - RACK_SIZE; i++) {
		rack.push_back(bag[bag.size()-i-1]);
	}
	sort(rack.begin(), rack.end());
	bag.resize(bag.size() - i);
}

bool valid(const string& inputType, const string errorMessage = "", const char terminator = '\n') {
	if (cin.fail()) {
		if (!cin.eof())
			cin.ignore(10000, terminator);
		cin.clear();
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
	while (true) {
		cout << "Please insert the number of players (2-4): ";
		cin >> numPlayers;
		if (valid("cin") && numPlayers >= 2 && numPlayers <= 4)
			return;
		cout << "The number must be an integer between 2 and 4!" << endl;
	}
}

void readNamePlayers(vector<Player>& players, const int& index) {
	while (true) {
		cout << colors[index] << "Player " << index + 1 << ": ";
		getline(cin, players[index].name); //fiz getline para poder ser mais que um nome (suposto?)
		cout << dfltColor;
		if (valid("getline", "Please insert a valid name\n")) {
			return;
		}
	}
	//verificar se já existe alguém com esse nome?
	//verificar se o nome não é uma string vazia?
}

bool readWord(string& word, const vector<Player>& players) {
		cout << "Word: ";
		cin >> word;
		return valid("cin", "Please insert a valid word.\n");
}

void readDirection(char& direction) {
	bool directionIsValid = false;
	while (true) {
		string expectedValues = "vVhH";
		cout << "Direction(H / V) : ";
		cin >> direction;
		if (valid("cin", "") && expectedValues.find(direction) != string::npos)
			return;
		else
			cout << "The input must be H/h for horizontal or v/V for vertical!\n";
	}
}

void readPosition(char& row, char& col) {
	string rows = "ABCDEFGHIJKLM", cols = "abcdefghijklm";
	char sep;
	string line;
	while (true) {
		cout << "Position of 1st letter (ROW column): " << endl;
		getline(cin, line);
		if (valid("getline", "") && line.size() == 3) {
			if (line[1] == ' ') {
				row = line[0];
				col = line[2];
				if (rows.find(row) != string::npos && cols.find(col) != string::npos)
					return;
				cout << "Error. Example of valid input:\nA b" << endl;
			}
		}
		else {
			cout << "Error. Example of valid input:\nA b" << endl;
		}
	}
}

bool searchWord(string path, string word) {
  bool found = false;
  ifstream wordsFile;
  wordsFile.open(path);
  cout << "path: " << path << endl;

  cout << "is open: " << wordsFile.is_open() << endl;
  if(wordsFile.is_open()){
	  while (!wordsFile.eof() && !found) {
		  string entry;
		  wordsFile >> entry;
		  if (entry == word)
			  found = true;
	  }
	  wordsFile.close();
  }
  
  return found;
}

void showRack(const vector<char> &rack) {
	cout << endl;
	for (int i = 0; i < rack.size(); i++)
		cout << bgGrey << red << rack[i] << " ";
	cout << dfltColor << endl << endl;
}

int main() {
	const size_t BOARD_SIZE = 13;

	board_t board(BOARD_SIZE, vector<pair<char, Player*>>(BOARD_SIZE)); //tabuleiro matriz de pares (letra, player)
	vector<char> bag; 
	vector<char> rack;
	vector<Player> players;
	int numPlayers;
	int SCORE_MAX;
	string path, trash;

	initBoard(board, BOARD_SIZE);
	ifstream extractFile("CONFIG.txt");

	extractFile.ignore(14);
	extractFile >> SCORE_MAX;
	/*cout << SCORE_MAX << endl;*/
	extractFile.ignore(14);
	getline(extractFile, path);

	getline(extractFile, trash);
	setBag(extractFile, bag);


	//leitura do n� de players
	readNumPlayers(numPlayers);
	players.resize(numPlayers);

	cout << "Please insert the names of the players: \n";
	for (int i = 0; i < numPlayers; i++) {
		readNamePlayers(players, i);
		players[i].color = colors[i];
	}


	int current = numPlayers - 1;
	int passTurns = 0, passRounds = 0;
	Turn turn;
	//não esquecer show rack quando desistimos
	while (players[current].score < SCORE_MAX && passRounds < 3 && numPlayers > 1) {
		current = (current + 1) % numPlayers;
		setRack(bag, rack);
		showBoard(board, BOARD_SIZE);
		showRack(rack);
		int attempts = 0;

		cout << players[current].color << players[current].name << "'s turn" << dfltColor << endl;
		while (attempts < 3) {
			if (!readWord(turn.word, players)) {
				attempts++;
				cout << "valid = false\n";
			}
			else {
				cout << "valid true";
				if (turn.word == "P") {
					passTurns++;
					passRounds = passTurns / numPlayers;
					continue; //faltava este acho eu
				}
				else if (turn.word == "G") {
					players.erase(players.begin() + current); // Remove player
					current--;
					numPlayers--;
					continue;
				}
				
				else {
					cout << "n passou nem des\n";
					for (int i = 0; i < turn.word.length(); i++)
						turn.word[i] = tolower(turn.word[i]); //verificar ficheiro
					cout << turn.word << endl;
					if (!searchWord(path, turn.word)) {
						attempts++;
					}
					else 
						break;
				}
			}	

		}
		if (attempts == 3) {
			cout << "3 invalid attempts. You lost your turn.\n";
			continue;
		}
		passTurns = 0;


		readPosition(turn.row, turn.col);
		readDirection(turn.direction);
		//verificar se a palavra encaixa

		//atualizar o board

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
