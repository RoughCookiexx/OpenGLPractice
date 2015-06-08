#pragma once
#include <fstream>
#include <vector>
#include <mutex>
class weighted_graph
{
public:

	// A simple point:
	struct vertex
	{
		float x, y, z;
	}*vertices;

	// An array of linked lists to store the entire graph:
	struct edge
	{
		struct vertex* a;
		struct vertex* b;
		struct edge* next;
		float weight;
	}*edges;

	int node_count;
	int max_degree;

	std::mutex mtx;

	weighted_graph(int node_count, int max_degree);
	~weighted_graph(void);
	void weighted_graph::create_random_test_graph(int width, int height);

};

