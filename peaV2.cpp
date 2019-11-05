
#include "Branch2.h"
#include "Graph.h"
#include "BF.h"
#include "DynamicProg.h"

#include<string>
#include <iostream>
#include<fstream>
#include<ctime>
#include <chrono>

void pomiar_czasu() {
	auto startTest = std::chrono::high_resolution_clock::now();

	auto endTest = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = endTest - startTest;
}
void bforceTest();
void BranchAndBoundTest2(Graph* myGraph);
void testWczytania(Graph* myGraph);

void lastTestBF() {
	//Aktualny stan: zdane
	std::cout << "Test obciazenia pamieci- czy destruktor dziala poprawnie:\n";
	for (int i = 0; i < 100; i++) {
		Graph* myGraph = new Graph(10);
		//myGraph->loadGraphFromFile();
		myGraph->createRandomGraph();
		BF* test = new BF();
		test->intitialBrutForce(myGraph);
		test->printResult();
		//test->printResult();
	}
	std::cout << "Zakońcozno pomyslnie test obciazen\n";
	for (int i = 0; i < 8; i++) {
		Graph* myGraph = new Graph(14);
		myGraph->loadGraphFromFile();
		BF* test = new BF();
		test->intitialBrutForce(myGraph);
		test->printResult();
	}	
}

void lastTestDynamic() {
	//Aktualny stan: okey
	std::cout << "Test obciazenia pamieci- czy destruktor dziala poprawnie:\n";
	Graph* myGraph = new Graph(14);
	DynamicProg* myDyn = new DynamicProg();
	for (int i = 0; i < 100; i++) {	
		myGraph->createRandomGraph();
		myDyn->DynamicTSP(myGraph);
		myDyn->printResult();
	}
	std::cout << "Zakoncozno pomyslnie test obciazen\n";
	for (int i = 0; i < 8; i++) {
		Graph* myGraph = new Graph(14);
		myGraph->loadGraphFromFile();
		DynamicProg* myDyn = new DynamicProg();
		myDyn->DynamicTSP(myGraph);
		myDyn->printResult();
	}
}

void lastTestBranchAndBound() {
	//aktualny stan: ---
	Graph* myGraph = new Graph(10);
	//myGraph->loadGraphFromFile();
	std::cout << "Test obciazenia pamieci- czy destruktor dziala poprawnie:\n";
	for (int i = 0; i < 100; i++) {
		Graph* myGraph = new Graph(13);
		myGraph->createRandomGraph(i);
		Branch2* test = new Branch2();
		test->startAlgorithm(myGraph);
		test->printResult();
	}
	std::cout << "Zakońcozno pomyslnie test obciazen\n";
	for (int i = 0; i < 8; i++) {
		Graph* myGraph = new Graph(14);
		myGraph->loadGraphFromFile();
		//BF* test = new BF();
		Branch2* test = new Branch2();
		test->startAlgorithm(myGraph);
		test->printResult();
	}
}

void toExcel() {
	//----------miniProgram---------------------//
	std::fstream wyniki;
	std::fstream wynikiCor;
	std::string  dataRow;
	wynikiCor.open("wynikiCor.txt", std::ios::out);
	wyniki.open("wyniki.txt", std::ios::in);
	if (wynikiCor.good() && wyniki.good()) {
		for (int i = 0; i < 100; i++) {
			std::getline(wyniki, dataRow);
			int n = dataRow.length();
			char* chArray = &dataRow[0];
			for (int k = 0; chArray[k] != '\0'; k++) {
				if (chArray[k] == 'e') {
					chArray[k] = 'E';
				}
				if (chArray[k] == '.') {
					chArray[k] = ',';
				}
			}
			std::string str(chArray);
			wynikiCor << str << std::endl;
		}
		wyniki.close();
		wynikiCor.close();
	}
	//------------------------------------------------
}

void bigSimulationBF() {
	Graph* testGraph = new Graph(10);
	BF* testBF = new BF();
	int tab[7] = { 6,7,8,9,10,11,12 };
	int tempProblem = 0;
	for (int j = 0; j < 7; j++) {
		tempProblem = tab[j];
		for (int i = 0; i < 100; i++) {
			testGraph = new Graph(tab[j]);
			testGraph->createRandomGraph(i);
			//----
			auto startTest = std::chrono::high_resolution_clock::now();
			testBF->intitialBrutForce(testGraph);
			auto endTest = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = endTest - startTest;
			std::fstream wyniki;
			std::string nazwa= "wynikiBF";
			std::string nazwa2= std::to_string(j);
			std::string nazwa3 = ".txt";
			nazwa.append(nazwa2);
			nazwa.append(nazwa3);

			wyniki.open(nazwa, std::ios::out | std::ios::app);
			if (wyniki.good() == true) {
				wyniki << diff.count() << std::endl;
				wyniki.close();
			}
			//----
		}
	}
}

