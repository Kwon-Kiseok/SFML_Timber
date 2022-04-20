#include "Branch.h"

void Branch::set()
{
	sprite.setOrigin(220, 40);
    dirBranch = side::RIGHT;
}

void Branch::Update(int i)
{
	float height = 150.f * i;

	switch (getDir())
	{
	case side::LEFT:
	{
		SetXY(610, height);
		setRotate(180);
		getSprite().setRotation(180);
	}
	break;
	case side::RIGHT:
	{
		SetXY(1330, height);
		setRotate(0);
		getSprite().setRotation(0);
	}
	break;
	default:
		SetXY(-2000, -2000);
		break;
	}
}

void Branch::setDir(side side)
{
    dirBranch = side;
}

side Branch::getDir()
{
    return dirBranch;
}

void Branch::setNewBranch(mt19937* gen)
{
    int rnd = (*gen)() % 5;
    switch (rnd)
    {
    case 0:
        dirBranch = side::LEFT;
        break;
    case 1:
        dirBranch = side::RIGHT;
        break;
    default:
        dirBranch = side::NONE;
        break;
    }
}

void Branch::downBranch(Branch nextBranch)
{
    this->dirBranch = nextBranch.dirBranch;
}

void Branch::setRotate(float degree)
{
    sprite.setRotation(degree);
}

