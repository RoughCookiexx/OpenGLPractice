#pragma once
#include "lib\glew.h"
#include "lib\glfw3.h"
#include "lib\wglew.h"
#include <gl\GL.h>
#include "weighted_graph.h"
#include <mutex>
class graph_renderer
{
public:

	graph_renderer();
	float render(GLFWwindow* window,weighted_graph* graph);
	~graph_renderer(void);
};

