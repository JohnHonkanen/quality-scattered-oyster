#pragma once
#include <string>
using namespace std;
class Object
{
protected:
	string name;
	static int instance_id;
public:
	Object();
	virtual ~Object();
	//Virtual
	virtual void destroy(); // Cleans up the Object
	virtual string toString();
	//Normal
	int getInstancedID();
	//Statics
	static void Destroy(Object *obj);

};

