#pragma once
#include "Graph.h"
class DynamicProg
{
	struct myData {
		int value;
		int from;
	};
public:
	void DynamicTSP(Graph* newGraphData);
};

