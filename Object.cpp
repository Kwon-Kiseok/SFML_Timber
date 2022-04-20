#include "Object.h"

void Object::init(const char* route, float x, float y)
{
	texture.loadFromFile(route);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Object::SetXY(float x, float y)
{
	this->x = x;
	this->y = y;
	sprite.setPosition(this->x, this->y);
}

Texture Object::getTexture()
{
	return texture;
}

Sprite Object::getSprite()
{
	return sprite;
}