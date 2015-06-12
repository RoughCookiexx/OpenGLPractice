#include "main.h"

using namespace std;

ofstream debug_file;
graph_renderer *graph_render_pointer;
gl_renderable_graph *graph;
input_handler *input;
static GLFWwindow* window;

int num_nodes = 1000;
int max_degree = 3;

bool done;

// This handles all mapped key input.
// It is linked in the main thread for now.
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		weighted_graph* graph = reinterpret_cast<weighted_graph*>(glfwGetWindowUserPointer(window));
		//debug_file << "Key pressed: " +key;
		switch(key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			case GLFW_KEY_UP:
				num_nodes++;
				break;
			case GLFW_KEY_DOWN:
				num_nodes--;
				break;
			case GLFW_KEY_RIGHT:
				graph->max_degree++;
				break;
			case GLFW_KEY_LEFT:
				graph->max_degree--;
				break;
			case GLFW_KEY_SPACE:
				int w, h;
				glfwGetWindowSize(window, &w, &h);
				//graph->clear();
				graph->create_random_test_graph(w,h);
				break;
		}
	}
}

int main(int argc, char **argv)
{
	FreeConsole();// this just hides the console window

	done = false; //  !done ... just getting started.
	debug_file.open("debug.log");
	debug_file << "Starting Program\n";

	// glfw handles a lot. Get it started right away. 
	// it makes this program platform specific. 
	// i'm already working on threading so seperating out any platform specifics early is a must.
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// This gives us a pointer to our data which we can use at any point:
	window = glfwCreateWindow(1920, 1080, "ALK_Project", glfwGetPrimaryMonitor(), NULL);
	graph = new weighted_graph(num_nodes, max_degree);
	glfwSetWindowUserPointer(window, graph);
	
	glfwSetKeyCallback(window, key_callback);

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
	//thread inputThread(main::StartInputThread);

	
	while (!glfwWindowShouldClose(window))
	{
		glfwWaitEvents();
	}

	//Collect main threads:
	graphProcessingThread.join();
	renderThread.join();
	//inputThread.join();
	
	glfwDestroyWindow(window);

	debug_file << "Exiting Main Thread\n";
	debug_file.close();
	return 0;
}


void main::StartRenderThread()
{
	debug_file << "Starting Render Thread\n";
	
	glfwMakeContextCurrent(window);
	
	glfwSwapInterval(1);
	graph_render_pointer = new graph_renderer();
	while (!glfwWindowShouldClose(window))
	{
		graph_render_pointer->graph_renderer::render(window);
	}
}

void main::StartGraphProcessingThread()
{
	debug_file << "Starting Graph Processing Thread\n";
}

void main::StartInputThread()
{
	debug_file << "Starting Input Thread\n";
	
	input = new input_handler(window);
	while(!glfwWindowShouldClose(window))
	{
		input->handle_event();
	}
	/*
	do
	{
		glfwPollEvents();
		Sleep(100);
	}while(!done);*/
}
