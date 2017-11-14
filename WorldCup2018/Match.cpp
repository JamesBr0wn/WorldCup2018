#include "WorldCup.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define GOALRATE 20
#define MONTH  "July\0"
typedef multimap<int, string> Schedule;
typedef Schedule::const_iterator CIT;
typedef pair<CIT, CIT> Range;
using namespace std;

vector<Shot> WorldCup::match(Team& home, Team& away, int type){ 
	vector<Shot> result;
	int homeGoal = 0, awayGoal = 0;
	int teamSection = home.getAbility() + away.getAbility();
	for (int i = 0; i < 12; i++) {
		result.push_back(Shot());
		//Determine shot times
		srand((unsigned int)time(NULL)+rand());
		unsigned int currentTime = i * 10 + (rand() % 10);
		result[i].time = currentTime;
		//Determine whether the shot has goal in
		srand((unsigned int)time(NULL) + rand());
		bool goal = ((rand() % 100) <= GOALRATE);
		result[i].goal = goal;
		//Determine which team take this shot
		srand((unsigned int)time(NULL) + rand());
		int teamRandom = rand() % teamSection;
		Team* shotTeam = &home;
		Team* shotedTeam = &away;
		if (teamRandom > home.getAbility()) {
			shotTeam = &away;
			shotedTeam = &home;
		}
		result[i].teamName = shotTeam->getCountry();
		//Determine which player take this shot
		int playerSection = 0;
		vector<Player*> teamPlayer = shotTeam->getPlayer();
		for (int j = 0; j < teamPlayer.size(); j++){
			playerSection += teamPlayer[j]->getAbility();
		}
		srand((unsigned int)time(NULL) + rand());
		int playerRandom = rand() % playerSection;
		int currentAbility = 0;
		Player* shotPlayer = teamPlayer[0];
		for (int j = 0; j < teamPlayer.size(); j++) {
			currentAbility += teamPlayer[j]->getAbility();
			if (playerRandom < currentAbility) {
				shotPlayer = teamPlayer[j];
				break;
			}
		}

		result[i].playerName = shotPlayer->getName();
		result[i].playerID = shotPlayer->getID();
		result[i].playerPosition = shotPlayer->getPosition();
		//If the shot has goal in
		if (goal) {
			//Modify the score
			if (shotTeam->getCountry() == home.getCountry()) {
				homeGoal++;
			}
			else {
				awayGoal++;
			}
			//Modify team data
			shotTeam->setGoals_for(shotTeam->getGoals_for() + 1);
			shotedTeam->setGoals_against(shotedTeam->getGoals_against() + 1);
			//MOdify palyer data
			shotPlayer->setGoal(shotPlayer->getGoal() + 1);
		}
		if (i+1 == 9 && (homeGoal != awayGoal || type == 0)) {
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
		srand((unsigned int)time(NULL) + rand());
		int dice = rand() % 6;
		if (dice < 3) {
			shotTeam = away;
			shotedTeam = home;
		}
		result.back().teamName = shotTeam.getCountry();
		//Determine which player take this shot randomly
		srand((unsigned int)time(NULL) + rand());
		int playerNum = rand() % shotTeam.getPlayer().size();
		Player* shotPlayer = shotTeam.getPlayer()[playerNum];
		result.back().playerID = shotPlayer->getID();
		result.back().playerName = shotPlayer->getName();
		result.back().playerPosition = shotPlayer->getPosition();
		//Modify the score
		if (shotTeam.getCountry() == home.getCountry()) {
			homeGoal++;
		}
		else {
			awayGoal++;
		}
		//Modify team data
		shotTeam.setGoals_for(shotTeam.getGoals_for() + 1);
		shotedTeam.setGoals_against(shotedTeam.getGoals_against() + 1);
		//Modify palyer data
		shotPlayer->setGoal(shotPlayer->getGoal() + 1);
	}
	//Modify team points
	if (homeGoal > awayGoal) {
		home.setWon(home.getWon() + 1);
		away.setLost(away.getLost() + 1);
	}
	else if (homeGoal < awayGoal) {
		home.setLost(home.getLost() + 1);
		away.setWon(away.getWon() + 1);
	}
	else {
		home.setDraw(home.getDraw() + 1);
		away.setDraw(away.getDraw() + 1);
	}
	return result;
}

void WorldCup::groupMatch() {
	Range range;
	for (int i = 1; i <= 12; i++) {
		//Matches in the ith day
		range = day_info.equal_range(i);
		//Print day information
		cout << "Hello everyone, it is " << MONTH  << " "<< i << ", ";
		if (i == 12) {
			cout << "the last day of group match, tomorrow 32 promotion team will face curel knockout." << endl;
		}
		else {
			cout << "the " << i << "th day of group match." << endl;
		}
		cout << "Today we will have ";
		if (i & 1) {
cout << "matches of Group A, C, E and G, totally 4 matches." << endl;
		}
		else {
			cout << "matches of Group B, D, F and H, totally 4 matches." << endl;
		}
		CIT it = range.first;
		int j = 1;
		for (; it != range.second; it++) {
			//The jth match in one day
			string vsTeam = it->second;
			string homeName = vsTeam.substr(0, vsTeam.find(" vs"));
			string awayName = vsTeam.substr(vsTeam.find("vs") + 3, vsTeam.find(',') - vsTeam.find("vs") - 3);
			//Print match information
			cout << "Next we will have today's " << j << "th match:" << endl;
			startMatch(homeName, awayName, 0);
			j++;
		}
		groupSort(i);
	}
}

void WorldCup::knockout() {

}

void WorldCup::startMatch(string homeName, string awayName, int type) {
	cout << homeName << "vs" << awayName << endl;
	Team& home = findTeam(homeName), away = findTeam(awayName);
	printTeamInfo(home);
	printTeamInfo(away);
	vector<Shot> result = match(home, away, type);
	liveBroadcast(homeName, awayName, result);
}

void WorldCup::liveBroadcast(string homeName, string awayName, vector<Shot> result) {
	int homeGoal = 0, awayGoal = 0;
	cout << "Playing..." << endl;
	for (int i = 0; i < result.size(); i++) {
		if (result[i].goal) {
			if (result[i].teamName == homeName) {
				homeGoal++;
			}
			else {
				awayGoal++;
			}
			cout << result[i].teamName << " did a goal, and it was " << result[i].playerID << ", " << result[i].playerName << " did the goal" << endl;
			cout << "Now it is " << homeGoal << ":" << awayGoal << endl;
		}
	}
	if (homeGoal > awayGoal) {
		cout << homeName << " beats " << awayName << " with the goals " << homeGoal << ":" << awayGoal << endl;
	}
	else if (homeGoal < awayGoal) {
		cout << homeName << " fails " << awayName << " with the goals " << homeGoal << ":" << awayGoal << endl;
	}
	else {
		cout << "It is a draw with " << homeGoal << ":" << awayGoal << endl;
	}
}

void WorldCup::groupSort(int i) {
	bool compareTeam(Team* a, Team* b);
	/*if (i & 1) {
		sortGroup(GA);
		sortGroup(GC);
		sortGroup(GE);
		sortGroup(GG);
	}
	else {
		sortGroup(GB);
		sortGroup(GD);
		sortGroup(GF);
		sortGroup(GH);
	}*/
}

void WorldCup::printTeamInfo(Team& team) {
	cout << team.getCountry() << endl;
	for (int i = 0; i < team.getPlayer().size(); i++) {
		Player* temp = team.getPlayer()[i];
		cout << temp->getID() << endl;
		cout << team.getPlayer()[i]->getID() << ", " << team.getPlayer()[i]->getName() << ", " << team.getPlayer()[i]->getPosition() << endl;
	}
}

string WorldCup::voicePool(Shot shot) {
	return string();
}


Team& WorldCup::findTeam(string teamName) {
	for (int i = 0; i < totalTeams.size(); i++) {
		if (teamName == totalTeams[i].getCountry()) {
			return totalTeams[i];
		}
	}
	throw runtime_error("No team match");
}

void WorldCup::sortGroup(Group group) {
	bool compareTeam(Team* a, Team* b);
	Team* temp;
	for (int i = 0; i < group.group.size()-1; i++){
		for (int j = 0; j < group.group.size() - 1; j++) {
			if (!compareTeam(group.group[j], group.group[j + 1])) {
				temp = group.group[j];
				group.group[j] = group.group[j + 1];
				group.group[j + 1] = temp;
				
			}
		}
	}
}

bool compareTeam(Team* a, Team* b) {
	return a->getPoints() > b->getPoints() || (a->getPoints() == b->getPoints() && a->getGoals_difference() > b->getGoals_difference()) || (a->getPoints() == b->getPoints() && a->getGoals_difference() == b->getGoals_difference() && a->getCountry() < b->getCountry());
}

