#ifndef __TEAM_HPP__
#define __TEAM_HPP__

#include"Player.hpp"
#include<vector>
class Team
{
public:
	void setCountry(string countryName);
	void setPlayer(const Player &tempPlayer);
	void setRank(int _rank);
	void setAbility(int _ability);
	void setContinent(string _coutinent);
	void setWon(int _won = 0);
	void setDraw(int _draw = 0);
	void setLost(int _lost = 0);
	void setGoals_for(int _goals_for = 0);
	void setGoals_against(int _goals_against = 0);
	void setPoints(int _points = 0);

	int getWon();
	int getDraw();
	int getLost();
	int getGoals_for();
	int getGoals_against();
	int getgGoals_diffence();
	int getPoints();
	int getAbility();
	string getCountry();
	string getContinent();
	int getRank();
	vector<Player>& getPlayer();
private:
	vector<Player> myPlayer;
	string country;
	string continent;
	int ability;		//能力值
	int rank;           //世界排名
	int won;            //获胜场次
	int draw;           //平局场次
	int lost;           //输球场次
	int goals_for;      //进球数目
	int goals_against;  //失球数目
	int points;         //比赛积分 3/1/0
};

#endif