#include "Renderer.h"



Renderer::Renderer()
{
	Renderer::alpha = 1.0f;
}


Renderer::~Renderer()
{
}

void Renderer::addView(Transform view) {
	Renderer::view = view;
}

void Renderer::addProjection(Transform projection) {
	Renderer::projection = projection;
}

void Renderer::setAlpha(float alpha) {
	this->alpha = alpha;
}

float Renderer::getAlpha() {
	return Renderer::alpha;
}