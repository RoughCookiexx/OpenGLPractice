#include "main.h"

using namespace std;

ofstream debug_file;
graph_renderer *graph_render_pointer;
weighted_graph *graph;
static GLFWwindow* window;


int num_nodes = 4000;
int max_degree = 3;


bool done;

// blatant memory leak:
static void create_new_graph()
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);
	
	graph->mtx.lock();
		graph->create_random_test_graph(w,h);
	graph->mtx.unlock();
} // regularly make destructors.


int main(int argc, char **argv)
{
	FreeConsole();// this just hides the console window

	done = false; //  !done ... just getting started.
	debug_file.open("debug.log");
	debug_file << "Starting Program\n";
	
	graph = new weighted_graph(num_nodes, max_degree);

	// glfw handles a lot. Get it started right away. 
	// it makes this program platform specific. 
	// i'm already working on threading so seperating out any platform specifics early is a must.
	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(1920, 1080, "ALK_Project", glfwGetPrimaryMonitor(), NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	create_new_graph();

	//Start up our main threads:
	thread graphProcessingThread(main::StartGraphProcessingThread);
	thread renderThread(main::StartRenderThread);
	thread inputThread(main::StartInputThread);

	while (!done)
	{
		glfwWaitEvents();
	}
	//Collect main threads:
	graphProcessingThread.join();
	inputThread.join();
	renderThread.join();

	debug_file << "Exiting Main Thread\n";
	debug_file.close();
	return 0;
}


// i honestly don't know how this links. it's magic to me right now and i love it.
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		debug_file << "Key pressed: " +key;
		switch(key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				done = true;
				break;
			case GLFW_KEY_UP:
				num_nodes++;
				break;
			case GLFW_KEY_DOWN:
				num_nodes--;
				break;
			case GLFW_KEY_RIGHT:
				max_degree++;
				break;
			case GLFW_KEY_LEFT:
				max_degree--;
				break;
			case GLFW_KEY_SPACE:
				create_new_graph();
				break;
		}
	}
}


// create an input handler ***
GLdouble fovy;
GLdouble aspect;
GLdouble znear;
GLdouble zfar;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	glMatrixMode(GL_PROJECTION);
	//gluPerspective(
}

void main::StartRenderThread()
{
	debug_file << "Starting Render Thread\n";

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	graph_render_pointer = new graph_renderer();
	while (!glfwWindowShouldClose(window))
	{
		graph_render_pointer->graph_renderer::render(window, graph);
	}
	glfwDestroyWindow(window);
}

void main::StartGraphProcessingThread()
{
	debug_file << "Starting Graph Processing Thread\n";
}

void main::StartInputThread()
{
	debug_file << "Starting Input Thread\n";

	do
	{
		glfwWaitEvents();
	}while(!done);
}
