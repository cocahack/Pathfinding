#include "astar.h"
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>

using namespace astar;
int astar::random(int min, int max)
{
	std::random_device rn;
	std::mt19937_64 rnd(rn());
	std::uniform_int_distribution<int> range{ min, max };
	return range(rnd);
}

node * astar::set_node(int arr[][N])
{
	int i, j;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			if (arr[i][j] == START) return new node{j,i};
	return nullptr;
}

/*
This function is that find node that has lowest f in openlist and pop that.
!!Caution: The argument can be manipulated.
*/
node* astar::find_and_pop(vector<node*>& openlist)
{
	int len = openlist.size();
	int loc = 0;
	node* returnval = nullptr;
	float lowest = 0.0;
	for (int i=0; i < len; ++i)
	{
		if (openlist[i]->f <= lowest)
		{
			lowest = openlist[i]->f;
			loc = i;
		}
	}
	returnval = openlist[loc];
	openlist.erase(openlist.begin()+loc);
	return returnval;
}

void astar::get_successors(int arr[][N], vector<node*>& s, node * c, int mode)
{
	int x = c->x;
	int y = c->y;	
	if (x - 1 > -1 && arr[y][x - 1] != WALL)
		s.push_back(new node{ x - 1,y, c });
	if (x + 1 < 10 && arr[y][x + 1] != WALL)
		s.push_back(new node{ x + 1,y,c });
	if (y - 1 > -1 && arr[y - 1][x] != WALL)
		s.push_back(new node{ x, y - 1,c });
	if (y + 1 < 10 && arr[y + 1][x] != WALL)
		s.push_back(new node{ x,y + 1,c});
	if (mode == 2)
	{
		if (x - 1 > -1 && y - 1 > -1 && arr[y - 1 ][x - 1] != WALL)
			s.push_back(new node{ x - 1,y - 1, c });
		if (x + 1 < 10 && y - 1 > -1 && arr[y - 1][x + 1] != WALL)
			s.push_back(new node{ x + 1,y - 1 ,c });
		if (x - 1 > -1 && y + 1 > -1 && arr[y + 1][x - 1] != WALL)
			s.push_back(new node{ x - 1, y + 1,c });
		if (x + 1 < 10 && y + 1 < 10 && arr[y + 1][x + 1] != WALL)
			s.push_back(new node{ x + 1,y + 1,c });
	}
}

float astar::straight_distance(node * current, node * successor)
{
	return sqrtf(pow(abs(current->x - successor->x), 2) + pow(abs(current->y - successor->y), 2));
}

float astar::straight_distance(node * ptr, int x, int y)
{
	return sqrtf(pow(abs(ptr->x - x), 2) + pow(abs(ptr->y - y), 2));
}

float astar::right_angled_distance(node * ptr, int x, int y)
{
	return abs(ptr->x-x)+abs(ptr->y-y);
}

bool astar::is_exist_in_list(vector<node*>& openlist, node * successor)
{
	int len = openlist.size();
	for (int i = 0; i < len; ++i)
		if ((*openlist[i]) == (*successor)) return true;
	return false;
}

node * astar::get_node_in_list(vector<node*>& list, node * successor)
{
	int len = list.size();
	for (int i = 0; i < len; ++i)
		if ((*list[i]) == (*successor)) return list[i];
	return nullptr;
}

void astar::print_list(vector<node*>& openlist, vector<node*>& closedlist)
{
	cout << "<--------- open list --------->\n\n";
	for (int i = 0; i < openlist.size(); ++i)
		cout << "x: " << openlist[i]->x << " y: " << openlist[i]->y << " f: " << openlist[i]->f << "\n";
	cout << "<--------- open list end --------->\n\n";
	cout << "<--------- closed list --------->\n\n";
	for (int i = 0; i < closedlist.size(); ++i)
		cout << "x: " << closedlist[i]->x << " y: " << closedlist[i]->y << " f: " << closedlist[i]->f << "\n";
	cout << "<--------- closed list end --------->\n\n";
}

node * astar::astar_algo(int arr[][N], node * start, int x, int y, int mode, vector<node*>& openlist, vector<node*>& closedlist)
{
	vector<node*> successors;
	start->h = straight_distance(start,x,y);
	start->sum_func();
	openlist.push_back(start);
	node* endnode{ nullptr };

	node* current{ nullptr };
	node* same_in_open{ nullptr };
	node* same_in_closed{ nullptr };
	int loc = 0;
	float f = 0.0;
	while (openlist.size() != 0)
	{
		current = find_and_pop(openlist);
		get_successors(arr,successors, current, mode);
		for (int i = 0; i < successors.size(); ++i)
		{
			if (successors[i]->x == x&&successors[i]->y == y) 
				return successors[i];
			successors[i]->g = current->g + straight_distance(current, successors[i]);
			if(mode == 2)
				successors[i]->h = straight_distance(successors[i],x,y);
			if(mode == 1)
				successors[i]->h = right_angled_distance(successors[i], x, y);
			successors[i]->sum_func();
		}
		for (int i = 0; i < successors.size(); ++i)
		{
			same_in_open = get_node_in_list(openlist, successors[i]);
			same_in_closed = get_node_in_list(closedlist, successors[i]);
			if (same_in_open) {
				if (same_in_open->g > successors[i]->g) {
					same_in_open->g = successors[i]->g;
					same_in_open->parent = successors[i]->parent;
					same_in_open->sum_func();
				}
				else continue;
			}
			else if (same_in_closed) {
				continue;
			}
			else 
				openlist.push_back(successors[i]);
			
		}	
		closedlist.push_back(current);
		successors.erase(successors.begin(), successors.end());
	}

	return endnode;
}



