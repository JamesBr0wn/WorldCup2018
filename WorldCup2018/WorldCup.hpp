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
	void getTeamInfo();			//��ö�����Ϣ
	void getPlaceInfo();		//��ñ���������Ϣ
	void showTeamInfo();		//��ʾ��������
	void setPot();				//�Ѷ���Ž�pot��
	void showPotInfo();			//��ʾpot��Ϣ
	void grouping32();			//С��������
	void showGroupInfo();		//��ʾ������Ϣ
	void schedule32();			//С������������
	void showTeam16();			//��ʾ16ǿ����
	void grouping16();			//16ǿ��������
	void showTeam8();		
	void grouping8();
	void showTeam4();
	void grouping4();		
	void showTeam2();
	void grouping2();
	void showTeam1();
	void showFinalStastics();	//��ʾ���ְ�����ְ�

	void groupMatch();			//С����
	void match16();				//ʮ��ǿ��
	void match8();				//�ķ�֮һ����
	void semiFinals();			//�����
	void final();				//����
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

	vector<Shot> match(Team& home, Team& away, int type);												//��������
	void knockout(int n);																				//��̭��
	pair<int, int> startMatch(string homeName, string awayName, int type);								//��Ӧ���Ƶ���ӽ��б���
	pair<int, int> liveBroadcast(string homeName, string awayName, vector<Shot> result);				//�������̺ͽ������
	string voicePool(Shot shot, string homeName, string awayName, int homeGoal, int awayGoal);//��˵������
	string helpVoice(Shot shot, string firTeamName, string secTeamName, int homeGoal, int awayGoal);
	Team& findTeam(string teamName);																	//�ɶ����ҵ����
	void groupSort();																					//С������������
	void sortGroup(Group& group);																		//��ĳ��С�鰴��������
	void printTeamInfo(Team& team);																		//��ӡ������Ϣ							

	int AFC;
	int CAF;
	int CONCACAF;
	int OFC;
	int CONMEBOL;
	int UEFA;

	string file;
	Date date;						//��ʾ��ǰ����
	Date matchDate;					//��ű�������
	multimap<int, string> day_info; //��ű���ʱ���
	vector<Team*> matchTeam;        //��ŵ�����̭���б����Ķ���
	vector<Team*> failTeam;			//��ŵ�����̭���б���̭�Ķ���
	vector<Team> totalTeams;        //������ж���
	vector<Player> totalPlayers;    //���������Ա
	vector<string> place;			//��ű�������
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