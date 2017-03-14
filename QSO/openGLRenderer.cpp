#include "openGLRenderer.h"



openGLRenderer::openGLRenderer(Window *window)
{
	openGLRenderer::window = window;
	GraphicsHandler::renderer = nullptr;
}


openGLRenderer::~openGLRenderer()
{
}
