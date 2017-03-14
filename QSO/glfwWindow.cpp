#include "glfwWindow.h"



glfwWindow::glfwWindow(GLuint screenWIDTH, GLuint screenHEIGHT)
{
	glfwWindow::screenWIDTH = screenWIDTH;
	glfwWindow::screenHEIGHT = screenHEIGHT;
}


glfwWindow::~glfwWindow()
{
}

void glfwWindow::init() {

	//Initiate glfw
	glfwInit();

	// Set OpenGL version to (Major, Minor) : 3.3 is newest OpenGL, Vulkan > 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Explicitly tell OpenGL not to use Legacy Functionality.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Resize Window Option
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(800, 600, "Quality Scattered Oysters (QSO)", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (window == nullptr){
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
	}

	// Define the viewport dimensions
	glViewport(0, 0, screenWIDTH, screenHEIGHT);

}

void glfwWindow::swapBuffers() {
	//Update Current Context (Active Scene)
	glfwSwapBuffers(window);
}

void glfwWindow::destroy() {
	//Terminate & Clean up glfw resources before application exit
	glfwTerminate();
}