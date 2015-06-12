#include "input_handler.h"



input_handler::input_handler(GLFWwindow* window)
{
	this->window = window;
	graph = reinterpret_cast<weighted_graph*>(glfwGetWindowUserPointer(window));
	glfwMakeContextCurrent(window);
}


input_handler::~input_handler(void)
{
}



GLdouble fovy;
GLdouble aspect;
GLdouble znear;
GLdouble zfar;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	glMatrixMode(GL_PROJECTION);
	//gluPerspective(
}

void input_handler::handle_event()
{
	//glfwMakeContextCurrent(window);

		glfwWaitEvents();
		glfwWaitEvents();
}