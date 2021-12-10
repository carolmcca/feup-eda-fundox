//#include <vector>
//#include <iostream>
//#include "fundox.h"
//
//using namespace std;
//
//const std::string dfltColor = "\033[0m";
//const std::string bgGrey = "\033[47m";
//const std::string red = "\033[31m";
//const std::string blue = "\033[34m";
//const std::string green = "\033[92m";
//const std::string magenta = "\033[95m";
//const vector<string> colors = { red, blue, green, magenta };
//const int NUM_MAX_ATTEMPTS = 3;
//Turn turn;
//
//void readWord(string &word, vector<Player> &players, int &index, int &passTurns, const string &dictionary) {
//	cout << players[index].color << players[index].name << "'s turn" << dfltColor << endl;
//	int attempts = 0;
//	while (attempts < NUM_MAX_ATTEMPTS) {
//		cout << "Word: ";
//		cin >> word;
//		return ;
//		if (valid("cin", "Please insert a valid word.\n")) {
//			attempts++;
//		}
//		else {
//			if (word == "P") {
//				passTurns++;
//				continue; //faltava este acho eu
//			}
//			else if (word == "G") {
//				players.erase(players.begin() + index); // Remove player
//				index--;
//				continue;
//			}
//
//			else {
//				for (int i = 0; i < word.length(); i++)
//					word[i] = tolower(turn.word[i]); //verificar ficheiro
//				if (!searchWord(dictionary, word)) {
//					attempts++;
//				}
//				else
//					break;
//			}
//		}
//	}
//}


