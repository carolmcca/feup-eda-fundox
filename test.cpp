#include "fundox.h"
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>

using namespace std;



int main() {

	board_t board(13, vector<pair<char, Player*>>(13)); //tabuleiro matriz de pares (letra, player)
	vector<Player> players(2); //vetor com os vários jogadores (assim pode ter o tamanho necessário)
	map<char, int> bag; //espécie de vetor que tem uma chave e um valor atribuido à chave, chave - letra, valor - quantidade de letras
	vector<char> rack;




	//cores
	

	//exemplo com player
	players[0].name = "Carolina";
	players[0].color = red;
	players[0].score = 0;

	//exemplo com o map

	bag['A'] = 5;
	bag['B'] = 3;

	int n = 0;
	map<char, int>::const_iterator mi = bag.begin();

	cout << (*mi).first << ": " << (*mi).second << endl;
	cout << mi->first << ": " << mi->second << endl; //igual ao de cima

	for (map<char, int>::const_iterator mi = bag.begin(); mi != bag.end(); mi++) {
		n++;
		cout << n << " - " << mi->first << ", " << mi->second << endl;
	}

	//exemplo com o board

	const int BOARD_SIDE = 13;

	for (int i = 0; i < BOARD_SIDE; i++) {
		for (int j = 0; j < BOARD_SIDE; j++) {
			board[i][j].first = ' ';
			board[i][j].second = nullptr;
		}
	}

	board[0][3] = pair<char, Player*>('D', &players[0]);
	board[1][3] = pair<char, Player*>('o', &players[0]);
	board[2][3] = pair<char, Player*>('u', &players[0]);
	board[3][3] = pair<char, Player*>('t', &players[0]);
	board[4][3] = pair<char, Player*>('o', &players[0]);
	board[5][3] = pair<char, Player*>('r', &players[0]);
	board[6][3] = pair<char, Player*>('a', &players[0]);
	board[7][3] = pair<char, Player*>('s', &players[0]);
	board[7][5] = pair<char, Player*>('g', &players[0]);

	

	return 0;
}