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
	void setWon(int _won);
	void setDraw(int _draw);
	void setLost(int _lost);
	void setGoals_for(int _goals_for);
	void setGoals_against(int _goals_against);
	void setGoals_diffence(int _goals_diffence);
	void setPoints(int _points);

	int getWon();
	int getDraw();
	int getLost();
	int getGoals_for();
	int getGoals_against();
	int getgGoals_diffence();
	int getPoints();
	int getAbility();
	string getCountry();
	int getRank();
	int getContinent();
	vector<Player> getPlayer();
private:
	vector<Player> myPlayer;
	string country;
	string continent;
	int ability;		//����ֵ
	int rank;           //��������
	int won;            //��ʤ����
	int draw;           //ƽ�ֳ���
	int lost;           //���򳡴�
	int goals_for;      //������Ŀ
	int goals_against;  //ʧ����Ŀ
	int goals_diffence; //��ʤ����
	int points;         //�������� 3/1/0
};

#endif