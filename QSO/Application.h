#pragma once
#include <vector>
#include "GameObject.h"
class Application
{
public:
	Application();
	virtual ~Application();
	void Initialize();
	void Start();
	void Loop();
	void Destroy();
	std::vector<GameObject*> gameObjects;

};

