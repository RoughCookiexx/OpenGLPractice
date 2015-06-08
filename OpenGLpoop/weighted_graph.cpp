#include "weighted_graph.h"

weighted_graph::weighted_graph(int node_count, int max_degree)
{
	this->node_count = node_count;
	this->max_degree = max_degree;
	vertices = new vertex[node_count];
	edges = new edge[node_count];
}


weighted_graph::~weighted_graph(void)
{
}

// This creates a test graph with VERTEX_COUNT nodes 
void weighted_graph::create_random_test_graph(int width, int height)
{	

	std::ofstream graph_log;
	graph_log.open("graph.txt");
	
	//construct vertices one at a time and link them to the previous. 
	//order doesn't matter. The last one created will be the head node.
	struct vertex* prev = nullptr;
	for(int i = 0; i < node_count; i++)
	{
		struct vertex* v = new struct vertex;
		vertices[i].x = ((std::rand() % width)/(float)width)*2-1; // convert to openGL style positioning (-1.0 to 1.0, -1.0 to 1.0) 
		vertices[i].y = ((std::rand() % height)/(float)height)*2-1; // (should be done at render time?)
		vertices[i].z = ((std::rand() % height)/(float)height)*-2; // (should be done at render time?)


		//graph_log << i << ": (" << v->x << ", " << v->y << ") " << "\n";
	}


	// create the edges
	for(int i = 0; i < node_count; i++)
	{
		int degree = std::rand() % max_degree+1; // ***doesn't check if the connecting nodes are already maxed*** (still soft limits and adds randomness..  .. TODO: leave better notes.)
		if(degree < 1) degree = 1; // do not allow unconnected nodes. 
		graph_log << "Creating edges for node: " << i << " with a degree of: " << degree << "\n";

		edge* prev = nullptr;
		for(int j = 0; j < degree; j++)
		{
			edge* new_edge = new edge();
			new_edge->a = &vertices[i];	// this is duplicate data from the vertex data structure.

			// Limit the distance between nodes.
			float distance;
			vertex* v;
			do
			{
				v = &vertices[std::rand() % node_count];
				float deltaX = abs(new_edge->a->x - v->x);
				float deltaY = abs(new_edge->a->y - v->y);
				float deltaZ = abs(new_edge->a->z - v->z);
				distance = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
			}while(distance > 0.25f);

			new_edge->b = v;
			new_edge->weight = std::rand();
			new_edge->next = prev;
			prev = new_edge;

			graph_log << "a: (" << new_edge->a->x << "," << new_edge->a->y << " b: " << new_edge->b->x << "," << new_edge->b->y << ")\n";
		}
		edges[i] = *prev;
	}
	graph_log.close();
}

