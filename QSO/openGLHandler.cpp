#include "openGLHandler.h"



openGLHandler::openGLHandler(Window *window)
{
	openGLHandler::window = window;
	GraphicsHandler::renderer = nullptr;
}


openGLHandler::~openGLHandler()
{
}

void openGLHandler::init() {

	window->init();
	
	// Set this to true so GLEW knows to use a modern approach to retreiving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Initialize DevIL
	ilInit();

	glm::mat4 view;
	glm::mat4 projection;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f)); // Change Z value to move camera closer/further away from the screen
	
	//Set projection to perspective view
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)window->screenWIDTH / (GLfloat)window->screenHEIGHT, 0.1f, 100.0f);

	openGLHandler::view.setTransform(view);
	openGLHandler::projection.setTransform(projection);

	// Setup OpenGL options
	glEnable(GL_BLEND); // Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void openGLHandler::start() {

	// Rendering commands go here
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Color to clear with (Background color of active scene)
	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

}

void openGLHandler::end() {
	
	// Swap the buffers (Update Scene)
	window->swapBuffers();
}

void openGLHandler::destroy() {
	window->destroy();
}
