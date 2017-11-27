#include "WorldCup.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#define GOALRATE 20
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
			//Modify palyer data
			shotPlayer->setGoal(shotPlayer->getGoal() + 1);
		}
		if (i + 1 == 9 && (homeGoal != awayGoal || type == 0)) {
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
	ofstream clear("simulationLog.txt");
	clear << "";
	clear.close();
	ofstream out("simulationLog.txt", ios::app);
	Range range;
	for (int i = 1; i <= 12; i++) {
		//Matches in the ith day
		range = day_info.equal_range(matchDate.day);
		//Print day information
		cout << "Hello everyone, it is " << matchDate.month << " "<< matchDate.day << ", ";
		out << "Hello everyone, it is " << matchDate.month << " " << matchDate.day << ", ";
		if (i == 12) {
			cout << "the last day of group match, tomorrow 32 promotion team will face curel knockout." << endl;
			out << "the last day of group match, tomorrow 32 promotion team will face curel knockout." << endl;
		}
		else {
			cout << "the " << i << "th day of group match." << endl;
			out << "the " << i << "th day of group match." << endl;
		}
		cout << "Today we will have ";
		out << "Today we will have ";
		if (i & 1) {
			cout << "matches of Group A, C, E and G, totally 4 matches." << endl;
			out << "matches of Group A, C, E and G, totally 4 matches." << endl;
		}
		else {
			cout << "matches of Group B, D, F and H, totally 4 matches." << endl;
			out << "matches of Group B, D, F and H, totally 4 matches." << endl;
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
			out << "Next we will have today's " << j << "th match:" << endl;
			startMatch(homeName, awayName, 0);
			j++;
		}
		groupSort();
		matchDate++;
	}
	showGroupMatchResult();
}

void WorldCup::match16() {
	ofstream out("simulationLog.txt", ios::app);
	matchDate.day = 27;
	cout << "1 / 8 Finals:" << endl;
	out << "1 / 8 Finals:" << endl;
	knockout(2);
}

void WorldCup::match8() {
	ofstream out("simulationLog.txt", ios::app);
	matchDate.month = "July";
	matchDate.day = 2;
	cout << "1 / 4 Finals:" << endl;
	out << "1 / 4 Finals:" << endl;
	knockout(1);
}

void WorldCup::semiFinals() {
	ofstream out("simulationLog.txt", ios::app);
	matchDate.day = 7;
	cout << "SemiFinals:" << endl;
	out << "SemiFinals:" << endl;
	knockout(1);
}

void WorldCup::final() {
	ofstream out("simulationLog.txt", ios::app);
	matchDate.day = 10;
	cout << "Final:" << endl;
	out << "Final:" << endl;
	knockout(1);
}

void WorldCup::knockout(int n) {
	ofstream out("simulationLog.txt", ios::app);
	vector<Team*> tempFail;
	vector<Team*> tempWin;
	for (int i = 0; i < matchTeam.size(); i+=2) {
		srand(i);
		int randNum = rand() % 2;
		if (n == 2 && i / 2 % 2 == 0 || n == 1) {
			cout << "Today is " << matchDate.month << "," << matchDate.day << ", ";
			out << "Today is " << matchDate.month << "," << matchDate.day << endl;
			if (randNum == 1) {
				cout << "a warm sunny day, nice for matches" << endl;
				out << "a warm sunny day, nice for matches" << endl;
			}
			else {
				cout << "the weather is a little bit cold" << endl;
				out << "the weather is a little bit cold" << endl;

			}
		}
		cout << "We will have the match between " << matchTeam[i]->getCountry() << " and " << matchTeam[i + 1]->getCountry() << endl;
		out << "We will have the match between " << matchTeam[i]->getCountry() << " and " << matchTeam[i + 1]->getCountry() << endl;
		pair<int, int> score = startMatch(matchTeam[i]->getCountry(), matchTeam[i + 1]->getCountry(), 1);
		tempWin.push_back(matchTeam[i + ((score.first > score.second) ? 0 : 1)]);
		tempFail.push_back(matchTeam[i + ((score.first > score.second) ? 1 : 0)]);
		if (n == 2 && i / 2 % 2 == 1 || n == 1) {
			matchDate++;
		}
	}
	matchTeam = tempWin;
	failTeam = tempFail;
	showKnockoutResult();
}

pair<int, int> WorldCup::startMatch(string homeName, string awayName, int type) {
	ofstream out("simulationLog.txt", ios::app);
	cout << homeName << " vs " << awayName << endl;
	out << homeName << " vs " << awayName << endl;
	Team& home = findTeam(homeName);
	Team& away = findTeam(awayName);
	printTeamInfo(home);
	printTeamInfo(away);
	vector<Shot> result = match(home, away, type);
	return liveBroadcast(homeName, awayName, result);
}

