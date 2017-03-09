#pragma once
#include "Behaviours.h"
#include <map>

class GameBehaviour :
	public Behaviours
{
public:
	GameBehaviour(std::string name);
	virtual ~GameBehaviour();
	virtual void Start();
	virtual void Update();
	virtual void onBecomeVisible();
	virtual void onBecomeInvisible();

	static enum BehaviorFuncs {
		BH_START,
		BH_UPDATE,
		BH_VISIBLE,
		BH_INVISIBLE
	};
};

