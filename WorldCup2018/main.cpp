#include<iostream>
#include"WorldCup.hpp"

using namespace std;

int main()
{
	WorldCup mycup;
	mycup.getTeamInfo();
	mycup.getPlaceInfo();
	mycup.showTeamInfo();
	mycup.setPot();
	mycup.showPotInfo();
	mycup.grouping32();
	mycup.showGroupInfo();
	mycup.schedule32();
	mycup.groupMatch();
	mycup.showTeam16();
	getchar();
}