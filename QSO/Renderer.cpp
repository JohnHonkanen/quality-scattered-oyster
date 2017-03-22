#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::setCamera(Camera * camera)
{
	Renderer::camera = camera;
}