#include "WorldCup.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<Shot> WroldCup::match(Team& home, Team& away, int type){
	vector<Shot> result;
	int homeGoal = 0, awayGoal = 0;
	for (int i = 0; i < 9; i++) {
		result.push_back(Shot());
		//Determine shot time
		srand((unsigned int)time(NULL));
		unsigned int currentTime = i * 10 + (rand() % 10);
		result[i].time = currentTime;
		//Determine whether the shot has goal in
		bool goal = ((rand() % 10) <= 3);
		result[i].goal = goal;
		//Determine which team take this shot
		int teamSection = home.getAbility() + away.getAbility();
		int teamRandom = rand() % teamSection;
		Team& shotTeam = home;
		Team& shotedTeam = away;
		if (teamRandom >= home.getAbility()) {
			shotTeam = away;
			shotedTeam = home;
		}
		result[i].teamName = shotTeam.getCountry();
		//Determine which player take this shot
		int playerSection = 0;
		vector<Player>& teamPlayer = shotTeam.getPlayer();
		for (int j = 0; j < teamPlayer.size(); j++){
			playerSection += teamPlayer[j].getAbility();
		}
		int playerRandom = rand() % playerSection;
		int currentAbility;
		Player& shotPlayer = teamPlayer[0];
		for (int j = 0; j < teamPlayer.size(); j++) {
			currentAbility += teamPlayer[j].getAbility();
			if (playerRandom < currentAbility) {
				shotPlayer = teamPlayer[j];
				break;
			}
		}
		result[i].playerName = shotPlayer.getName();
		result[i].playerID = shotPlayer.getID();
		//If the shot has goal in
		if (goal) {
			//Modify the score
			if (shotTeam.getCountry() == home.getCountry()) {
				homeGoal++;
			}
			else {
				awayGoal++;
			}
			//Modify team data
			shotTeam.setGoals_for(shotTeam.getGoals_for() + 1);
			shotedTeam.setGoals_against(shotTeam.getGoals_against() + 1);
			//MOdify palyer data
			shotPlayer.setGoal(shotPlayer.getGoal() + 1);
		}
	}
	//If it ends in a draw after the 90min combat and it's in a Knockout
	if (homeGoal == awayGoal) {
		
	}
}