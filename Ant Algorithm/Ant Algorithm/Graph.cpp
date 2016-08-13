#include "Graph.h"
#include <fstream>

Graph::Graph(string filename)
{
	read(filename);
	
	for (unsigned i = 0; i < POINTS_NUMBER; i++) {
		Vertice v;
		v.color = 0;
		v.index = i;
		points.push_back(v);
	}
}

void Graph::read(string name)
{
	ifstream f(name);
	string line = "";
	int p1, p2;

	while (getline(f, line))
	{
		if (line == "") break;
		string tmp;

		switch (line[0])
		{
		case 'c':
			continue;
			break;
		case 'p':
			tmp = line.substr(line.find("edge ") + 5);
			POINTS_NUMBER = stoi(tmp.substr(0, tmp.find(" ")));
			EDGES_NUMBER = stoi(tmp.substr(tmp.find(" ") + 1));
			break;
		case 'e':
			tmp = line.substr(line.find("e ") + 2);
			p1 = stoi(tmp.substr(0, tmp.find(" "))) - 1;
			p2 = stoi(tmp.substr(tmp.find(" ") + 1)) - 1;
			edges.push_back(pair<int, int>(p1, p2));

			break;
		default:
			break;
		}
	}
}

void Graph::show()
{
	//for (unsigned i = 0; i < points.size(); i++)
	//	cout << "#" << points[i].index << " color=" << points[i].color << endl;
	cout << "All confs: " << countConfsoverall() << endl;
}

int Graph::countMaxConf() 
{
	int max_conf = 0;

	for (unsigned i = 0; i < POINTS_NUMBER; i++) {
		vector<Vertice *> neighbours = getNeighbours(i);
		int count = 0;

		for (unsigned j = 0; j < neighbours.size(); j++)
			if (neighbours[j]->color == points[i].color)
				count++;
		if (count > max_conf)
			max_conf = count;
	}

	return max_conf;
}

int Graph::countConfsoverall()
{
	int sum = 0;

	for (unsigned i = 0; i < edges.size(); i++)
		if (points[edges[i].first].color == points[edges[i].second].color)
			sum++;

	return sum;
}

double Graph::pn(int iter)
{
	double avgX = countMaxConf();
	double avgY = 4.8*countConfsoverall() / (POINTS_NUMBER * POINTS_NUMBER);

	return exp(-3.2*((5 * iter + 1)*avgY / avgX));
}

Vertice * Graph::maxConfVertice(int cur_index)
{
	int max_conflicts = 0;
	Vertice * v = &points[0];

	for (unsigned i = 0; i < POINTS_NUMBER;  i++) {
		if (i == cur_index) continue;

		vector<Vertice *> neighbours = getNeighbours(points[i].index);
		int count = 0;

		for (unsigned j = 0; j < neighbours.size(); j++)
			if (points[i].color == neighbours[j]->color)
				count++;

		if (count > max_conflicts) {
			max_conflicts = count;
			v = &points[i];
		}
	}

	return v;
}

int Graph::minConfColor()
{
	vector<int> cols(COLORS_SIZE, 0);

	for (unsigned i = 0; i < POINTS_NUMBER; i++) {
		vector<Vertice *> neighbours = getNeighbours(i);

		int count_conf = 0;
		for (unsigned j = 0; j < neighbours.size(); j++)
			if (points[i].color == neighbours[j]->color)
				count_conf++;

		cols[points[i].color] += count_conf;
	}

	int min_conf = cols[0];
	int min_conf_color = 0;
	for (unsigned i = 1; i < COLORS_SIZE; i++)
		if (cols[i] < min_conf) {
			min_conf_color = i;
			min_conf = cols[i];
		}

	return min_conf_color;
}

vector<Vertice>& Graph::getPoints()
{
	return points;
}

vector<pair<int, int>>& Graph::getEdges()
{
	return edges;
}

vector<Vertice *> Graph::getNeighbours(int index)
{
	vector<Vertice *> v = vector<Vertice *>();

	for (unsigned i = 0; i < EDGES_NUMBER; i++) {
		if (edges[i].first == index)
			v.push_back(&points[edges[i].second]);
		if (edges[i].second == index)
			v.push_back(&points[edges[i].first]);
	}
	return v;
}