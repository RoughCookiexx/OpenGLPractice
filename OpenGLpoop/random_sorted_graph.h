#pragma once
#include "gl_renderable_graph.h"

class random_sorted_graph :
	public gl_renderable_graph
{
public:
	random_sorted_graph(int node_count, int max_degree);
	~random_sorted_graph(void);
	void create_random_test_graph(int width, int height);
	void sort();
};

