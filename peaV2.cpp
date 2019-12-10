﻿
#include "Branch2.h"
#include "Graph.h"
#include "BF.h"
#include "DynamicProg.h"
#include "Tabu_Search.h"
#include "Simulated_Annealing.h"

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
void BranchAndBoundTest2();
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

void toExcel(std::string fileInputName) {
	//funkcja ta sluzy jedynie do konwersji notacji uzytej przez biblioteke chrono, na format, bezposrednio obsugiwany z excella bez koniecznosci zmiany ustawien
	//----------miniProgram---------------------//
	std::fstream wyniki;
	std::fstream wynikiCor;
	std::string  dataRow;
	std::string fileOutputName = fileInputName;
	std::string tempEx = "EX.txt";
	fileOutputName.append(tempEx);
	wynikiCor.open(fileOutputName, std::ios::out);
	wyniki.open(fileInputName, std::ios::in);
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
void bigConvertToExcel() {
	std::string strTab[1] = { 
	/*"WynikiBF0.txt",
	"WynikiBF1.txt" ,
	"WynikiBF2.txt" ,
	"WynikiBF3.txt" ,
	"WynikiBF4.txt" ,
	"WynikiBF5.txt" ,
	"WynikiBF6.txt" ,*/

	/*"WynikiBNB0.txt" ,
	"WynikiBNB1.txt" ,
	"WynikiBNB2.txt" ,
	"WynikiBNB3.txt" ,
	"WynikiBNB4.txt" ,
	"WynikiBNB5.txt" ,
	"WynikiBNB6.txt" ,*/

	"WynikiDynamic0.txt",
	/*"WynikiDynamic1.txt",
	"WynikiDynamic2.txt",
	"WynikiDynamic3.txt",
	"WynikiDynamic4.txt",
	"WynikiDynamic5.txt",
	"WynikiDynamic6.txt",*/
	};
	for (int i = 0; i < 1; i++) {
		toExcel(strTab[i]);
	}
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
	int tab[1] = { 12 };//15,16,17,18,19,20,21
	int tempProblem = 0;
	for (int j = 0; j < 1; j++) {
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
	int tab[7] = { 15,16,17,18,19,20,21 };
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

void tryToFindBest() {
	Graph* myGraph = new Graph(10);
	Tabu_Search* myTabu = new Tabu_Search();
	int tabx[] = { 0.5,1,2,4,10 };
	int taby[] = { 2,4,8,16 };
	
	int sizes[] = { 20,25,30,40, };
	for (int iter = 0; iter < 4; iter++) {
		for (int wieleRazy = 0; wieleRazy < 10; wieleRazy++) {
			myGraph = new Graph(sizes[iter]);
			myGraph->createRandomGraph();
			int best_result = 1 << 30;
			int bestParB = 0;
			float bestParC = 0;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 4; j++) {
					int result = myTabu->tabuSParam(myGraph, 50, taby[j], tabx[i]);
					if (result < best_result) {
						best_result = result;
						bestParB = taby[j];
						bestParC = tabx[i];
					}
				}
			}
			string fileName;
			//cout << "Podaj nazwe pliku do ktorego chcesz zpaisac graf: ";
			std::string nazwa = "wynikiParametry";
			std::string nazwa2 = std::to_string(sizes[iter]);
			std::string nazwa3 = ".txt";
			nazwa.append(nazwa2);
			nazwa.append(nazwa3);
			fileName = nazwa;
			std::fstream graphOutput;
			graphOutput.open(fileName, ios::app);	//  | ios::app
			if (graphOutput.good() == true) {
				//graphOutput << numbOfVerts << endl;

				graphOutput << bestParB << " " << bestParC;

				graphOutput << endl;

				graphOutput.close();
			}
		}
		
	}
}

void mainMenu() {
	Graph *myGraph = new Graph(10);
	int size = 0;
	int userInput = 999;
	int userTemp=100;
	BF* myBF = new BF();
	DynamicProg* myDynamicProg = new DynamicProg();
	Branch2* myBranch2 = new Branch2();
	Tabu_Search* myTabu = new Tabu_Search();
	Simulated_Annealing* mySA = new Simulated_Annealing();


	while (userInput != 0) {
		std::cout << "----Main Menu--------------------\n";
		std::cout << "Wybierz opcje :\n"
			<< "0. Zakoncz program\n"
			<< "1. Wejdz w tryb Testowy\n"
			<< "2. Wejdz w tryb Sprawdzanie\n"
			<< "3.Przeksztalc wyniki\n";
		std::cin >> userInput;
		switch (userInput) {
		case 3:
			std::cout << "Zaczynam convert...\n";
			bigConvertToExcel();
			std::cout << "Koncze convert!\n";
			break;
		case 0:
			break;
		case 1:
			//testy
			std::cout << "rozpoczynam wielkie testy...\n";
			//bigSimulationBF();
			//bigSimulationDynamicProg();
			//bigSimulationBranchAndBound();
			//tryToFindBest();
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
					<< "6. Przejdz do Branch & Bound\n"
					<< "7. Zmien ustawienia generowania grafu\n"
					<< "8. Tabu Search\n"
					<< "9. SA Wyzarzanie\n";
				std::cin >> userInput;
				switch (userInput)
				{
				case 8:
					while (userInput != 0) {
						std::cout << "-------Menu Tabu Search------------------\n";
						std::cout << "Wybierz opcje :\n"
							<< "0. Wroc do poprzedniego menu \n"
							<< "1. Wykonaj algorytm Tabu Search\n"
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
							//myBF->intitialBrutForce(myGraph);
							myTabu->tabuS(myGraph);
							break;
						case 2:
							myTabu->printResult();
							break;
						case 3:
							myGraph->printGraph();
							break;
						case 4:
							std::cout << "Podaj rozmiar grafu: ";
							std::cin >> size;
							myGraph = new Graph(size);
							myGraph->setRandomParam(userTemp);//Universalne generowanie
							myGraph->createRandomGraph();
							break;
						case 5:
							myGraph->loadGraphFromFile();
							break;
						}
					}
					userInput = 999;
					break;

				case 9:
					//TU UZUUUUUUUPEEEEEEEEEEEEEEEEELNNNNNNNNNNNNNICCCCCCCCCCCCCCCCCCCCCCCCC
					while (userInput != 0) {
						std::cout << "-------Menu SA------------------\n";
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
							//myBF->intitialBrutForce(myGraph);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							mySA->runAlgorithm(myGraph);
							break;
						case 2:
							mySA->printResult();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
							break;
						case 3:
							myGraph->printGraph();
							break;
						case 4:
							std::cout << "Podaj rozmiar grafu: ";
							std::cin >> size;
							myGraph = new Graph(size);
							myGraph->setRandomParam(userTemp);//Universalne generowanie
							myGraph->createRandomGraph();
							break;
						case 5:
							myGraph->loadGraphFromFile();
							break;
						}
					}
					userInput = 999;
					break;
				case 7:
					std::cout << "Zmien generowanie grafu z maxValue:" << userTemp << "\n"
						<< "Na (ppodaj wartosc): ";
					userTemp = 0;
					std::cin >> userTemp;					
					std::cout << "Pomyslnie ustawiono\n";
					break;
				case 0:
					break;
				case 1:
					myGraph->loadGraphFromFile();
					break;
				case 2:
					std::cout << "Podaj rozmiar grafu: ";
					std::cin >> size;
					myGraph = new Graph(size);
					myGraph->setRandomParam(userTemp);//Universalne generowanie
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
							myGraph->setRandomParam(userTemp);//Universalne generowanie
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
							myGraph->setRandomParam(userTemp);//Universalne generowanie
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
							myGraph->setRandomParam(userTemp);//Universalne generowanie
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


void BranchAndBoundTest2() {
	Graph* myGraph = new Graph(3);
	myGraph->loadGraphFromFile();
	Branch2* test = new Branch2();
	test->startAlgorithm(myGraph);
	test->printResult();
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