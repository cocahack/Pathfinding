#include "..\..\eight-puzzle\eight-puzzle\eight-puzzle.h"
#pragma once
#include <chrono>
#include <random>
#include <vector>
#include <cmath>
#include <list>
#define FREE 0
#define WALL 1
#define START 2
#define GOAL 3
#define INF -1
#define N 10
using namespace std;
namespace astar
{
	int random(int min, int max);

		
	struct node
	{
		node() :x{ 0 }, y{ 0 }, parent{ nullptr }, f{ 0.0 }, g{ 0.0 }, h{ 0.0 } {}

		node(int xx, int yy) :x{ xx }, y{ yy }, parent{ nullptr }, f{ 0.0 }, g{ 0.0 }, h{ 0.0 } {}
		node(int xx, int yy, node* p) :x{ xx }, y{ yy }, parent{ p }, f{ 0.0 }, g{ 0.0 }, h{ 0.0 } {}
		~node() {  }

		bool operator==(const node& n) { return x == n.x&&y == n.y; }
		bool operator!=(const node& n) { return !(*this == n); }
		void sum_func() { f = g + h; }
		node* parent;
		int x, y;
		float f, g, h;
	};

	node* set_node(int arr[][N]);


	node* find_and_pop(vector<node*>& openlist);
	void get_successors(int arr[][N], vector<node*>& s, node* c, int mode);
	float straight_distance(node* current, node* successor);
	float straight_distance(node* ptr, int x, int y );
	float right_angled_distance(node* ptr, int x, int y);
	bool is_exist_in_list(vector<node*>& openlist, node* successor);
	node* get_node_in_list(vector<node*>& list, node * successor);
	void print_list(vector<node*>& openlist, vector<node*>& closedlist);
	node* astar_algo(int arr[][N], node* start, int x, int y, int mode, vector<node*>& openlist, vector<node*>& closedlist);
	
	
}
