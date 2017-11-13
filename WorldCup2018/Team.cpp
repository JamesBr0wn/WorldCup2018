#include "Team.hpp"

void Team::setCountry(string countryName)
{
	country = countryName;
}

void Team::setPlayer(const Player &tempPlayer)
{
	myPlayer.push_back(tempPlayer);
}

void Team::setRank(int _rank)
{
	rank = _rank;
}

void Team::setAbility(int _ability)
{
	ability = _ability;
}

void Team::setContinent(string _coutinent)
{
	continent = _coutinent;
}

void Team::setWon(int _won)
{
	won = _won;
}

void Team::setDraw(int _draw)
{
	draw = _draw;
}

void Team::setLost(int _lost)
{
	lost = _lost;
}

void Team::setGoals_for(int _goals_for)
{
	goals_for = _goals_for;
}

void Team::setGoals_against(int _goals_against)
{
	goals_against = _goals_against;
}

void Team::setPoints(int _points)
{
	points = _points;
}

int Team::getWon()
{
	return won;
}

int Team::getDraw()
{
	return draw;
}

int Team::getLost()
{
	return lost;
}

int Team::getGoals_for()
{
	return goals_for;
}

int Team::getGoals_against()
{
	return goals_against;
}

int Team::getgGoals_diffence()
{
	return getGoals_for() - getGoals_against();
}

int Team::getPoints()
{
	return points;
}

int Team::getAbility()
{
	return ability;
}

string Team::getCountry()
{
	return country;
}

int Team::getRank()
{
	return rank;
}

string Team::getContinent()
{
	return continent;
}

vector<Player>& Team::getPlayer()
{
	return myPlayer;
}
