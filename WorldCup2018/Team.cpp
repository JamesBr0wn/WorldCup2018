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

void Team::setAbility(double _ability)
{
	ability = _ability;
}

void Team::setContinent(string _coutinent)
{
	continent = _coutinent;
}

string Team::getCountry()
{
	return country;
}

int Team::getRank()
{
	return rank;
}

vector<Player> Team::getPlayer()
{
	return myPlayer;
}
