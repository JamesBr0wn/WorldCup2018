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
	mycup.grouping16();
	mycup.knockout();
	mycup.showTeam8();
	mycup.grouping8();
	mycup.knockout();
	mycup.showTeam4();
	mycup.grouping4();
	mycup.knockout();
	mycup.showTeam2();
	mycup.grouping2();
	mycup.knockout();
	mycup.showFinalStastics();
	getchar();
}