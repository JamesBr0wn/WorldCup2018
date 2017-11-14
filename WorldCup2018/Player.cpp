#include "Player.hpp"

Player::Player(string _name, string _country, string _id, string _position, int _ability, int _goal)
{
	setName(_name);
	setCountry(_country);
	setID(_id);
	setPosition(_position);
	setAbility(_ability);
	setGoal(_goal);
}

string Player::getName()
{
	return name;
}

string Player::getPosition()
{
	return position;
}

string Player::getCountry()
{
	return country;
}

string Player::getID()
{
	return id;
}

int Player::getAbility()
{
	return ability;
}

int Player::getGoal()
{
	return goal;
}

void Player::setID(string _id)
{
	id = _id;
}

void Player::setCountry(string _country)
{
	country = _country;
}

void Player::setName(string _name)
{
	name = _name;
}

void Player::setPosition(string _position)
{
	position = _position;
}

void Player::setAbility(int _ability)
{
	ability = _ability;
}

void Player::setGoal(int _goal)
{
	goal = _goal;
}
