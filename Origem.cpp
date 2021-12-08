#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void bubbleSort(vector<char>& v){
	int length = v.size();
	bool stop = false;
	
	while (length > 1 && !stop){

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

void setBag(ifstream& extractFile, vector<char>& bag, vector <char> rack)
{
	 Da primeira vez a fun��o l� o ficheiro e p�e as letras numa ordem aleat�ria
	if (rack.size() == 0)
	{
		char letter;
		int num_occurences;

		while (extractFile >> letter >> num_occurences)
			for (int i = 1; i <= num_occurences; i++)
				bag.push_back(letter);

		for (int i = 0; i < bag.size(); i++)
			cout << bag.at(i);

		cout << endl << endl;

		srand(time(NULL)); // basta fazer uma vez
	}

	 Das vezes seguintes o que tem de entrar � a bag j� com as letras que foram tiradas da rack, para ser s� preciso dar shuffle. 
	 Para isso, � preciso trocar as letras da rack com as �ltimas da bag quando se d� "refresh" na rack

    random_shuffle(bag.begin(), bag.end());

	for (int i = 0; i < bag.size(); i++)
		cout << bag.at(i);

	cout << endl;
}

int main(){
	/* o que vai sair como output:
	 1. bag com as letras todas pela ordem que foram extra�das da file
	 2. bag com as letras em ordem random (d� diferente de todas as vezes)
	 3. simula��o de jogo: j� jogaram muitas vezes, a bag j� s� tem 5 letras (as 5 primeiras pq vamos extraindo do fim para o �nicio para a rack) e � necess�rio dar outro shuffle
	 4. h� uma rack qql que aparece organizada por ordem alfab�tica*/

	vector <char> bag, rack;
	ifstream extractFile("CONFIG.txt");
	string trash, wordFile;
	int winnerPoints;

	if (!extractFile.is_open())
	{
		cout << "File CONFIG.txt not found!" << endl;
		exit(1);
	}

	// Work in progress...
	extractFile.ignore(14);
	extractFile >> winnerPoints;
	/*cout << winnerPoints << endl;*/
	extractFile.ignore(13);
	getline(extractFile, wordFile);
	/*cout << wordFile << endl;*/
	getline(extractFile, trash);

	setBag(extractFile, bag, rack);

	cout << endl;

	extractFile.close();

	bag.resize(5);

	rack = { 'U', 'P', 'A', 'S', 'A', 'T', 'I' };

	bubbleSort(rack);

	setBag(extractFile, bag, rack);
	cout << endl;

	cout << "Sorted rack: " << endl;

	for (int j = 0; j < rack.size(); j++)
		cout << rack.at(j) << " ";

	cout << endl;


	return (0);
}


// //alguns j� devem estar no ficheiro fundox.cpp
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//#include <algorithm>
//
//using namespace std;
//
//void bubbleSort(vector<char>& v)
//{
//	int length = v.size();
//	bool stop;
//
//	while (length > 1)
//	{
//		stop = true;
//
//		for (int j = 0; j < length - 1; j++)
//			if (v.at(j) > v.at(j + 1))
//			{
//				iter_swap(v.begin() + j, v.begin() + j + 1);
//				stop = false;
//			}
//
//		if (stop)
//			break;
//
//		length--;
//	}
//}
//
//void setBag(ifstream& extractFile, vector<char>& bag, vector <char> rack)
//{
//	// Da primeira vez a fun��o l� o ficheiro e p�e as letras numa ordem aleat�ria
//	if (rack.size() == 0)
//	{
//		char letter;
//		int num_occurences;
//
//		while (extractFile >> letter >> num_occurences)
//			for (int i = 1; i <= num_occurences; i++)
//				bag.push_back(letter);
//
//		srand(time(NULL)); // basta fazer uma vez
//	}
//
//	// Das vezes seguintes o que tem de entrar � a bag j� com as letras que foram tiradas da rack, para ser s� preciso dar shuffle. 
//	// Para isso, � preciso trocar as letras da rack com as �ltimas da bag quando se d� "refresh" na rack
//
//	random_shuffle(bag.begin(), bag.end());
//}
//
//int main()
//{
// // alguns destes n�o v�o ser precisos porque j� v�o estar no main
//	vector <char> bag, rack;
//	ifstream extractFile("CONFIG.txt");
//	string trash, wordFile;
//	int winnerPoints;
//
//	if (!extractFile.is_open())
//	{
//		cout << "File CONFIG.txt not found!" << endl;
//		exit(1);
//	}
//
//	// Work in progress... Preciso de discutir isto convosco
//	extractFile.ignore(14);
//	extractFile >> winnerPoints;
//	/*cout << winnerPoints << endl;*/
//	extractFile.ignore(13);
//	getline(extractFile, wordFile);
//	/*cout << wordFile << endl;*/
//	getline(extractFile, trash);
//
//	setBag(extractFile, bag, rack);
//
//	cout << endl;
//
//	extractFile.close();
//
//	// aqui algures define-se a primeira rack (rack = tal e coiso) e enquanto eles jogam a bag vai sofrendo resize
//
//	bubbleSort(rack);
//
//	// fazer setBag(extractFile, bag, rack) quando todos passam uma vez S� DEPOIS de dar reset � rack, TROCANDO os seus elementos com elementos da bag
//
//	return (0);
//}