#pragma once
#include <fstream>
#include "gl_renderable_graph.h"
class weighted_graph :
	public gl_renderable_graph
{
public:
	weighted_graph(int node_count, int max_degree);
	~weighted_graph(void);
	void create_random_test_graph(int width, int height);
};

