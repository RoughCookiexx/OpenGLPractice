#include "random_sorted_graph.h"

random_sorted_graph::random_sorted_graph(int num_nodes, int max_degree)
	:gl_renderable_graph(num_nodes,max_degree)
{
}

random_sorted_graph::~random_sorted_graph(void)
{
}

void random_sorted_graph::create_random_test_graph(int width, int height)
{
	
	mtx.lock();
	vertices = new vertex[num_nodes];
	edges = new edge[num_nodes];

	//construct vertices one at a time. 
	for(int i = 0; i < num_nodes; i++)
	{
		struct vertex* v = new struct vertex;
		v->x = ( (std::rand() % width) / (float)width ) * 2 -1; // convert to openGL style positioning (-1.0 to 1.0, -1.0 to 1.0) 
		v->y = 0;
		v->z = 1.0f;//((std::rand() % height)/(float)height)*-2; // (should be done at render time?)

		vertices[i] = *v;
	}

	// create the edges
	for(int i = 0; i < num_nodes; i++)
	{
		edge* new_edge = new edge();
		new_edge->a = &vertices[i];	// reference the data from the vertex data structure.

		vertex *v = new vertex();
		
		v->x = new_edge->a->x;

		new_edge->b = v;
		new_edge->weight = (std::rand() % height) ;
		v->y = new_edge->a->y + (new_edge->weight / (float)(height))-0.5f;
		
		edges[i] = *new_edge;
	}
	mtx.unlock();


}
