#include "WorldCup.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<Shot> WroldCup::match(Team& home, Team& away, int type){
	vector<Shot> result;
	int homeGoal = 0, awayGoal = 0;
	int teamSection = home.getAbility() + away.getAbility();
	for (int i = 0; i < 12; i++) {
		result.push_back(Shot());
		//Determine shot time
		srand((unsigned int)time(NULL));
		unsigned int currentTime = i * 10 + (rand() % 10);
		result[i].time = currentTime;
		//Determine whether the shot has goal in
		bool goal = ((rand() % 10) <= 3);
		result[i].goal = goal;
		//Determine which team take this shot
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
		if (i+1 == 9 && homeGoal != awayGoal) {
			break;
		}
	}
	//In a knockout
	//If the two team is still in a draw after a 120-min long combat, use a dice to determine which team wins
	if (type == 1 && homeGoal == awayGoal) {
		result.push_back(Shot());
		//Const data
		result.back().time = 120;
		result.back().goal = true;
		//Determine which team take this goal by dice
		Team& shotTeam = home;
		Team& shotedTeam = away;
		int dice = rand() % 6;
		if (dice < 3) {
			shotTeam = away;
			shotedTeam = home;
		}
		result.back().teamName = shotTeam.getCountry();
		//Determine which player take this shot randomly
		int playerNum = rand() % 11;
		Player& shotPlayer = shotTeam.getPlayer()[playerNum];
		result.back().playerID = shotPlayer.getID();
		result.back().playerName = shotPlayer.getName();
		result.back().playerPosition = shotPlayer.getPosition();
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
		//Modify palyer data
		shotPlayer.setGoal(shotPlayer.getGoal() + 1);
	}
	//Modify team points, goals for and  goals against
	if (homeGoal > awayGoal) {
		home.setWon(home.getWon() + 1);
		away.setLost(away.getLost() + 1);
		home.setPoints(home.getPoints() + 3);
	}
	else if (homeGoal < awayGoal) {
		home.setLost(home.getLost() + 1);
		away.setWon(away.getWon() + 1);
		away.setPoints(away.getPoints() + 3);
	}
	else {
		home.setDraw(home.getDraw() + 1);
		away.setDraw(away.getDraw() + 1);
		home.setPoints(home.getPoints() + 1);
		away.setPoints(away.getPoints() + 1);
	}
}