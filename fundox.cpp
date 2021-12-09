#include "fundox.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

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

bool valid(const string& inputType, const string errorMessage = "", const char terminator = '\n') {
	if (cin.fail()) {
		cin.clear();
		if (!cin.eof())
			cin.ignore(10000, terminator);
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
}

void readWord(string& word, const vector<Player>& players, const int& index) {
	cout << players[index].color << players[index].name << "'s turn" << dfltColor << endl;
	while (true) {
		cout << "Word: ";
		cin >> word;
		if (valid("cin", "Please insert a valid word.\n"))
			return;
	}
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

void setBag(const string file, vector<char>& bag) { } //Eduarda

void shuffle(vector<char>& bag) { } //Eduarda

void setRack(vector<char>& bag, vector<char>& rack) { } //Mariana

void bubbleSort(vector<char>& v) {
	int length = v.size();
	bool stop = false;

	while (length > 1 && !stop) {

		for (int j = 0; j < length - 1; j++)
			if (v.at(j) > v.at(j + 1)) {
				iter_swap(v.begin() + j, v.begin() + j + 1);
			}
			else {
				stop = true;
			}

		length--;
	}
}

void showRack(vector<char>& rack) { } //Mariana

bool searchWord(string path, string word) {
  bool found = false;
  ifstream words;
  words.open(path);

  while (!words.eof() && !found) {
    string entry;
    words >> entry;
    if (entry == word)
      found = true;
  }
  words.close();
  return found;
}

int main() {
	const size_t BOARD_SIZE = 13;
	const size_t RACK_MAX_SIZE = 7;

	board_t board(BOARD_SIZE, vector<pair<char, Player*>>(BOARD_SIZE)); //tabuleiro matriz de pares (letra, player)
	vector<char> bag; //esp�cie de vetor que tem uma chave e um valor atribuido � chave, chave - letra, valor - quantidade de letras
	vector<char> rack(RACK_MAX_SIZE);
	vector<Player> players;
	int numPlayers;
	int SCORE_MAX = 10; //ATEN��O N�O � PARA FICAR


	initBoard(board, BOARD_SIZE);
	//ler pontos do ficheiro
	// SCORE_MAX = ?;
	//setBag(file, bag);


	//leitura do n� de players
	readNumPlayers(numPlayers);
	players.resize(numPlayers);

	cout << "Please insert the names of the players: \n";
	for (int i = 0; i < numPlayers; i++) {
		readNamePlayers(players, i);
		players[i].color = colors[i];
	}


	int current = numPlayers - 1;
	int passPlays = 0, passRounds = 0;
	Turn turn;
	//n�o esquecer show rack quando desistimos
	while (players[current].score < SCORE_MAX && passRounds < 3 && numPlayers > 1) {
		current = (current + 1) % numPlayers;
		//setRack(bag, rack);
		//showRack(rack);
		showBoard(board, BOARD_SIZE);

		readWord(turn.word, players, current);
		if (turn.word == "P") {
			passPlays++;
			passRounds = passPlays / numPlayers;
			continue; //faltava este acho eu
		}
		else if (turn.word == "G") {
      players.erase(players.begin() + current); // Remove player
      current--;
			numPlayers--;
			continue;
		}
		passPlays = 0;
		for (int i = 0; i < turn.word.length(); i++)
			turn.word[i] = tolower(turn.word[i]); //verificar ficheiro

    string path = "WORDS_EN.txt"; // TODO: string to be read from CONFIG.txt
    searchWord(path, turn.word); // TODO: do something with the return value


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
