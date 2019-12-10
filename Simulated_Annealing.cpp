#include "Simulated_Annealing.h"

vector<int> Simulated_Annealing::makeRandPermut(int size_of_permutation)
{
	vector<int> newRandPermut;
	newRandPermut.reserve(size_of_permutation);
	for (int i = 0; i < size_of_permutation; ++i) {
		newRandPermut.push_back(i);
	}
	random_shuffle(newRandPermut.begin(), newRandPermut.end());

	return newRandPermut;
}

void Simulated_Annealing::runAlgorithm(Graph* newGraphData)
{
	matrixSize = newGraphData->getNumbOfVerts();
	permutation = makeRandPermut(matrixSize);//punkt startowy(losowy)
	nextPermut = vector<int> (permutation);

	float COOLING = 0.95;
	int howMany = 100;// ile razy algorytm sie wywola aby uzyskac rozne wyniki	A 10-1000
	int totalSteps = matrixSize * 3;//ile sily jeszcze dysponujemy, ilosc krokow jakie jeszcze mozemy robic	B 2-50
	//int cadence = matrixSize * 1;//na jak dlugo zostaje zablokowany dany ruch	C 1/4 - 10

	for (int i = 0; i < howMany; ++i) { //wykonania algorytmu
		while (temperature >= 0.1) {
			int number_of_steps = totalSteps;
			nextPermut = permutation;

			int costOfPermut = 0;//liczenie kosztu sciezki przed swap'em
			for (int i = 0; i < matrixSize - 1; i++) {
				//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
				costOfPermut += newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
			}
			// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
			costOfPermut += newGraphData->getValueOfEdge(permutation[matrixSize - 1], permutation[0]);
			

			for (; number_of_steps > 0; number_of_steps--) {
				int firstPos = rand() % matrixSize;   // potencjalne pozycja do zamiany
				int secondPos = rand() % matrixSize;

				swap(nextPermut[firstPos], nextPermut[secondPos]);//sprobuj przejsc dalej

				costOfPermut = 0;//liczenie kosztu sciezki po swap'ie
				for (int i = 0; i < matrixSize - 1; i++) {
					//---------------------------- (1->2->4->7->3->....) licz przeskok z 1->2, potem kolejny,
					costOfPermut += newGraphData->getValueOfEdge(nextPermut[i], nextPermut[(i + 1)]);
				}
				// (Y . . . X), X->Y pol¹cz koniec z poczatkiem aby zamknac cykl
				costOfPermut += newGraphData->getValueOfEdge(nextPermut[matrixSize - 1], nextPermut[0]);

				int diffrence = result - costOfPermut;//roznica rozwiazan najlepszego i aktualnie rozpatrywanego

				if (diffrence > 0) {
					result = costOfPermut;
					bestResult = nextPermut;//przypisz najlepsze rozwiazanie- znalazles teraz
				}
				if (diffrence > 0 || (diffrence < 0 && exp(diffrence / temperature) >((double)rand() / RAND_MAX) + 1)) {//warunek akceptacji
					permutation = nextPermut;//zaakceptuj przejscie, przejdz
					break;
				}
				else {
					swap(nextPermut[firstPos], nextPermut[secondPos]);//cofnij sie, wykonuj dalej
				}

			}

			
			temperature *= COOLING;
		}

		temperature = 1<<16;
		permutation = makeRandPermut(matrixSize);
	}

	cout << "Result: " << result<<"\n";

}

void Simulated_Annealing::printResult()
{
	std::cout << "Result : " << result << std::endl;

	std::cout << "Path: ";//<< indexQ;
	for (int i = 0; i < matrixSize; i++) {
		//bestResult
		//newGraphData->getValueOfEdge(permutation[i], permutation[(i + 1)]);
		std::cout << bestResult[i] << "-->";
	}
	std::cout << bestResult[0]<<"\n";
}
