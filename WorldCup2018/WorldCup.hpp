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

struct Date
{
	int day;
	string month;
	int operator++(int) {
		int old = day;
		day++;
		if (day == 31) {
			day = 1;
			month="July";
		}
		return old;
	}
	int operator+=(int _day) {
		day+=_day;
		if (day == 31) {
			day -= 30;
			month = "July";
		}
		return day;
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
	void groupMatch();
	void knockout();
	void showFinalStastics();
private:
	void helpTeamShow(ofstream& out, int number,int amount, int &i);
	void helpSetPlot(vector<Team*>& tempPot, int amount, int &i);
	void helpGrouping32(vector<Team*>& tempPot,int ok);
	bool helpGrouping32_1(vector<Team*>&tempPot,int index, Group &tempGroup);
	void setTeamAmount(int _CAF, int _CONMEBOL, int _AFC, int _OFC, int _CONCACAF, int _UEFA);
	void helpPotShow(ofstream& out, vector<Team*>& tempPot);
	void helpSchedule16(ofstream &out, Group tempGroup,multimap<int,string>& day_info,const vector<string>&tempPlace,int _day, int match);
	void helpShowTeam16(ofstream &out, Group tempGroup);
	void helpGrouping16(ofstream &out, Group tempGroup1, Group tempGroup2, vector<string>&tempPlace);
	void helpShowTeam8_4_2(ofstream &out, int teamAmount);
	void helpGrouping8_4_2(ofstream &out, int teamAmount);
	void showGroupMatchResult();
	void showKnockoutResult();
	void showTeamScore(vector<Team*>& group, ofstream& out);
	vector<string> helpGetMatchPlace();

	vector<Shot> match(Team& home, Team& away, int type);
	pair<int, int> startMatch(string homeName, string awayName, int type);
	pair<int, int> liveBroadcast(string homeName, string awayName, vector<Shot> result);
	string voicePool(Shot shot);
	Team& findTeam(string teamName);
	void groupSort();
	void printTeamInfo(Team& team);
	void sortGroup(Group& group);

	int AFC;
	int CAF;
	int CONCACAF;
	int OFC;
	int CONMEBOL;
	int UEFA;

	string file;
	Date date;						//表示当前日期
	Date matchDate;
	multimap<int, string> day_info; //存放比赛时间表
	vector<Team*> matchTeam;        //存放当轮淘汰赛中比赛的队伍
	vector<Team*> failTeam;			//存放当轮淘汰赛中被淘汰的队伍
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