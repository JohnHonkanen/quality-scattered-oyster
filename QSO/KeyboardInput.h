#pragma once
class KeyboardInput
{
private:
	bool keys[1024];

public:
	KeyboardInput();
	~KeyboardInput();

	void setKey(int key, bool keyPress);
	bool keyPressed(int key);


};

