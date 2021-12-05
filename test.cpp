//
////exemplo com player
//players[0].name = "Carolina";
//players[0].color = red;
//players[0].score = 0;
//
////exemplo com o map
//
//bag['A'] = 5;
//bag['B'] = 3;
//
//int n = 0;
//map<char, int>::const_iterator mi = bag.begin();
//
//cout << (*mi).first << ": " << (*mi).second << endl;
//cout << mi->first << ": " << mi->second << endl; //igual ao de cima
//
//for (map<char, int>::const_iterator mi = bag.begin(); mi != bag.end(); mi++) {
//	n++;
//	cout << n << " - " << mi->first << ", " << mi->second << endl;
//}
//
////exemplo com o board
//
//initBoard(board, BOARD_SIZE);
//
//board[0][3] = pair<char, Player*>('D', &players[0]);
//board[1][3] = pair<char, Player*>('o', &players[0]);
//board[2][3] = pair<char, Player*>('u', &players[0]);
//board[3][3] = pair<char, Player*>('t', &players[0]);
//board[4][3] = pair<char, Player*>('o', &players[0]);
//board[5][3] = pair<char, Player*>('r', &players[0]);
//board[6][3] = pair<char, Player*>('a', &players[0]);
//board[7][3] = pair<char, Player*>('s', &players[0]);
//board[7][5] = pair<char, Player*>('g', &players[0]);
//
//showBoard(board, BOARD_SIZE);
#include <iostream>
#include <vector>
#include "fundox.h"

using namespace std;

int main() {
	const std::string dfltColor = "\033[0m";
	const std::string bgGrey = "\033[47m";
	const std::string red = "\033[31m";
	const std::string blue = "\033[34m";
	const std::string green = "\033[92m";
	const std::string magenta = "\033[95m";
	bool validInput = false;
	int numPlayers;
	vector<string> colors = { red, blue, green, magenta };

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
	cout << dfltColor << endl;

	int passPlays = 0;
	int passRounds = 0;
	int current = 0;
	string word;
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
		//continue;
	}
	else if (cin.peek() != '\n') {
		cin.ignore(10000, '\n');
		cout << "Invalid play! You must choose a single word.\n";
		//continue;
	}
	else {
		cin.ignore(10000, '\n');
		validInput = true;
		if (word == "P") {
			passPlays++;
			passRounds = passPlays / numPlayers;
			//continue; //faltava este acho eu
		}
		else if (word == "G") {
			//removePlayer(players);
			numPlayers--;
			//continue;
		}
		//passPlays = 0;
		for (int i = 0; i < word.length(); i++)
			word.at(i) = toupper(word.at(i)); //verificar ficheiro
	}


	cout << passPlays << endl;
	cout << passRounds << endl;
	cout << numPlayers << endl;
}

