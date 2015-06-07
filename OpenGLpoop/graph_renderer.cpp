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
	glPointSize(5.0f);
	
        glLoadIdentity();
	glBegin(GL_POINTS);
	glColor3f(0.7, 0.6, 1.0);
	weighted_graph::vertex* v = graph->head_vertex;
	
	// render vertices one at a time.
	for(int i = 0; i < graph->node_count; i++)
	{
		glVertex2f(v->x, v->y);
		if(v->next != nullptr)
			v = v->next;
	}
	glEnd();
    glfwSwapBuffers(window);
	return 0;
}

graph_renderer::~graph_renderer(void)
{
}
