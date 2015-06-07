#pragma once
#include <fstream>
class weighted_graph
{
public:

// An array of linked lists to store the entire graph:
struct edge
{
	struct vertex* a;
	struct edge* next;
	float weight;
}*head_node;


	int node_count;
	int max_degree;
	
	// A simple linked list of points:
	struct vertex
	{
		float x;
		float y;
		struct vertex* next;
	}*head_vertex;

	weighted_graph(int node_count, int max_degree);
	~weighted_graph(void);
	void weighted_graph::create_random_test_graph(int width, int height);
};

