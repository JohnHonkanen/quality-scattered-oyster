#pragma once
#include "Behaviours.h"
class GameBehaviour :
	public Behaviours
{
public:
	GameBehaviour();
	virtual ~GameBehaviour();
	virtual void Start();
	virtual void Update();
	virtual void onBecomeVisible();
	virtual void onBecomeInvisible();
};

