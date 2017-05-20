#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "astar.h"
using namespace std;
using namespace astar;
int matrix[10][10];
int result[10][10];

void read_txt(ifstream& ifs)
{
	cout << "Initializing.....\n";
	char c{ 0 };
	int i = 0, j = 0;
	int n = 0;
	while (ifs >> c)
	{
		if (c == '\0') break;
		if (c != '\n')
		{
			matrix[i][j] = c - '0';
			++j;
			if (j == 10) { ++i; j = 0; }
		}
	}
}
void get_end(int& x, int& y)
{
	int i, j;
	for (i = 0; i<N; ++i)
		for (j = 0; j < N; ++j)
			if (matrix[i][j] == GOAL) { x = j; y = i; return; }
}
void print_node(node* node)
{
	while (node->parent != nullptr)
	{
		cout << node->x << "\t" << node->y << "\n";
		node = node->parent;
	}
}
void set_result(node* node)
{
	int i, j;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			result[i][j] = matrix[i][j];
	node = node->parent;
	while (node->parent != nullptr)
	{
		result[node->y][node->x] = 8;
		node = node->parent;
	}
}
void out_result(ofstream& ofs)
{
	int i, j;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			ofs << result[i][j];
		}
		ofs << "\n";
	}
	ofs << "\0";
}

void delete_nodes(vector<node*>& v)
{
	int i,len = v.size();
	for (i = 0 ; i < len; ++i) {
		delete v[i];
	}
}
int main()
try{
	ifstream ifs{"input.txt", ios_base::in};
	if (!ifs.is_open()) throw exception("File not exist.");
	read_txt(ifs);
	ifs.close();
	int mode; char c;
	cout << "Select pathfinding mode. (1) Right-angled (2) Diagonal ";
	while (cin >> c)
	{	
		if (c == '1' || c == '2') { mode = c - '0'; break; }
		else {
			cout << "\nCannot input the character except '1' and '2'\n";
			cout << "Select pathfinding mode. (1) Right-angled (2) Diagonal ";
		}
	}
	int x, y; // end point
	get_end(x, y);
	node* start = set_node(matrix);
	vector<node*> openlist;
	vector<node*> closedlist;
	node* path_end = astar_algo(matrix, start, x, y, mode, openlist, closedlist);
	if (path_end != nullptr)
	{
		print_node(path_end);
		set_result(path_end);
		ofstream ofs{ "output.txt",ios_base::out };
		out_result(ofs);
		ofs.close();
	}
	else cout << "There is no way that go to the goal.\n";
	delete_nodes(openlist);
	delete_nodes(closedlist);
	
	return 0;
}
catch(exception e)
{
	cout << e.what() << endl;
}