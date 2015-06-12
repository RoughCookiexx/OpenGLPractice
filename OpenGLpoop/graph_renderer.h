#pragma once
#include "lib\glew.h"
#include "lib\glfw3.h"
#include "lib\wglew.h"
#include <gl\GL.h>
#include "gl_renderable_graph.h"
#include <mutex>
class graph_renderer
{
public:
	float render(GLFWwindow* window);
	graph_renderer(void);
	~graph_renderer(void);

};

