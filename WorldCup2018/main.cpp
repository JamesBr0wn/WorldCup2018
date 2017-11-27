#include<iostream>
#include"WorldCup.hpp"
#include"Player.hpp"
#include"Team.hpp"
using namespace std;

int main()
{
	cout << " __                 __    _______     ______    __         ______           " << endl;
	cout << " \\ \\               / /   / _____ \\   |  __  |  | |        |  ___ \\      " << endl;
	cout << "  \\ \\     ___     / /   / /     \\ \\  | |__|_|  | |        | |   \\ \\   " << endl;
	cout << "   \\ \\   /   \\   / /   | |       | | | | \\ \\   | |        | |    | |   " << endl;
	cout << "    \\ \\_/ / \\ \\_/ /     \\ \\_____/ /  | |  \\ \\  | |______  | |___/ / " << endl;
	cout << "     \\___/   \\___/       \\_______/   |_|   \\_\\ |________| |______/     " << endl;

	cout << "                  ________   _       _   _______   " << endl;
	cout << "                 /  ______| | |     | | |  ___  \\ " << endl;
	cout << "                 | |        | |     | | | |___| |  " << endl;
	cout << "                 | |        | |     | | | |_____/  " << endl;
	cout << "                 | |_______ | \\_____/ | | |       " << endl;
	cout << "                 \\________|  \\_______/  |_|      " << endl;
	
	cout << "           ________   _________     ____        ______    " << endl;
	cout << "          |  ____  | |  _____  |   / _  |      / ____ \\  " << endl;
	cout << "          |_|    | | | |     | |  / / | |     | /    \\ | " << endl;
	cout << "           ______| | | |     | | |_/  | |     | \\____/ | " << endl;
	cout << "          |  ______| | |     | |      | |     |  ____  |  " << endl;
	cout << "          | |        | |     | |      | |     | /    \\ | " << endl;
	cout << "          | |______  | |_____| |   ___| |___  | \\____/ | " << endl;
	cout << "          |________| |_________|  |_________|  \\______/  " << endl;

	WorldCup mycup;
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