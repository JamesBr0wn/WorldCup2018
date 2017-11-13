#ifndef __WROLDCUP_HPP__
#define __WORLDCIP_HPP__
#include"Team.hpp"
#include<vector>
#include<map>
struct Group
{
	vector<Team> group;
	map<string,int> continent;
	char groupName;
	Group(char _name=' ') :groupName(_name) {
		continent["AFC"] = 0;
		continent["CAF"] = 0;
		continent["CONCACAF"] = 0;
		continent["OFC"] = 0;
		continent["CONMEBOL"] = 0;
		continent["UEFA"] = 0;
	}
};

struct Shot {
	unsigned int time;
	bool goal;
	string teamName;
	string playerID;
	string playerName;
	string playerPosition;
};

class WroldCup
{
public:
	WroldCup();
	void getTeamInfo();
	void showTeamInfo();
	void showGroupInfo();
	void showPotInfo();
	void setPot();
	void grouping();
	std::vector<Shot> match(Team& home, Team& away, int type);
private:
	void helpTeamShow(ofstream& out, int number,int amount, int &i);
	void helpSetPlot(vector<Team>& tempPot, int amount, int &i);
	void helpGrouping(vector<Team>& tempPot,bool ok);
	void setTeamAmount(int _CAF, int _CONMEBOL, int _AFC, int _OFC, int _CONCACAF, int _UEFA);
	void helpPotShow(ofstream& out, vector<Team>& tempPot);
	int AFC;
	int CAF;
	int CONCACAF;
	int OFC;
	int CONMEBOL;
	int UEFA;
	vector<Team> totalTeams;
	vector<Player> totalPlayers;
	vector<Team> pot1;
	vector<Team> pot2;
	vector<Team> pot3;
	vector<Team> pot4;
	Group GA;
	Group GB;
	Group GC;
	Group GD;
	Group GE;
	Group GF;
	Group GG;
	Group GH;
};

#endif