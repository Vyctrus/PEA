#pragma once
class Graph//projected as matrix buddy
{
	private:
		int numbOfVerts = 0; //Number of verticles
		int** matrix;
		void setNumbOfVerts(int number);
	public:
		void printGraph();
		Graph(int numberOfVerticles);
		~Graph();
		void createRandomGraph();
		void createRandomGraph(int addSmth);

		void loadGraphFromFile();
		void saveToFile();

		int getValueOfEdge(int startPoint, int endPoint);
		void setValueOfEdge(int startPoint, int endPoint, int valueToSet);

		int getNumbOfVerts();
		void updateGraph(int newSize);
		


};

