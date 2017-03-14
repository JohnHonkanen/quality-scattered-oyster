#include "Application.h"



Application::Application()
{
}


Application::~Application()
{
}

void Application::Initialize()
{
}

void Application::Start()
{
	for (int i = 0; i < Application::gameObjects.size(); i++) {
		Application::gameObjects[i]->broadcastMessage(GameBehaviour::BH_START);
	}
}

void Application::Loop()
{
	for (int i = 0; i < Application::gameObjects.size(); i++) {
		Application::gameObjects[i]->broadcastMessage(GameBehaviour::BH_UPDATE);
	}
}

void Application::Destroy()
{
	for (int i = 0; i < Application::gameObjects.size(); i++) {
		Object::Destroy(Application::gameObjects[i]);
	}
}
