#pragma once

#include "lib\glfw3.h"
#include "weighted_graph.h"

class input_handler
{
public:
	input_handler(GLFWwindow* window);
	~input_handler(void);
	void handle_event();
	weighted_graph* graph;
	GLFWwindow* window;
};

