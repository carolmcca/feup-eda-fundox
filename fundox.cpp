#include "fundox.h"
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>

using namespace std;

//colors
const std::string dfltColor	= "\033[0m";
const std::string bgGrey	= "\033[47m";
const std::string red		= "\033[31m";
const std::string blue		= "\033[34m";
const std::string green		= "\033[92m";
const std::string magenta	= "\033[95m";

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

int main() {
	const size_t BOARD_SIZE = 13;
	board_t board(BOARD_SIZE, vector<pair<char, Player*>>(BOARD_SIZE)); //tabuleiro matriz de pares (letra, player)
	vector<Player> players(2); //vetor com os vários jogadores (assim pode ter o tamanho necessário)
	map<char, int> bag; //espécie de vetor que tem uma chave e um valor atribuido à chave, chave - letra, valor - quantidade de letras
	vector<char> rack;


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

	initBoard(board, BOARD_SIZE);

	board[0][3] = pair<char, Player*>('D', &players[0]);
	board[1][3] = pair<char, Player*>('o', &players[0]);
	board[2][3] = pair<char, Player*>('u', &players[0]);
	board[3][3] = pair<char, Player*>('t', &players[0]);
	board[4][3] = pair<char, Player*>('o', &players[0]);
	board[5][3] = pair<char, Player*>('r', &players[0]);
	board[6][3] = pair<char, Player*>('a', &players[0]);
	board[7][3] = pair<char, Player*>('s', &players[0]);
	board[7][5] = pair<char, Player*>('g', &players[0]);

	showBoard(board, BOARD_SIZE);

	return 0;
}

//	//inicializar board
//	//ler número de jogadores
//	//inicializar o vetor com os players - pedir nome e atribuir a cor
//	//ler a posição e a palavra (usar codigo ascii)
//	//verificar se está no ficheiro
//	//verificar se encaixa e há letras suficientes (com cópia da rack) 
//	//meter no board 
//	//atualizar prateleira com novas letras (só acrescentamos as que ainda náo estavam o board né? portanto temos que verificar quais das letras ja estão (?))
//	//mostrar o board
//	//pedir ao jogador seguinte 
//	//repetir
//	//ciclo de jogo: while (pontos<pontos_max || não passar a vez em rondas consecutivas)