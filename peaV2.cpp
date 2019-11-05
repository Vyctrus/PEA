
#include "Branch2.h"
#include "Graph.h"
#include "BF.h"
#include "DynamicProg.h"

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
int main()
{
	//Obszar final testow
	//lastTestBF(); 
	//lastTestDynamic(); ok
	lastTestBranchAndBound();

	//test przeciązen
	//int temp;
	//Graph* myGraph = new Graph(14);
	//myGraph->createRandomGraph();
	//myGraph->printGraph();
	//std::cin >> temp;
	//DynamicProg *myDyn = new DynamicProg();
		

	/*for (int i = 0; i < 100; i++) {
		myDyn->DynamicTSP(myGraph);
	}*/
	std::cout << "Test wczytania\n";
	Graph* myGraph = new Graph(14);
	testWczytania(myGraph);

}


void mainMenu() {
	int userInput = 999;
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
			break;
		case 2:
			std::cout << "-------Menu Sprawdzanie------------------\n";
			//Sprawdzanie
			//Laduj graf z pliku
			//generuj losowy graf
			//wyswietl graf
			//cofnij do poprzedniego menu
			//uzyj algorytmu brut force->menu
				//wykonaj
				//wyswietl wynik
				//wyswietl graf
				//generuj losowy(int)
				//laduj z pliku
			//uzyj algorytmu dynamic programing->menu
			//uzyj b&b->menu
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