pair<int, int> WorldCup::liveBroadcast(string homeName, string awayName, vector<Shot> result) {
	ofstream out("simulationLog.txt", ios::app);
	int homeGoal = 0, awayGoal = 0;
	cout << "Playing..." << endl;
	out << "Playing..." << endl;
	for (int i = 0; i < result.size(); i++) {
		voicePool(result[i], homeName, awayName, homeGoal, awayGoal);
		if (result[i].goal) {
			if (result[i].teamName == homeName) {
				homeGoal++;
			}
			else {
				awayGoal++;
			}
			cout << result[i].teamName << " did a goal, and it was " << result[i].playerID << ", " << result[i].playerName << " did the goal" << endl;
			cout << "Now it is " << homeGoal << ":" << awayGoal << endl;
			out << result[i].teamName << " did a goal, and it was " << result[i].playerID << ", " << result[i].playerName << " did the goal" << endl;
			out << "Now it is " << homeGoal << ":" << awayGoal << endl;
		}
	}
	if (homeGoal > awayGoal) {
		cout << homeName << " beats " << awayName << " with the goals " << homeGoal << ":" << awayGoal << endl << endl;
		out << homeName << " beats " << awayName << " with the goals " << homeGoal << ":" << awayGoal << endl << endl;
	}
	else if (homeGoal < awayGoal) {
		cout << homeName << " fails " << awayName << " with the goals " << homeGoal << ":" << awayGoal << endl << endl;
		out << homeName << " fails " << awayName << " with the goals " << homeGoal << ":" << awayGoal << endl << endl;
	}
	else {
		cout << "It is a draw with " << homeGoal << ":" << awayGoal << endl << endl;
		out << "It is a draw with " << homeGoal << ":" << awayGoal << endl << endl;
	}
	return pair<int, int>(homeGoal, awayGoal);
}

void WorldCup::groupSort() {
	bool compareTeam(Team* a, Team* b);
	sortGroup(GA);
	sortGroup(GC);
	sortGroup(GE);
	sortGroup(GG);
	sortGroup(GB);
	sortGroup(GD);
	sortGroup(GF);
	sortGroup(GH);
}

void WorldCup::printTeamInfo(Team& team) {
	ofstream out("simulationLog.txt", ios::app);
	cout << "Country:" << team.getCountry() << endl;
	out << "Country:" << team.getCountry() << endl;
	for (int i = 0; i < team.getPlayer().size(); i++) {
		Player* temp = team.getPlayer()[i];
		cout << "\t" << team.getPlayer()[i]->getID() << ", " << team.getPlayer()[i]->getName() << ", " << team.getPlayer()[i]->getPosition() << endl;
		out << "\t" << team.getPlayer()[i]->getID() << ", " << team.getPlayer()[i]->getName() << ", " << team.getPlayer()[i]->getPosition() << endl;
	}
}

string WorldCup::voicePool(Shot shot, string homeName, string awayName, int homeGoal, int awayGoal) 
{
	if (shot.teamName == homeName) {
		return helpVoice(shot, homeName, awayName, homeGoal, awayGoal);
	}
	else return helpVoice(shot, awayName, homeName, awayGoal, homeGoal);
}

