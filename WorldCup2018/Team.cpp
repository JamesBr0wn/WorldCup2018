#include "Team.hpp"

Team::Team(string _country, string _continent, vector<Player*> _myPlayer, int _rank, int _ability, int _won, int _draw, int _lost, int _goals_for, int _goals_against)
{
	setCountry(_country);
	myPlayer = _myPlayer;
	setRank(_rank);
	setAbility(_ability);
	setContinent(_continent);
	setWon(_won);
	setDraw(_draw);
	setLost(_lost);
	setGoals_for(_goals_for);
	setGoals_against(_goals_against);
}

void Team::setCountry(string countryName)
{
	country = countryName;
}

void Team::setPlayer(Player* tempPlayer)
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

int Team::getGoals_difference()
{
	return getGoals_for() - getGoals_against();
}

int Team::getPoints()
{
	return 3*getWon()+getDraw();
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

vector<Player*> Team::getPlayer()
{
	return myPlayer;
}
