#include "gl_renderable_graph.h"



gl_renderable_graph::gl_renderable_graph(int node_count, int max_degree)
{
	mtx.lock();
	this->num_nodes = node_count;
	this->max_degree = max_degree;
	vertices = new vertex[num_nodes];
	edges = new edge[num_nodes];
	mtx.unlock();
}

gl_renderable_graph::~gl_renderable_graph(void)
{

}


void gl_renderable_graph::clear()
{
	for(int i = 0; i < num_nodes; i++)
	{

	}
}