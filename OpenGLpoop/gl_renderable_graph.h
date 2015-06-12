#pragma once
#include <mutex>

class gl_renderable_graph
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
		int weight; // change to pointer to vertex information?
	}*edges;

	int num_nodes;
	int max_degree;

	std::mutex mtx;

	gl_renderable_graph(int node_count, int max_degree);
	~gl_renderable_graph(void);
	void clear();

	virtual void create_random_test_graph(int width, int height)=0;
};