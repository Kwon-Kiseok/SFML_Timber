#pragma once
#include "Object.h"

class Branch : public Object
{
private:
	side dirBranch;
public:
	Branch() : dirBranch(side::NONE) {}
	~Branch() {}

	void set();
	void Update(int i);
	void setDir(side side);
	side getDir();
	void setNewBranch(mt19937* gen);
	void downBranch(Branch nextBranch);
	void setRotate(float degree);
};

