#include "DynamicProg.h"
#include <iostream>

void DynamicProg::DynamicTSP(Graph* newGraphData)
{
	int matrixSize = newGraphData->getNumbOfVerts();
	int** btab;
	int** wtfrom;
	int bitPathSize = (1 << matrixSize);
	btab = new int* [bitPathSize];// 1<<matrixSize  zeby pomiescic informacje w postaci bitowej(1010101)
	wtfrom = new int* [bitPathSize];

	//value:koszt dojscia sciezka zawarta w i, z ostatnim wierzcholkiem w j
	for (int i = 0; i < bitPathSize; i++) {
		btab[i] = new int[matrixSize];
		wtfrom[i] = new int[matrixSize];
		for (int j = 0; j < matrixSize; j++) {
			btab[i][j] =( 1 << 30);//999999 *pseudo nieskonczonosc
			wtfrom[i][j] = 99;
		}
	}

	// 0->1 0->2 0->3... 0->(mSize-1)
	for (int i = 0; i < matrixSize; i++) {
		// 1<<i miasto do, +1 miasto z(pocz¹tkowe, 0) 
		btab[(1 << i) | 1][i] = newGraphData->getValueOfEdge(0, i);
		wtfrom[(1 << i) | 1][i] = 0;//
		//w 0 0 jest -1
		if (i == 0) {
			btab[(1 << i) | 1][i] = 0;
		}
		
	}


	for (int bitPath = 0; bitPath < bitPathSize; bitPath++) {
		//dla kazdej sciezki (kombinacji 010101)
		for (int ev=0; ev < matrixSize; ev++) {
			//endVert- vert w ktorym konczymy sciezke
			if (bitPath & (1 << ev)) {
				//w sciezce jest koncowy wierzcholek ev, dla kazdego z mozliwych koncow
				for (int i = 0; i < matrixSize; i++) {
					//szukaj wsrod wszystkich ktore jeszcze mozesz dolaczyc
					if (bitPath & (1 << i)) {
						//juz to mamy(tego juz nei dolaczysz)
					}
					else {
						//nie ma i w sciezce a ev jest czyli tutaj nawet ujemne na srodku mog¹ byc
						//		aktualne value + dojscie do i z ev-specyzowane skad			<	value dla wierzcholka i dla sciezki zawierajacej takie miasta
						if ((btab[bitPath][ev] + newGraphData->getValueOfEdge(ev, i)) < btab[bitPath|(1<<i)][i]) {
							//jak to dojscie bedzie optymalne, to je ustaw na optymalne dla tej sciezki
							// bitPath |(1<<i) to sciezka poszerzona o wierzcholek i
							btab[bitPath | (1 << i)][i] = (btab[bitPath][ev] + newGraphData->getValueOfEdge(ev, i));
							wtfrom[bitPath | (1 << i)][i] = ev;
							//dla danego wierzcholka nalezy zapamietac tez skad
						}
					}
				}

			}	
		}
	}


	//zapelniona tablica z optymalnymi dojsciami do poszczegolnych miast
	int result = (1 << 30);
	int indexQ = 0;
	for (int i = 1; i < matrixSize; i++) {//tutaj zmiana po 2ch browarach, sprawdzic potem czy 1 czy zostawic 0
		//sprawdzenie po wartosciach sciezek zawierajacych wszystkie elementy
		//wraz z dodaniem do nich kosztu powrotu-wyszukanie minimum
		//					"pelne sciezki"				"zapetlenie", powrot
		
		int temp = btab[bitPathSize- 1][i] + (newGraphData->getValueOfEdge(i,0));
		if (temp < result) {
			result = temp;
			indexQ = i;
		}	
	}
	std::cout << "Result : " << result << std::endl;



	int mask = (1 << matrixSize) - 1;//full
	int iter = indexQ;
	int* myTab;
	myTab = new int[matrixSize];
	//myTab[0] = 0;
	//myTab[matrixSize - 1] = iter;
	myTab[0] = 0;
	myTab[matrixSize-1] = iter;
	for (int k = matrixSize - 2; k >0;k--) {
		int poprzednikItera= wtfrom[mask][iter];
		myTab[k] = poprzednikItera;//myTab od : matrixSize - 1 - k
		//dla poprzednika itera odbierz maske----- wytnij itera z maski
		mask = mask - (1 << iter);
		iter = poprzednikItera;
	}
	
	std::cout << "Path: ";//<< indexQ;
	
	for (int i = 0; i < matrixSize; i++) {
		std::cout << myTab[i] << "-->";
	}
	std::cout << "\n";

	
}
