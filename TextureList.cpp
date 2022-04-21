#include "TextureList.h"
#include <random>
#include "Timer.h"

TextureList::~TextureList()
{
	delete bg;
	delete[] cloud;
	delete bee;
	delete tree;
	delete[] branch;
	delete treeLog;
}

void TextureList::init()
{
	bg = new Background();
	bg = new Background();
	bg->init("graphics/background.png", 0, 0);

	cloud = new Cloud[3];
	for (int i = 0; i < 3; ++i)
	{
		cloud[i].init("graphics/cloud.png", 0.f, (0.f + 150 * i));
	}

	bee = new Bee();
	bee->init("graphics/bee.png", 0, 800);

	tree = new Tree();
	tree->init("graphics/tree.png", 810, 0);

	int countBranch = 6;
	branch = new Branch[countBranch];
	for (int i = 0; i < countBranch; ++i)
	{
		// 임시 위치 설정
		branch[i].init("graphics/branch.png", -2000, -2000);
		branch[i].set();
	}

	tombstone = new RIP_Tombstone();
	tombstone->init("graphics/rip.png", 2000, 2000);

	treeLog = new Tree_Log();
	treeLog->init("graphics/log.png", 810, 720);
}

void TextureList::draw(RenderWindow* window)
{
	window->draw(bg->getSprite());
	for (int i = 0; i < 3; ++i)
	{
		window->draw(cloud[i].getSprite());
	}
	window->draw(tree->getSprite());
	
	window->draw(bee->getSprite());

	for (int i = 0; i < 6; ++i)
	{
		window->draw(branch[i].getSprite());
	}

	window->draw(tombstone->getSprite());
	window->draw(treeLog->getSprite());
}

void TextureList::update()
{
	random_device rd;
	mt19937 gen(rd());
	Time dt = Timer::GetInstance()->getTime();

	bee->Update(gen, dt);

	for (int i = 0; i < 3; ++i)
	{
		cloud[i].Update(gen, dt);
	}

	for (int i = 0; i < 6; ++i)
	{
		branch[i].Update(i);
	}

	if (treeLog->getActive())
	{
		treeLog->Fly(dt);
	}
}
