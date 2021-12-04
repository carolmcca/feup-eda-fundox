//#include "fundox.h"
//#include <iostream>
//#include <vector>
//#include <utility>
//#include <map>
//#include <string>
//
//using namespace std;
//
//int main() {
//
//	board_t board(25, vector<pair<char, string>>(25)); //tabuleiro matriz de pares (letra, cor)
//	vector<Player> players(2); //vetor com os vários jogadores (assim pode ter o tamanho necessário)
//	map<char, int> bag; //espécie de vetor que tem uma chave e um valor atribuido à chave, chave - letra, valor - quantidade de letras
//	vector<char> rack;
//
//
//
//
//	//cores
//	const string defaultColor = "\033[0m";
//	const string red = "\033[31m";
//	cout << red << "Vermelho" << defaultColor << endl;
//
//	//exemplo com player
//	players[0].name = "Carolina";
//	players[0].color = red;
//	players[0].score = 0;
//
//	//exemplo com o map
//
//	bag['A'] = 5;
//	bag['B'] = 3;
//
//	int n = 0;
//	map<char, int>::const_iterator mi = bag.begin();
//
//	cout << (*mi).first << ": " << (*mi).second << endl;
//	cout << mi->first << ": " << mi->second << endl; //igual ao de cima
//
//	for (map<char, int>::const_iterator mi = bag.begin(); mi != bag.end(); mi++) {
//		n++;
//		cout << n << " - " << mi->first << ", " << mi->second << endl;
//	}
//
//	//exemplo com o board
//
//	const int BOARD_SIDE = 8;
//
//	for (int i = 0; i < BOARD_SIDE; i++) {
//		for (int j = 0; j < BOARD_SIDE; j++) {
//			board[i][j].first = '+';
//			board[i][j].second = defaultColor;
//		}
//	}
//
//	board[0][3] = pair<char, string>('D', players[0].color);
//	board[1][3] = pair<char, string>('o', players[0].color);
//	board[2][3] = pair<char, string>('u', players[0].color);
//	board[3][3] = pair<char, string>('t', players[0].color);
//	board[4][3] = pair<char, string>('o', players[0].color);
//	board[5][3] = pair<char, string>('r', players[0].color);
//	board[6][3] = pair<char, string>('a', players[0].color);
//	board[7][3] = pair<char, string>('s', players[0].color);
//	board[7][5] = pair<char, string>('g', players[0].color);
//
//	for (int i = 0; i < BOARD_SIDE; i++) {
//		for (int j = 0; j < BOARD_SIDE; j++) {
//			cout << board[i][j].second;
//			cout << board[i][j].first; //se meter o cout do color antes buga tudo
//		}
//		cout << endl;
//	}
//
//	return 0;
//}