string WorldCup::helpVoice(Shot shot, string firTeamName, string secTeamName, int firstGoal, int secondGoal)
{
	if (shot.time <= 30 && firstGoal == 0 && secondGoal == 0) {
		//率先进一球
	}
	else if (shot.time > 30 && firstGoal == 0 && secondGoal == 0) {
		if (shot.time > 70) {
			//关键一球
		}
		else {
			//打破僵局
		}
	}
	if (shot.time < 70) {
		if (firstGoal == secondGoal) {
			//再次甩开
		}
		else if (secondGoal - firstGoal == 1) {
			//再次追上
		}
		else if (firstGoal - secondGoal > 0) {
			//远远甩开
		}
		else if (secondGoal - firstGoal > 1) {
			//追上一球，还有机会追平
		}
	}
	else {
		if (firstGoal == secondGoal) {
			//再次甩开(关键）
		}
		else if (secondGoal - firstGoal == 1) {
			//再次追上(关键）
		}
		else if (firstGoal - secondGoal > 0) {
			//远远甩开(关键）
		}
		else if (secondGoal - firstGoal > 1) {
			//虽然追上一球，但是
		}
	}
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

void WorldCup::sortGroup(Group& group) {
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

void WorldCup::showGroupMatchResult() {
	file = "result16.txt";
	ofstream out(file);
	cout << endl << "Final result for group A" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << endl << "Final result for group A" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(GA.group, out);
	cout << endl << "Final result for group B" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << endl << "Final result for group B" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(GB.group, out);
	cout << endl << "Final result for group C" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << endl << "Final result for group C" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(GC.group, out);
	cout << endl << "Final result for group D" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << endl << "Final result for group D" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(GD.group, out);
	cout << endl << "Final result for group E" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << endl << "Final result for group E" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(GE.group, out);
	cout << endl << "Final result for group F" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << endl << "Final result for group F" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(GF.group, out);
	cout << endl << "Final result for group G" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << endl << "Final result for group G" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(GG.group, out);
	cout << endl << "Final result for group H" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << endl << "Final result for group H" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(GH.group, out);
}

void WorldCup::showKnockoutResult() {
	ofstream out(file);
	cout << "Final result" << endl;
	out << "Final result" << endl;
	cout << "Promotion Team(s):" << endl;
	out << "Promotion Team(s):" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(matchTeam, out);
	cout << "Elimination Team(s):" << endl;
	out << "Elimination Team(s):" << endl;
	cout << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	out << setw(15) << "Team\t" << "W\tD\tL\tGF\tGA\tGD\tPts" << endl;
	showTeamScore(failTeam, out);
}

void WorldCup::showFinalStastics() {
	file = "finalStastics.txt";
	ofstream out(file);
	Group top10;
	for (int i = 0; i < totalTeams.size(); i++) {
		top10.group.push_back(&totalTeams[i]);
	}
	sortGroup(top10);
	int size = top10.group.size();
	for (int i = 10; i < size; i++) {
		top10.group.erase(top10.group.begin()+10);
	}
	cout << "Top Teams" << endl;
	out << "Top Teams" << endl;
	showTeamScore(top10.group, out);

	vector<Player*> tempPlayers;
	for (int i = 0; i < totalPlayers.size(); i++) {
		if (totalPlayers[i].getGoal() > 0) {
			tempPlayers.push_back(&totalPlayers[i]);
		}
	}
	bool comparePlayer(Player* a, Player* b);
	sort(tempPlayers.begin(), tempPlayers.end(), comparePlayer);
	cout << endl << "Goalscorers" << endl;
	out << endl << "Goalscorers" << endl;
	int currentGoal = 0;
	for (int i = 0; i < tempPlayers.size(); i++) {
		if (currentGoal != tempPlayers[i]->getGoal()) {
			currentGoal = tempPlayers[i]->getGoal();
			cout << currentGoal << " Goal";
			out << currentGoal << " Goal";
			if (tempPlayers[i]->getGoal() != 1) {
				cout << "s";
			}
			cout << endl;
		}
		cout << "\t" << tempPlayers[i]->getName() << " ," << tempPlayers[i]->getID() << " ," << tempPlayers[i]->getCountry() << endl;
		out << "\t" << tempPlayers[i]->getName() << " ," << tempPlayers[i]->getID() << " ," << tempPlayers[i]->getCountry() << endl;
	}
}

void WorldCup::showTeamScore(vector<Team*>& group, ofstream& out) {
	for (int i = 0; i < group.size(); i++) {
		cout << setw(15) << group[i]->getCountry() << "\t"<< group[i]->getWon() << "\t" << group[i]->getDraw() << "\t" << group[i]->getLost() << "\t" << group[i]->getGoals_for() << "\t" << group[i]->getGoals_against() << "\t" << group[i]->getGoals_difference() << "\t" << group[i]->getPoints() << endl;
		out << setw(15) << group[i]->getCountry() << "\t" << group[i]->getWon() << "\t" << group[i]->getDraw() << "\t" << group[i]->getLost() << "\t" << group[i]->getGoals_for() << "\t" << group[i]->getGoals_against() << "\t" << group[i]->getGoals_difference() << "\t" << group[i]->getPoints() << endl;
	}
}

bool compareTeam(Team* a, Team* b) {
	return a->getPoints() > b->getPoints() || (a->getPoints() == b->getPoints() && a->getGoals_difference() > b->getGoals_difference()) || (a->getPoints() == b->getPoints() && a->getGoals_difference() == b->getGoals_difference() && a->getCountry() < b->getCountry());
}

bool comparePlayer(Player* a, Player* b) {
	return a->getGoal() > b->getGoal();
}