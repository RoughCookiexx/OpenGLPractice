#include "main.h"

using namespace std;

ofstream debug_file;
graph_renderer *graph_render_pointer;
weighted_graph *graph;
static GLFWwindow* window;

bool done;



int main(int argc, char **argv)
{
	FreeConsole();// this just hides the console window

	done = false; //  !done ... just getting started.
	debug_file.open("debug.log");
	debug_file << "Starting Program\n";

	graph = new weighted_graph(100, 7);

	// glfw handles a lot. Get it started right away. 
	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	window = glfwCreateWindow(1920, 1080, "ALK_Project", glfwGetPrimaryMonitor(), NULL);
	
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	int w, h;
	glfwGetWindowSize(window, &w, &h);
	graph->create_random_test_graph(w,h);

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


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		done = true;
	}
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
	
    glfwTerminate();
}

void main::StartGraphProcessingThread()
{
	debug_file << "Starting Graph Processing Thread\n";
}

void main::StartInputThread()
{
	debug_file << "Starting Input Thread\n";
	
	//while(!done)
	{
		//glfwWaitEvents();
	}
}
