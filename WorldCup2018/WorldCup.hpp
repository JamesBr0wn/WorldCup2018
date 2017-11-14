#ifndef __WROLDCUP_HPP__
#define __WORLDCIP_HPP__
#include"Team.hpp"
#include<vector>
#include<map>
struct Group
{
	vector<Team*> group;
	map<string,int> continent;
	char groupName;
	Group(char _name=' ') :groupName(_name){
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

class WorldCup
{
public:



	void groupMatch();
	void knockout();



	WorldCup();
	void getTeamInfo();
	void getPlaceInfo();
	void showTeamInfo();
	void showGroupInfo();
	void showPotInfo();
	void setPot();
	void grouping32();
	void schedule32();
	void showTeam16();
	void grouping16();
	void showTeam8();
	void grouping8();
	void showTeam4();
	void grouping4();
	void showTeam2();
	void grouping2();
	vector<Shot> match(Team& home, Team& away, int type);
private:
	void helpTeamShow(ofstream& out, int number,int amount, int &i);
	void helpSetPlot(vector<Team*>& tempPot, int amount, int &i);
	void helpGrouping32(vector<Team*>& tempPot,int ok);
	bool helpGrouping32_1(vector<Team*>&tempPot,int index, Group &tempGroup);
	void setTeamAmount(int _CAF, int _CONMEBOL, int _AFC, int _OFC, int _CONCACAF, int _UEFA);
	void helpPotShow(ofstream& out, vector<Team*>& tempPot);
	void helpSchedule16(Group tempGroup,multimap<int,string>& day_info,const vector<string>&tempPlace,int _day, int match);
	vector<string> helpGetMatchPlace();
	void helpShowTeam16(Group tempGroup,int winner);
	void helpGrouping16(Group tempGroup1, Group tempGroup2, vector<string>tempPlace);
	void helpShowTeam8_4_2(int teamAmount);
	void helpGrouping8_4_2(int teamAmount);

	int AFC;
	int CAF;
	int CONCACAF;
	int OFC;
	int CONMEBOL;
	int UEFA;
	int day;     //表示当前日期
	multimap<int, string> day_info; //存放比赛时间表
	vector<Team*> matchTeam;         //存放比赛的队伍
	vector<Team> totalTeams;        //存放所有队伍
	vector<Player> totalPlayers;    //存放所有球员
	vector<string> place;
	vector<Team*> pot1;
	vector<Team*> pot2;
	vector<Team*> pot3;
	vector<Team*> pot4;
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