void bigSimulationDynamicProg() {
	Graph* testGraph = new Graph(10);
	DynamicProg* testDynamicProg = new DynamicProg();
	int tab[7] = { 7,8,9,10,11,12,17 };
	int tempProblem = 0;
	for (int j = 0; j < 7; j++) {
		tempProblem = tab[j];
		for (int i = 0; i < 100; i++) {
			testGraph = new Graph(tab[j]);
			testGraph->createRandomGraph(i);
			//----
			auto startTest = std::chrono::high_resolution_clock::now();
			testDynamicProg->DynamicTSP(testGraph);
			auto endTest = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = endTest - startTest;
			std::fstream wyniki;
			std::string nazwa = "wynikiDynamic";
			std::string nazwa2 = std::to_string(j);
			std::string nazwa3 = ".txt";
			nazwa.append(nazwa2);
			nazwa.append(nazwa3);

			wyniki.open(nazwa, std::ios::out | std::ios::app);
			if (wyniki.good() == true) {
				wyniki << diff.count() << std::endl;
				wyniki.close();
			}
			//----
		}
	}
}

void bigSimulationBranchAndBound() {
	Graph* testGraph = new Graph(10);
	Branch2* testBranch2 = new Branch2();
	int tab[7] = { 6,7,8,9,10,11,12 };
	int tempProblem = 0;
	for (int j = 0; j < 7; j++) {
		tempProblem = tab[j];
		for (int i = 0; i < 100; i++) {
			testGraph = new Graph(tab[j]);
			testGraph->createRandomGraph(i);
			//----
			auto startTest = std::chrono::high_resolution_clock::now();
			testBranch2->startAlgorithm(testGraph);
			auto endTest = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = endTest - startTest;
			std::fstream wyniki;
			std::string nazwa = "wynikiBNB";
			std::string nazwa2 = std::to_string(j);
			std::string nazwa3 = ".txt";
			nazwa.append(nazwa2);
			nazwa.append(nazwa3);

			wyniki.open(nazwa, std::ios::out | std::ios::app);
			if (wyniki.good() == true) {
				wyniki << diff.count() << std::endl;
				wyniki.close();
			}
			//----
		}
	}
}
void mainMenu();
int main()
{
	//Obszar final testow
	//lastTestBF(); ok
	//lastTestDynamic(); ok
	//lastTestBranchAndBound(); ok

	mainMenu();

}


