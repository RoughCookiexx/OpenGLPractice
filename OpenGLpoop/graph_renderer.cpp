#include "graph_renderer.h"

graph_renderer::graph_renderer()
{
	glEnable(GL_MULTISAMPLE);  
	glEnable(GL_POINT_SMOOTH); // rounds points
}

// All OpenGL drawing is done in here:
float graph_renderer::render(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0f);
	
	gl_renderable_graph* graph = reinterpret_cast<gl_renderable_graph*>(glfwGetWindowUserPointer(window));
	graph->mtx.lock();

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glBegin(GL_POINTS);
	glColor3f(0.7, 0.6, 1.0);
	

	// add vertices to render stack one at a time:
	for(int i = 0; i < graph->num_nodes; i++)
	{
		glVertex3f(graph->vertices[i].x, graph->vertices[i].y,graph->vertices[i].z);
	}
	glEnd();

	// add all edges to the stack:
	glBegin(GL_LINES);
	for(int i = 0; i < graph->num_nodes; i++)
	{
		gl_renderable_graph::edge* render_edge = &(graph->edges[i]);
		
		glColor3f(0.1, 0.6, 7.0);
		
		if(render_edge)
		do
		{
			glVertex3f(render_edge->a->x,render_edge->a->y,render_edge->a->z);
			glVertex3f(render_edge->b->x,render_edge->b->y,render_edge->a->z);
			render_edge = render_edge->next;
		}while(render_edge);
	}
	graph->mtx.unlock();
	glEnd();

    glfwSwapBuffers(window);
	return 0;
}

graph_renderer::~graph_renderer(void)
{
}
