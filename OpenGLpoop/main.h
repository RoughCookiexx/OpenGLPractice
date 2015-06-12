#include <thread>
#include <windows.h>
#include <fstream>
#include "lib\glew.h"
#include "lib\glfw3.h"
#include "lib\wglew.h"
#include <GL/GL.h>
#include "graph_renderer.h"
#include "input_handler.h"
#include "weighted_graph.h"

class main
{
public:
	static void StartRenderThread();
	static void StartGraphProcessingThread();
	static void StartInputThread();
	static void DebugLog(char* debug_line);
	static void RenderFrame(GLFWwindow* window);
	static void DrawGraph();
};