#include "random_sorted_graph.h"

random_sorted_graph::~random_sorted_graph(void)
{
}

void random_sorted_graph::create_random_test_graph(int width, int height)
{
	//std::ofstream graph_log;
	//graph_log.open("graph.txt");
	mtx.lock();
	this->clear();
	vertices = new vertex[num_nodes];
	edges = new edge[num_nodes];
	//construct vertices one at a time. 
	for(int i = 0; i < num_nodes; i++)
	{
		struct vertex* v = new struct vertex;
		v->x = ((std::rand() % width)/(float)width)*2-1; // convert to openGL style positioning (-1.0 to 1.0, -1.0 to 1.0) 
		v->y = ((std::rand() % height)/(float)height)*2-1; // (should be done at render time?)
		v->z = ((std::rand() % height)/(float)height)*-2; // (should be done at render time?)

		vertices[i] = *v;
	}


	// create the edges
	for(int i = 0; i < num_nodes; i++)
	{
		int degree = std::rand() % max_degree+1; // ***doesn't check if the connecting nodes are already maxed*** (still soft limits and adds randomness..  .. TODO: leave better notes.)

		//graph_log << "Creating edges for node: " << i << " with a degree of: " << degree << "\n";

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
				v = &vertices[std::rand() % num_nodes];
				float deltaX = abs(new_edge->a->x - v->x);
				float deltaY = abs(new_edge->a->y - v->y);
				float deltaZ = abs(new_edge->a->z - v->z);
				distance = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
			}while(distance > 0.25f); // not very efficient, but it works for now.

			new_edge->b = v;
			new_edge->weight = std::rand();
			new_edge->next = prev;
			prev = new_edge;

			//graph_log << "a: (" << new_edge->a->x << "," << new_edge->a->y << " b: " << new_edge->b->x << "," << new_edge->b->y << ")\n";
		}
		edges[i] = *prev;
	}
	mtx.unlock();
	//graph_log.close();
}
