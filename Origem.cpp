#include "fundox.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void connectWords(board_t& board, const Turn& turn, const string path, Player& player)
{
	vector<Player**> changeColor;
	int posDef, analised_position, row, col, aux_row, aux_col;

	// posDef � fixo e vai servir para marcar o comprimento ao longo do qual se l� (linhas se a palavra for vertical, colunas se for horizontal)
	// analised_position marca a dire��o perpendicular; tamb�m � fixo
	// os auxs s�o feios mas n�o arranjei outra forma...

	if (turn.isVertical) {
		posDef = turn.row;
		analised_position = turn.col;
		aux_col = turn.col;
	}
	else	{
		posDef = turn.col;
		analised_position = turn.row;
		aux_row = turn.row;
	}

	for (int i = posDef; i < posDef + turn.word.length(); i++) {
		int j = 1;
		string testedWord;

		// estas vari�veis mudam a cada entrada no for mas n�o mudam dentro do for; marcam a dire��o que deve permanecer fixa em cada caso 
		// (se a palavra for vertical queremos fixar uma linha e andar ao longo dela, por exemplo)
		if (turn.isVertical){
			row = i;
			aux_row = i;
		}
		else{
			col = i;
			aux_col = i;
		}

		// o while � para garantir que n�o sai do board
		// j vai ser um indicador de quantas posi��es atr�s (ao longo da dimens�o m�vel) da letra analisada se encontra o primeiro espa�o (1 no caso de ela n�o ter nada atr�s, por exemplo)
		while (analised_position - j >= 0){
			if (turn.isVertical)
				col = analised_position - j;
			else
				row = analised_position - j;

			if (board[row][col].first != ' ')
				j++;
			else
				break;
		}

		// meter as anteriores

		// percorremos todas as posi��es anteriores com letras e colocamo-las no vetor testedWord, pois s�o elas que v�o constituir a string que queremos verificar se � uma palavra v�lida
		while (j > 1) {
			if (turn.isVertical)
				col = analised_position - j + 1;
			else
				row = analised_position - j + 1;

			testedWord.push_back(board[row][col].first);

			// adicionamos o aopontador para o apontador da cor da letra na posi��o do board avaliada
			// o apontador s� � adicionado se o espa�o que vai ser ocupado pela letra da palavra nova estivesse vazio antes 
			// (se estivesse ocupado n�o pode ser considerado que estamos a formar uma palavra perpendicular � indicada por n�s porque ela j� estava no tabuleiro na jogada anterior)
			if (board[aux_row][aux_col].first == ' ')
				changeColor.push_back(&(board[row][col].second));

			j--;
		}

		// se a palavra nova estiver no fim do tabuleiro, apenas falta adicionar a letra da palavra nova � palavra a ser testada 
		// (apenas se existir alguma coisa para testar, claro)
		if (analised_position == 12) {
			if (testedWord.length() != 0)
				testedWord.push_back(turn.word.at(i - posDef));
		}

		// se n�o estivermos no fim do tabuleiro, fazemos algo an�logo mas depois prosseguimos para as letras seguintes, caso estas existam
		else
		{
			if (turn.isVertical)
				col = analised_position + 1;
			else
				row = analised_position + 1;

			// avan�a se houver letras atr�s (j� estar�o em tested word) ou � frente (a seguir n�o h� um espa�o)
			if (testedWord.length() != 0 || board[row][col].first != ' '){
				// meter a letra da palavra nova
				testedWord.push_back(turn.word.at(i - posDef));

				// meter as letras seguintes, se existirem; j chega sempre aqui a 1
				while (analised_position + j < 13)
				{
					if (turn.isVertical)
						col = analised_position + j;
					else
						row = analised_position + j;

					if (board[row][col].first != ' ')
					{
						testedWord.push_back(board[row][col].first);

						// s� muda a cor se a palavra nova (ex: vertical) estiver a adicionar uma letra nova � palavra testada (mantendo o exemplo, horizontal) e n�o a sobrepuser a uma que j� l� esteja
						if (board[aux_row][aux_col].first == ' ')
							changeColor.push_back(&(board[row][col].second));
						j++;
					}
					else
						break;
				}
			}
		}

		// vemos se a palavra a ser testada � v�lida; se n�o for nada vai acontecer (se calhar � melhor p�r uma mensagem de jogada inv�lida ou assim)
		if (testedWord.length() > 0)
			if (!searchWord(path, testedWord))
				return;
	}

	// s� chega aqui se a jogada for v�lida
	// vamos pegar nas letras que t�m de mudar de cor (que est�o no vetor changeColor) e apontar os lugares correspondentes no board para o player que estiver a jogar
	for (int i = 0; i < changeColor.size(); i++)
		// pq � que n�o d� player* ???
		*(changeColor.at(i)) = &player;

	// aqui, depois de todos os testes feitos, adicionamos as novas letras ao tabuleiro 
	// (tecnicamente adiciona todas as da palavra nova, ou seja, mesmo que j� l� estivessem s�o escritas por cima)
	// os espa�os respetivos s�o atribu�dos ao player atual

	for (int i = posDef; i < turn.word.length() + posDef; i++)
	{
		if (turn.isVertical)
			aux_row = i;
		else
			aux_col = i;

		board[aux_row][aux_col].first = turn.word.at(i - posDef);
		board[aux_row][aux_col].second = &player;
	}

	return;
}