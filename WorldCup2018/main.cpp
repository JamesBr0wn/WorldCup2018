#include<iostream>
#include"WorldCup.hpp"
#include"Player.hpp"
#include"Team.hpp"
using namespace std;

int main()
{

	WorldCup mycup;
	mycup.printWelcomeInfo();
	getchar();
	mycup.getTeamInfo();
	mycup.getPlaceInfo();
	mycup.showTeamInfo();
	getchar();
	mycup.setPot();
	mycup.showPotInfo();
	mycup.grouping32();
	mycup.showGroupInfo();
	getchar();
	mycup.schedule32();
	getchar();
	mycup.groupMatch();
	getchar();
	mycup.showTeam16();
	getchar();
	mycup.grouping16();
	getchar();
	mycup.match16();
	getchar();
	mycup.showTeam8();
	getchar();
	mycup.grouping8();
	getchar();
	mycup.match8();
	getchar();
	mycup.showTeam4();
	getchar();
	mycup.grouping4();
	getchar();
	mycup.semiFinals();
	getchar();
	mycup.showTeam2();
	getchar();
	mycup.grouping2();
	getchar();
	mycup.final();
	getchar();
	mycup.showTeam1();
	getchar();
	mycup.showFinalStastics();
	getchar();
}