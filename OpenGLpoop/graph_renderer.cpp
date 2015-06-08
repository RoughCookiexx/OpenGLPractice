#include "graph_renderer.h"

graph_renderer::graph_renderer()
{
	glEnable(GL_MULTISAMPLE);  
	glEnable(GL_POINT_SMOOTH); // rounds points
}

// All OpenGL drawing is done in here:
float graph_renderer::render(GLFWwindow* window, weighted_graph* graph)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0f);
	
	glLoadIdentity();
	glBegin(GL_POINTS);
	glColor3f(0.7, 0.6, 1.0);
	
	// render vertices one at a time.
	for(int i = 0; i < graph->node_count; i++)
	{
		glVertex3f(graph->vertices[i].x, graph->vertices[i].y,graph->vertices[i].z);
	}
	glEnd();

	// render all edges
	glBegin(GL_LINES);
	for(int i = 0; i < graph->node_count; i++)
	{
		weighted_graph::edge* render_edge = &(graph->edges[i]);

		do
		{
			glVertex3f(render_edge->a->x,render_edge->a->y,render_edge->a->z);
			glVertex3f(render_edge->b->x,render_edge->b->y,render_edge->a->z);
			render_edge = render_edge->next;
		}while(render_edge);
	}
	glEnd();

    glfwSwapBuffers(window);
	return 0;
}

graph_renderer::~graph_renderer(void)
{
}
