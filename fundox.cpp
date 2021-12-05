#include "fundox.h"
#include <iostream>
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

void setBag(const string file, vector<char>& bag); //Eduarda

void shuffle(vector<char>& bag); //Eduarda

void setRack(vector<char>& bag, vector<char>& rack); //Mariana

void bubbleSort(vector<char>& v); //Eduarda

void showRack(vector<char>& rack); //Mariana

void removePlayer(vector<Player>& players); //Mariana

void verifyInput(); //Carol

int main() {
	const size_t BOARD_SIZE = 13;
	const size_t RACK_MAX_SIZE = 7;

	board_t board(BOARD_SIZE, vector<pair<char, Player*>>(BOARD_SIZE)); //tabuleiro matriz de pares (letra, player)
	vector<char> bag; //espécie de vetor que tem uma chave e um valor atribuido à chave, chave - letra, valor - quantidade de letras
	vector<char> rack(RACK_MAX_SIZE);
	int numPlayers;
	vector<string> colors = { red, blue, green, magenta };
	int SCORE_MAX;


	initBoard(board, BOARD_SIZE);
	//ler pontos do ficheiro
	// SCORE_MAX = ?;
	//setBag(file, bag);

	setRack(bag, rack);

	//função com leitura do número de players ??
	bool validInput = false;
	while (!validInput) {
		cout << "Please insert the number of players (2-4): ";
		cin >> numPlayers;
		if (cin.fail()) {
			if (cin.eof()) {
				cin.clear();
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		else if (cin.peek() != '\n' || numPlayers < 2 || numPlayers > 4) {
			cin.ignore(10000, '\n');
		}
		else {
			cin.ignore(10000, '\n');
			validInput = true;
			continue;
		}
		cout << "Please insert an integer between 2 and 4.\n";
	}

	vector<Player> players(numPlayers); //pomos aqui ou no início e damos resize aqui?


	string name;
	cout << "Please insert the names of the players: \n";
	for (int i = 0; i < numPlayers; i++) {
		validInput = false;
		while (!validInput) {
			cout << colors[i] << "Player " << i + 1 << ": ";
			getline(cin, players[i].name); //fiz getline para poder ser mais que um nome (suposto?)
			if (cin.fail()) {
				if (cin.eof()) {
					cin.clear();
				}
				else {
					cin.clear();
					cin.ignore(10000, '\n');       //verificar se deu ctr+Z depois de meter o nome?
				}
			}
			else {
				validInput = true;
			}
		}
		//verificar length e cin.fail (mudar para while provavelmente)
		players[i].color = colors[i];
	}
	cout << dfltColor;

	showBoard(board, BOARD_SIZE);

	int current = numPlayers - 1;
	int passPlays = 0, passRounds = 0;
	string word;
	char row, column, direction;
	//não esquecer show rack quando desistimos

	while (players[current].score < SCORE_MAX && passRounds < 3 && numPlayers > 1) {
		current = (current + 1) % numPlayers;
		setRack(bag, rack);
		showRack(rack);
		showBoard(board, BOARD_SIZE);

		cout << players[current].color << players[current].name << "'s turn" << dfltColor << endl;
		cout << "Word: ";
		cin >> word;
		cout << word << endl;
		if (cin.fail()) {
			if (cin.eof()) {
				cin.clear();
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
			}
			cout << "Invalid play! You lost your turn...\n";
			continue;
		}
		else if (cin.peek() != '\n') {
			cin.ignore(10000, '\n');
			cout << "Invalid play! You must choose a single word.\n";
			continue;
		}
		else {
			cin.ignore(10000, '\n');
			validInput = true;
			if (word == "P") {
				passPlays++;
				passRounds = passPlays / numPlayers;
				continue; //faltava este acho eu
			}
			else if (word == "G") {
				removePlayer(players);
				numPlayers--;
				continue;
			}
			passPlays = 0;
			for (int i = 0; i < word.length(); i++)
				word.at(i) = toupper(word.at(i)); //verificar ficheiro
		}


		cout << "Position of 1st letter (ROW, column): ";
		cin >> row >> column;
		//cin.fail
		//verificar se a 1a letra da palavra bate com a do board

		cout << "Direction (H/V): ";
		cin >> direction;
		direction = toupper(direction);
		//cin.fail
		//verificar se a palavra encaixa

		//atualizar o board

	}

	return 0;
}

//initialiar o tabuleiro (13x13)
//ler numero de pontos do ficheiro
//letras no bag
//desordenar o bag (rand de vetor de números)
//rack (7) - ordem alfabética
//pedir o n de jogadores (com cor do jogador) - tem que estar enter 2 e 4
//inicializar vector players (vector com cores) 
//while()
//jogada - palavra, linha, coluna, horizontal/vertical (m ou M) - passar/desistir
//se todos passarem rack feita de novo (volta para o bag) - 
//usar as letras do tabuleiro passam para a cor do jogador e tira pontos ao outro
//repor rack
//fim do jogo: n de pontos/ todos os jogadores passam a vez em 3 rondas seguidas
