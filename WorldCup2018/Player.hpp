#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include<string>
using namespace std;

class Player
{
public:
	Player(string _name = "", string _country = "", string _id = "", string _position = "", int _ability = 0, int _goal = 0);
	string getName();
	string getPosition();
	string getCountry();
	string getID();
	int getAbility();
	int getGoal();
	void setID(string _id);
	void setCountry(string _country);
	void setName(string _name);
	void setPosition(string _position);
	void setAbility(int _ability);
	void setGoal(int _goal);
private:
	string id;
	string country;
	string name;
	string position;
	int ability;
	int goal;
};

#endif