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
#include <string>

using namespace std;

const std::string dfltColor = "\033[0m";
const std::string bgGrey = "\033[47m";
const std::string red = "\033[31m";
const std::string blue = "\033[34m";
const std::string green = "\033[92m";
const std::string magenta = "\033[95m";
const vector<string> colors = { red, blue, green, magenta };

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

void readWord(string &word, const vector<Player>& players, const int& index){
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

int main() {
	int numPlayers;
	vector<Player> players;


	//leitura do nº de players
	readNumPlayers(numPlayers);
	players.resize(numPlayers);

	cout << "Please insert the names of the players: \n";
	for (int i = 0; i < numPlayers; i++) {
		readNamePlayers(players, i);
		players[i].color = colors[i];
	}

	int current = numPlayers - 1;
	int passPlays = 0, passRounds = 0;
	string word;
	char row, col, direction;
	//não esquecer show rack quando desistimos
	while (true) {
		current = (current + 1) % numPlayers;

		readWord(word, players, current);
		if (word == "P") {
			passPlays++;
			passRounds = passPlays / numPlayers;
			continue; //faltava este acho eu
		}
		else if (word == "G") {
			numPlayers--;
			continue;
		}
		passPlays = 0;
		for (int i = 0; i < word.length(); i++)
			word[i] = toupper(word[i]); 

		readPosition(row, col);
		readDirection(direction);
		

	}


	
}