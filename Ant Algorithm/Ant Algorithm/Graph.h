#pragma once
#include <iostream>
#include <vector>
#include <string>

#define COLORS_SIZE 13

using namespace std;

struct Vertice
{
	int index;
	int color;
};

class Graph
{
private:
	vector<Vertice> points; 
	vector<pair<int, int>> edges;

	int countMaxConf();			// ���-�� ���������� � ��������� ������� ������� �������.
public:
	unsigned POINTS_NUMBER;
	unsigned EDGES_NUMBER;

	Graph(string);

	void read(string name);
	void show();
	double pn(int iter);
	Vertice * maxConfVertice(int except_index);
	int minConfColor();
	int countConfsoverall();	// ����� ���-�� ���������� � ������ ������� (�������)

	vector<Vertice> & getPoints();
	vector<pair<int, int>> & getEdges();
	vector<Vertice *> getNeighbours(int index);
};

