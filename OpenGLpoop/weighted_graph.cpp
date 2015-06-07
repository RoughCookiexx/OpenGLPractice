#include "weighted_graph.h"



weighted_graph::weighted_graph(int node_count, int max_degree)
{
	head_vertex = new struct vertex();
	this->node_count = node_count;
	this->max_degree = max_degree;
}


weighted_graph::~weighted_graph(void)
{
}

// This creates a test graph with VERTEX_COUNT nodes 
void weighted_graph::create_random_test_graph(int width, int height)
{	

	std::ofstream graph_log;
	graph_log.open("graph.txt");

	//int w,h;
	//glfwGetWindowSize(main_window, &w, &h);
	
	//construct vertices one at a time and link them to the previous. 
	//order doesn't matter. The last one created will be the head node.
	struct vertex* prev = nullptr;
	for(int i = 0; i < node_count; i++)
	{
		struct vertex* v = new struct vertex;
		v->x = ((std::rand() % width)/(float)width)*2-1; // convert to openGL style positioning (-1.0 to 1.0, -1.0 to 1.0)
		v->y = ((std::rand() % height)/(float)height)*2-1;
		v->next = prev;
		prev = v;

		graph_log << i << ": (" << v->x << ", " << v->y << ") " << v->next << "\n";
	}

	head_vertex = prev;

	// create the edges
	for(int i = 0; i < node_count; i++)
	{
		int degree = std::rand() % max_degree;
		if(degree < 1) degree = 1; // do not allow unconnected nodes. 
		for(int j = 0; j < degree; j++)
		{

		}
	}

	graph_log.close();
}
