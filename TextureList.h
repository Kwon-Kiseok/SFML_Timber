#pragma once
#include "Background.h"
#include "Cloud.h"
#include "Bee.h"
#include "Tree.h"
#include "Branch.h"
#include "RIP_Tombstone.h"
#include "Tree_Log.h"

class TextureList
{
public:
	Background* bg;
	Cloud* cloud;
	Bee* bee;
	Tree* tree;
	Tree_Log* treeLog;
	Branch* branch;
	RIP_Tombstone* tombstone;

	~TextureList();

	void init();
	void update();
	void draw(RenderWindow* window);
};

