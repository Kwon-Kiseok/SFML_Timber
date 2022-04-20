#pragma once
#include "SFML_headers.h"

class Object
{
protected:
	float x;
	float y;
	Texture texture;
	Sprite sprite;
public:
	Object(float x = 0, float y = 0) : x(x), y(y) {}
	virtual ~Object() {}

	virtual void init(const char* route, float x, float y);
	virtual void SetXY(float x, float y);
	virtual Texture getTexture();
	virtual Sprite getSprite();

};

