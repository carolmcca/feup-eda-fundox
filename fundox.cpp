#include "fundox.h"
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>

using namespace std;

int main() {

	board_t board(25, vector<pair<char, string>>(25)); //tabuleiro matriz de pares (letra, cor)
	vector<Player> players(2) ; //vetor com os vários jogadores (assim pode ter o tamanho necessário)
	map<char, int> bag; //espécie de vetor que tem uma chave e um valor atribuido à chave, chave - letra, valor - quantidade de letras
	vector<char> rack;

	//cores
	const string defaultColor = "\033[0m";
	const string red = "\033[31m";
	cout << red << "Vermelho" << defaultColor << endl;

	//inicializar board
	//ler número de jogadores
	//inicializar o vetor com os players - pedir nome e atribuir a cor
	//ler a posição e a palavra (fazer um mapa para saber a posição na matriz? Porque recebe aA e tem que ir para [0][0])
	//meter no board
	//verificar se completa alguma palavra
	//atualizar prateleira com novas letras (só acrescentamos as que ainda náo estavam o board né? portanto temos que verificar quais das letras ja estão (?))
	//mostrar o board
	//pedir ao jogador seguinte 
	//repetir
	//ciclo de jogo: while ()

	
	return 0;
}