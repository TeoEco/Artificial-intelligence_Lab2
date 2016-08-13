#include "Graph.h"
#include <iostream>
#include <ctime>

#define ANTS_SIZE 5

void init();

int main() {
	init();
	
	system("pause");
	return 0;
}

Graph * min_confsoverall(vector<Graph> & graphs) {
	int min = graphs[0].countConfsoverall();
	Graph * g = &graphs[0];

	for (unsigned i = 1; i < ANTS_SIZE; i++) {
		int tmp = graphs[i].countConfsoverall();
		if (tmp < min) {
			g = &graphs[i];
			min = tmp;
		}
	}

	return g;
}

void init()
{
	const string FILENAME = "yuzGCP13013.txt";
	const double Pc = 0.5;

	vector<Graph> graphs = vector<Graph>(ANTS_SIZE, Graph(FILENAME));
	vector<Vertice *> ants(ANTS_SIZE);
	Graph * best_solution = nullptr;

	for (unsigned i = 0; i < ANTS_SIZE; i++)
		ants[i] = &graphs[i].getPoints()[rand() % graphs[0].POINTS_NUMBER];

	srand((unsigned)time(0));

	int iter = 0;
	while (min_confsoverall(graphs)->countConfsoverall() != 0) {
		for (unsigned i = 0; i < ants.size(); i++) {
			if (rand() % 100 <= 100 * graphs[i].pn(iter)) {
				// Select max conflict
				ants[i] = graphs[i].maxConfVertice(ants[i]->index);
				ants[i]->color = graphs[i].minConfColor();
			}
			else {
				// Select neighbour vertices
				vector<Vertice *> tmp = graphs[i].getNeighbours(ants[i]->index);
				ants[i] = tmp[rand() % tmp.size()];

				if (rand() % 100 <= 100 * Pc)
					ants[i]->color = graphs[i].minConfColor();
			}
		}
		best_solution = min_confsoverall(graphs);
		best_solution->show();
		//printf("%20.18f\n", g.pn(iter));
		//iter++;
	}

	cout << "Graph painted successfully with " << best_solution->countConfsoverall() << " confs." << endl;
}