void mainMenu() {
	Graph *myGraph = new Graph(10);
	int size = 0;
	int userInput = 999;
	BF* myBF = new BF();
	DynamicProg* myDynamicProg = new DynamicProg();
	Branch2* myBranch2 = new Branch2();

	while (userInput != 0) {
		std::cout << "----Main Menu--------------------\n";
		std::cout << "Wybierz opcje :\n"
			<< "0. Zakoncz program\n"
			<< "1. Wejdz w tryb Testowy\n"
			<< "2. Wejdz w tryb Sprawdzanie\n";
		std::cin >> userInput;
		switch (userInput) {
		case 0:
			break;
		case 1:
			//testy
			std::cout << "rozpoczynam wielkie testy...\n";
			//bigSimulationBF();
			bigSimulationDynamicProg();
			//bigSimulationBranchAndBound();
			std::cout << "koncze wielkie testy!!!!\n";
			break;
		case 2:
			while (userInput != 0) {
				std::cout << "-------Menu Sprawdzanie------------------\n";
				std::cout << "Wybierz opcje :\n"
					<< "0. Wroc do poprzedniego menu \n"
					<< "1. Laduj graf z pliku\n"
					<< "2. Generuj losowy graf\n"
					<< "3. Wyświetl graf\n"
					<< "4. Przejdz do Brute Force\n"
					<< "5. Przejdz do Dynamic Programming\n"
					<< "6. Przejdz do Branch & Bound\n";
				std::cin >> userInput;
				switch (userInput)
				{
				case 0:
					break;
				case 1:
					myGraph->loadGraphFromFile();
					break;
				case 2:
					std::cout << "Podaj rozmiar grafu: ";
					std::cin >> size;
					myGraph = new Graph(size);
					myGraph->createRandomGraph();
					break;
				case 3:
					myGraph->printGraph();
					break;
				case 4:
					//BruteForce
						//wykonaj
						//wyswietl wynik
						//wyswietl graf
						//generuj losowy(int)
						//laduj z pliku
					while (userInput != 0) {
						std::cout << "-------Menu Brute Force------------------\n";
						std::cout << "Wybierz opcje :\n"
							<< "0. Wroc do poprzedniego menu \n"
							<< "1. Wykonaj algorytm Brute Force\n"
							<< "2. Wyswietl wynik\n"
							<< "3. Wyswietl graf\n"
							<< "4. Generuj losowy graf\n"
							<< "5. Laduj graf z pliku\n";
						std::cin >> userInput;
						switch (userInput)
						{
						case 0:
							break;
						case 1:							
							myBF->intitialBrutForce(myGraph);
							break;
						case 2:
							myBF->printResult();
							break;
						case 3:
							myGraph->printGraph();
							break;
						case 4:
							std::cout << "Podaj rozmiar grafu: ";
							std::cin >> size;
							myGraph = new Graph(size);
							myGraph->createRandomGraph();
							break;
						case 5:
							myGraph->loadGraphFromFile();
							break;
						}
					}
					userInput = 999;
					break;
				case 5:
					//Dynamic Programing
					while (userInput != 0) {
						std::cout << "-------Menu Dynamic Programing------------------\n";
						std::cout << "Wybierz opcje :\n"
							<< "0. Wroc do poprzedniego menu \n"
							<< "1. Wykonaj algorytm Dynamic Programing\n"
							<< "2. Wyswietl wynik\n"
							<< "3. Wyswietl graf\n"
							<< "4. Generuj losowy graf\n"
							<< "5. Laduj graf z pliku\n";
						std::cin >> userInput;
						switch (userInput)
						{
						case 0:
							break;
						case 1:
							myDynamicProg->DynamicTSP(myGraph);
							break;
						case 2:
							myDynamicProg->printResult();
							break;
						case 3:
							myGraph->printGraph();
							break;
						case 4:
							std::cout << "Podaj rozmiar grafu: ";
							std::cin >> size;
							myGraph = new Graph(size);
							myGraph->createRandomGraph();
							break;
						case 5:
							myGraph->loadGraphFromFile();
							break;
						}
						
					}
					userInput = 999;
					break;
				case 6:
					//Branch and bound
					while (userInput != 0) {
						std::cout << "-------Menu Branch And Bound------------------\n";
						std::cout << "Wybierz opcje :\n"
							<< "0. Wroc do poprzedniego menu \n"
							<< "1. Wykonaj algorytm Branch&Bound\n"
							<< "2. Wyswietl wynik\n"
							<< "3. Wyswietl graf\n"
							<< "4. Generuj losowy graf\n"
							<< "5. Laduj graf z pliku\n";
						std::cin >> userInput;
						switch (userInput)
						{
						case 0:
							break;
						case 1:
							myBranch2->startAlgorithm(myGraph);
							break;
						case 2:
							myBranch2->printResult();
							break;
						case 3:
							myGraph->printGraph();
							break;
						case 4:
							std::cout << "Podaj rozmiar grafu: ";
							std::cin >> size;
							myGraph = new Graph(size);
							myGraph->createRandomGraph();
							break;
						case 5:
							myGraph->loadGraphFromFile();
							break;
						}
						
					}
					userInput = 999;
					break;
				}
			}
			userInput = 999;
			break;
		}
	}
}
void testWczytania(Graph* myGraph) {
	myGraph->loadGraphFromFile();
	myGraph->printGraph();
	//DynamicProg* myDyn = new DynamicProg();
	//myDyn->DynamicTSP(myGraph);
	Branch2* test = new Branch2();
	test->startAlgorithm(myGraph);
}


void BranchAndBoundTest2(Graph * myGraph) {
	//Graph* myGraph = new Graph(3);
	//myGraph->loadGraphFromFile();
	Branch2* test = new Branch2();
	test->startAlgorithm(myGraph);
}


void bforceTest() {
	Graph* myGraph = new Graph(3);
	myGraph->loadGraphFromFile();
	BF* test = new BF();
	test->intitialBrutForce(myGraph);
}
void graphtest() {
	std::cout << "Hello World!\n";
	Graph* myGraph = new Graph(4);
	delete myGraph;
	std::cout << "Not bad, but not good still yet...\n";
	myGraph = new Graph(5);
	myGraph->setValueOfEdge(3, 3, 999);
	std::cout << "Value of set edge is: " << myGraph->getValueOfEdge(3, 3) << std::endl;
	system("pause");
	myGraph->createRandomGraph();
	myGraph->printGraph();
	myGraph->saveToFile();

	system("pause");
}