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
	void getTeamInfo();			//获得队伍信息
	void getPlaceInfo();		//获得比赛场地信息
	void showTeamInfo();		//显示参赛队伍
	void setPot();				//把队伍放进pot中
	void showPotInfo();			//显示pot信息
	void grouping32();			//小组赛分组
	void showGroupInfo();		//显示分组信息
	void schedule32();			//小组赛比赛安排
	void showTeam16();			//显示16强队伍
	void grouping16();			//16强比赛安排
	void showTeam8();		
	void grouping8();
	void showTeam4();
	void grouping4();		
	void showTeam2();
	void grouping2();
	void showTeam1();
	void showFinalStastics();	//显示积分榜和射手榜

	void groupMatch();			//小组赛
	void match16();				//十六强赛
	void match8();				//四分之一决赛
	void semiFinals();			//半决赛
	void final();				//决赛
private:
	void helpTeamShow(ofstream& out, int number,int amount, int &i);
	void helpSetPlot(vector<Team*>& tempPot, int amount, int &i);
	void helpGrouping32(vector<Team*>& tempPot,int ok);
	bool helpGrouping32_1(vector<Team*>&tempPot,int index, Group &tempGroup);
	void setTeamAmount(int _CAF, int _CONMEBOL, int _AFC, int _OFC, int _CONCACAF, int _UEFA);
	void helpPotShow(ofstream& out, vector<Team*>& tempPot);
	void helpSchedule16(ofstream &out, Group tempGroup,multimap<int,string>& day_info
						,const vector<string>&tempPlace,int _day, int match);
	void helpShowTeam16(ofstream &out, Group tempGroup);
	void helpGrouping16(ofstream &out, Group tempGroup1, Group tempGroup2, vector<string>&tempPlace);
	void helpShowTeam8_4_2(ofstream &out, int teamAmount);
	void helpGrouping8_4_2(ofstream &out, int teamAmount);
	void showGroupMatchResult();
	void showKnockoutResult();
	void showTeamScore(vector<Team*>& group, ofstream& out);
	vector<string> helpGetMatchPlace();

	vector<Shot> match(Team& home, Team& away, int type);												//单场比赛
	void knockout(int n);																				//淘汰赛
	pair<int, int> startMatch(string homeName, string awayName, int type);								//对应名称的球队进行比赛
	pair<int, int> liveBroadcast(string homeName, string awayName, vector<Shot> result);				//比赛过程和结果播报
	string voicePool(Shot shot, string homeName, string awayName, int homeGoal, int awayGoal);//解说语音池
	string helpVoice(Shot shot, string firTeamName, string secTeamName, int homeGoal, int awayGoal);
	Team& findTeam(string teamName);																	//由队名找到球队
	void groupSort();																					//小组赛队伍排序
	void sortGroup(Group& group);																		//对某个小组按积分排序
	void printTeamInfo(Team& team);																		//打印队伍信息							

	int AFC;
	int CAF;
	int CONCACAF;
	int OFC;
	int CONMEBOL;
	int UEFA;

	string file;
	Date date;						//表示当前日期
	Date matchDate;					//存放比赛日期
	multimap<int, string> day_info; //存放比赛时间表
	vector<Team*> matchTeam;        //存放当轮淘汰赛中比赛的队伍
	vector<Team*> failTeam;			//存放当轮淘汰赛中被淘汰的队伍
	vector<Team> totalTeams;        //存放所有队伍
	vector<Player> totalPlayers;    //存放所有球员
	vector<string> place;			//存放比赛场地
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


/*
cout << "__				    __	  _______	  ______   __          ______" << endl;
cout << "\ \	 	       / /   / ____  \   |  __  |  | |        |  ___ \" << endl;
cout << " \ \	   __     / /   / /	    \ \  | |__|_|  | |        | |   \ \" << endl;
cout << "  \ \	  /	 \	 / /   | |		 | | | | \ \   | |	      | |    | |" << endl;
cout << "   \ \_/ / \ \_/ /     \ \_____/ /  | |  \ \  | |______  | |___/ /" << endl;
cout << "    \___/	 \___/       \_______/	 |_|   \_\ |________| |______/" << endl;

	  
cout << 	  			"  ________	  _       _    _____" << endl;
cout << 	  			" /  ______| | |	 | |  / ___ \" << endl;
cout << 	  			" | |		 | |	 | | | /   \ \" << endl;
cout << 	  			" | |		 | |     | | | |___|_|" << endl;
cout << 				" | |______	 | \_____/ | | |" << endl;
cout << 				" \________|  \_______/  |_|" << endl;

   ________   _________
  |  ____  | |  _____  |
  |_|    | | | |     | |
   ______| | | |     | |		 
  |  ______| | |     | |
  | |        | |     | |
  | |______  | |_____| |
  |________| |_________|  
   
   
   
   
   
   
   
   
   
   
   
   
   
   */
#endif