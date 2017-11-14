#include <iostream>
#include "WorldCup.hpp"
#include "Team.hpp"
using namespace std;
int main() {
	WorldCup cup;
	vector<Player> tempPlayer1, tempPlayer2;
	vector<Player*> player1, player2;
	string temp1 = "", temp2 = "";
	for (int i = 0; i < 11; i++) {
		temp1 = temp1 + string("A");
		temp2 = temp2 + string("B");
		tempPlayer1.push_back(Player(temp1, "CN", "#", "Fuck", 50 + i, 0));
		tempPlayer2.push_back(Player(temp2, "JP", "#", "Fuck", 46 + i, 0));
	}
	for (int i = 0; i < 11; i++) {
		player1.push_back(&(tempPlayer1[i]));
		player2.push_back(&(tempPlayer2[i]));
	}
	Team A("CN", "Asia",player1 , 1, 45, 3, 2, 1, 8, 1), B("JP", "Asia",player2 , 4, 30, 2, 0, 1, 5, 3);
	cout << A.getPoints() << " " << A.getGoals_for() << " " << A.getGoals_against() << " " << endl << B.getPoints() << " " << B.getGoals_for() << " " << B.getGoals_against() << endl;
	vector<Shot> temp = cup.match(A, B, 0);
	for (int i = 0; i < temp.size(); i++) {
		cout << temp[i].time << " " << temp[i].goal << " " << temp[i].teamName << " " << temp[i].playerName << endl;
	}
	cout << A.getPoints() << " " << A.getGoals_for() << " " << A.getGoals_against() << " " << endl << B.getPoints() << " " << B.getGoals_for() << " " << B.getGoals_against() << endl;
	system("pause");
	return 0;
}