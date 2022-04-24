#include "Player.h"
#include "Weapon.h"

Player::~Player()
{
	delete weapon;
}

void Player::setDir(side side)
{
	dir = side;
}

side Player::getDir()
{
	return dir;
}

void Player::SetWeapon()
{
	weapon = new Weapon();
	weapon->init("graphics/axe.png", 700, 830);
}

void Player::move()
{
	if (dir == side::LEFT)
	{
		x = 720;
		y = 720;
		sprite.setScale(-1.0f, 1.0f);
	}
	else
	{
		x = 1200;
		y = 720;
		sprite.setScale(1.0f, 1.0f);
	}
	sprite.setPosition(x, y);
}

int Player::GetScore()
{
	return score;
}

void Player::AddScore(int addScore)
{
	score += addScore;
}

void Player::SetScore(int input)
{
	score = input;
}

void Player::ResetPos(float x, float y)
{
	this->x = x;
	this->y = y;
	sprite.setPosition(this->x, this->y);
	sprite.setScale(-1.0f, 1.0f);
	//weapon->ResetPos(this->x, this->y);
}

void Player::SetWeaponPos(side side)
{
	if (side == side::LEFT)
	{
		weapon->SetXY(weapon->AXE_POSITION_LEFT, weapon->getSprite().getPosition().y);
	}
	else if(side == side::RIGHT)
	{
		weapon->SetXY(weapon->AXE_POSITION_RIGHT, weapon->getSprite().getPosition().y);
	}
}

void Player::draw(RenderWindow* window)
{
	window->draw(sprite);
	window->draw(weapon->getSprite());
}

void Player::WeaponInvisible()
{
	weapon->SetXY(3000, weapon->getSprite().getPosition().y);
}
