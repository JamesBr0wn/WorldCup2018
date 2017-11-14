#include "WorldCup.hpp"
#include<fstream>
#include<string>
#include<iostream>
#include <cstdlib> 
#include <ctime>  
using namespace std;

#define hostRank 0
#define teamMember 11
#define placeNum 8
typedef multimap<int, string>::iterator IT;
typedef pair<IT, IT> Range;
WorldCup::WorldCup():day(1)
{
	GA = Group('A');GB = Group('B');GC = Group('C');GD = Group('D');
	GE = Group('E');GF = Group('F');GG = Group('G');GH = Group('H');
}

void WorldCup::getTeamInfo()
{
	ifstream in("data.txt");
	if (!in) {
		cout << "No such file." << endl;
		exit(0);
	}
	string _country,temp;
	int _rank;
	string _id, _name, _position,_continent;
	double _teamAbility, _playerAbility;
	int _AFC, _CAF, _CONCACAF, _OFC, _CONMEBOL, _UEFA;
	in >> _CAF >> _CONMEBOL >> _AFC>>_OFC >> _CONCACAF >> _UEFA;
	getline(in, temp);
	setTeamAmount(_CAF, _CONMEBOL, _AFC,_OFC, _CONCACAF, _UEFA);
	while (!in.eof()) {
		Team tempTeam;
		Player tempPlayer;
		getline(in, _country);
		getline(in, _continent);
		in >> _rank;
		in >> _teamAbility;
		getline(in, temp);
		for (int i = 0; i < teamMember; i++) {
			getline(in, _id);
			getline(in, _name);
			getline(in, _position);
			in >> _playerAbility;
			getline(in, temp);

			tempPlayer.setCountry(_country);
			tempPlayer.setID(_id);
			tempPlayer.setName(_name);
			tempPlayer.setPosition(_position);
			tempPlayer.setAbility(_playerAbility);
			totalPlayers.push_back(tempPlayer);
		}
		for (int i = 0; i < teamMember; i++) 
			tempTeam.setPlayer(&totalPlayers[i]);
		tempTeam.setContinent(_continent);
		tempTeam.setRank(_rank);
		tempTeam.setAbility(_teamAbility);
		tempTeam.setCountry(_country);
		totalTeams.push_back(tempTeam);
	}
	in.close();
}

void WorldCup::getPlaceInfo()
{
	ifstream in("dataPlace.txt");
	if (!in) {
		cout << "No such file." << endl;
		getchar();
		exit(0);
	}
	string _place;
	for (int i = 0; i < placeNum; i++) {
		in >> _place;
		place.push_back(_place);
	}
	in.close();
}

void WorldCup::showTeamInfo()
{
	ofstream out("team32.txt");
	int i = 0;
	out << "CAF";
	cout << "CAF";
	helpTeamShow(out, CAF, CAF, i);
	out << "CONMEBOL";
	cout << "CONMEBOL";
	helpTeamShow(out, CAF+CONMEBOL, CONMEBOL, i);
	out << "AFC";
	cout << "AFC";
	helpTeamShow(out, CAF + CONMEBOL+AFC, AFC, i);
	out << "OFC";
	cout << "OFC";
	helpTeamShow(out, CAF + CONMEBOL + AFC+OFC, OFC, i);
	out << "CONCACAF";
	cout << "CONCACAF";;
	helpTeamShow(out, CAF + CONMEBOL + AFC + OFC +CONCACAF, CONCACAF, i);
	out << "UEFA";
	cout << "UEFA";
	helpTeamShow(out, CAF + CONMEBOL + AFC + OFC + CONCACAF +UEFA, UEFA, i);
	out.close();
}

void WorldCup::showGroupInfo()
{
	ofstream out;
	out.open("finalDraw.txt", ios_base::app);
	out << "The Final Draw:" << endl;
	cout << "The Final Draw:" << endl;
	out << "group A" << endl;
	cout << "group A" << endl;
	helpPotShow(out, GA.group);
	out << "group B" << endl;
	cout << "group B" << endl;
	helpPotShow(out, GB.group);
	out << "group C" << endl;
	cout << "group C" << endl;
	helpPotShow(out, GC.group);
	out << "group D" << endl;
	cout << "group D" << endl;
	helpPotShow(out, GD.group);
	out << "group E" << endl;
	cout << "group E" << endl;
	helpPotShow(out, GE.group);
	out << "group F" << endl;
	cout << "group F" << endl;
	helpPotShow(out, GF.group);
	out << "group G" << endl;
	cout << "group G" << endl;
	helpPotShow(out, GG.group);
	out << "group H" << endl;
	cout << "group H" << endl;
	helpPotShow(out, GH.group);
	out.close();
	
}

void WorldCup::showPotInfo()
{
	ofstream out("finalDraw.txt");
	out << "First stage :" << endl;
	cout << "First stage :" << endl;
	out << "pot1" << endl;
	cout << "pot1" << endl;
	helpPotShow(out, pot1);
	out << "pot2" << endl;
	cout << "pot2" << endl;
	helpPotShow(out, pot2);
	out << "pot3" << endl;
	cout << "pot3" << endl;
	helpPotShow(out, pot3);
	out << "pot4" << endl;
	cout << "pot4" << endl;
	helpPotShow(out, pot4);
	out.close();
}

void WorldCup::setPot()
{
	int i = 0;
	helpSetPlot(pot2, CAF + CONMEBOL, i);
	helpSetPlot(pot3, CAF + CONMEBOL+ AFC+ OFC + CONCACAF, i);
	helpSetPlot(pot4, CAF + CONMEBOL + AFC + OFC + CONCACAF+ UEFA, i);
}

void WorldCup::grouping32()
{
	helpGrouping32(pot1,1);
	helpGrouping32(pot2,0);
	helpGrouping32(pot3, 0);
	helpGrouping32(pot4, 0);
}

void WorldCup::schedule32()
{
	srand((unsigned)time(NULL));
	day_info.clear();
	vector<string>savePlace = helpGetMatchPlace();
	cout << "Matches by squads" << endl;
	int tempDay = day;
	int tempDay1 = day + 1;
	int i = 0;
	helpSchedule16(GA, day_info, savePlace, 0,0);
	day = tempDay1;
	helpSchedule16(GB, day_info, savePlace, 1,0);
	day = tempDay;
	helpSchedule16(GC, day_info, savePlace, 0,1);
	day = tempDay1;
	helpSchedule16(GD, day_info, savePlace, 1,1);
	day = tempDay;
	helpSchedule16(GE, day_info, savePlace, 0,2);
	day = tempDay1;
	helpSchedule16(GF, day_info, savePlace, 1,2);
	day = tempDay;
	helpSchedule16(GG, day_info, savePlace, 0,3);
	day = tempDay1;
	helpSchedule16(GH, day_info, savePlace, 1,3);
	day = tempDay;
	cout << "\nMatches by date" << endl;
	for (int i = 0; i < 12; i++, day++) {
		cout << "June " << day << endl;
		Range range = day_info.equal_range(day);
		for (IT j = range.first; j != range.second; j++)
			cout << '\t' << j->second << endl;
	}
}

void WorldCup::showTeam16()
{
	cout << "Qualified for round of 16:" << endl;
	helpShowTeam16(GA, 2);
	helpShowTeam16(GB, 2);
	helpShowTeam16(GC, 2);
	helpShowTeam16(GD, 2);
	helpShowTeam16(GE, 2);
	helpShowTeam16(GF, 2);
	helpShowTeam16(GG, 2);
	helpShowTeam16(GH, 2);
}

void WorldCup::grouping16()
{
	day_info.clear();
	srand((unsigned)time(NULL));
	day++;
	vector<string>savePlace;
	vector<string>tempPlace = place;
	while (tempPlace.size()) {
		int index = rand() % tempPlace.size();
		savePlace.push_back(tempPlace[index]);
		tempPlace.erase(tempPlace.begin() + index);
	}
	cout << "Schedule for round of 16:" << endl;
	day++;
	cout << "June " << day << endl;
	helpGrouping16(GA, GB, savePlace);
	helpGrouping16(GC, GD, savePlace);
	day++;
	cout << "June " << day << endl;
	helpGrouping16(GE, GF, savePlace);
	helpGrouping16(GG, GH, savePlace);
	day++;
	cout << "June " << day << endl;
	helpGrouping16(GB, GA, savePlace);
	helpGrouping16(GD, GC, savePlace);
	day++;
	cout << "June " << day << endl;
	helpGrouping16(GF, GE, savePlace);
	helpGrouping16(GG, GH, savePlace);
}

void WorldCup::showTeam8()
{
	helpShowTeam8_4_2(8);
}

void WorldCup::grouping8()
{
	helpGrouping8_4_2(8);
}

void WorldCup::showTeam4()
{
	helpShowTeam8_4_2(4);
}

void WorldCup::grouping4()
{
	helpGrouping8_4_2(4);
}

void WorldCup::showTeam2()
{
	helpShowTeam8_4_2(2);
}

void WorldCup::grouping2()
{
	helpGrouping8_4_2(2);
}

void WorldCup::helpTeamShow(ofstream &out,int number, int amount, int &i)
{
	out << "(" << amount << ")" << endl;
	cout << "(" << amount << ")" << endl;
	for (; i < number; i++) {
		cout << '\t' << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
		out << '\t' << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
	}
}

void WorldCup::helpSetPlot(vector<Team*>& tempPot,int amount,int &i)
{
	for (; i < amount; i++) {
		if (totalTeams[i].getRank() <= 7 || totalTeams[i].getRank() == hostRank)
			pot1.push_back(&totalTeams[i]);
		else
			tempPot.push_back(&totalTeams[i]);
	}
}

void WorldCup::helpGrouping32(vector<Team*>& tempPot, int ok)
{
	srand((unsigned)time(NULL));
	bool check[8];
	for (int i = 0; i < 8; i++)check[i] = false;
	while (tempPot.size()) {
		bool flag = false;
		int index = rand() % tempPot.size();
		if (tempPot[index]->getRank() == hostRank) {
			helpGrouping32_1(tempPot, index, GA);
			tempPot.erase(tempPot.begin() + index);
			check[0] = true;
			continue;
		}
		for (int i = ok; i < 8; i++) {
			switch (i) {
			case 0:
				if(!check[i])
					flag = helpGrouping32_1(tempPot, index, GA);
				if (flag)check[i] = true;
				break;
			case 1:
				if (!check[i])
					flag = helpGrouping32_1(tempPot, index, GB);
				if (flag)check[i] = true;
				break;
			case 2:
				if (!check[i])
					flag = helpGrouping32_1(tempPot, index, GC);
				if (flag)check[i] = true;
				break;
			case 3:
				if (!check[i])
					flag = helpGrouping32_1(tempPot, index, GD);
				if (flag)check[i] = true;
				break;
			case 4:
				if (!check[i])
					flag = helpGrouping32_1(tempPot, index, GE);
				if (flag)check[i] = true;
				break;
			case 5:
				if (!check[i])
					flag = helpGrouping32_1(tempPot, index, GF);
				if (flag)check[i] = true;
				break;
			case 6:
				if (!check[i])
					flag = helpGrouping32_1(tempPot, index, GG);
				if (flag)check[i] = true;
				break;
			case 7:
				if (!check[i])
					flag = helpGrouping32_1(tempPot, index, GH);
				if (flag)check[i] = true;
				break;
			default:
				break;
			}
			if (flag)break;
		}
		tempPot.erase(tempPot.begin() + index);
	}
}
bool WorldCup::helpGrouping32_1(vector<Team*>&tempPot, int index, Group &tempGroup)
{
	if (tempPot[index]->getContinent() != "EUROPE"&&tempGroup.continent[tempPot[index]->getContinent()] == 0) {
		tempGroup.continent[tempPot[index]->getContinent()] = 1;
		tempGroup.group.push_back(tempPot[index]);
		return true;
	}
	else if (tempGroup.continent[tempPot[index]->getContinent()] < 2) {
		tempGroup.continent[tempPot[index]->getContinent()] ++;
		tempGroup.group.push_back(tempPot[index]);
		return true;
	}
	return false;
}



void WorldCup::setTeamAmount(int _CAF, int _CONMEBOL, int _AFC,int _OFC, int _CONCACAF, int _UEFA)
{
	CAF = _CAF; CONMEBOL = _CONMEBOL; AFC = _AFC;
	CONCACAF = _CONCACAF; UEFA = _UEFA; OFC = _OFC;
}

void WorldCup::helpPotShow(ofstream & out, vector<Team*>& tempPot)
{
	for (unsigned int i = 0; i < tempPot.size(); i++) {
		out << '\t' << tempPot[i]->getCountry() << endl;
		cout << '\t' << tempPot[i]->getCountry() << endl;
	}
}

void WorldCup::helpSchedule16(Group tempGroup, multimap<int,string>& day_info, const vector<string>&tempPlace, int _day,int match)
{
	cout << "Group " << tempGroup.groupName << endl;
	int j = 1,temp1,temp2; bool ok;
	while (j != 4) {
		ok = false;
		cout << '\t' << tempGroup.group[0]->getCountry() << " vs " << tempGroup.group[j]->getCountry();
		cout << "," << tempPlace[_day * 4 + match] << "," << "June " << day << endl;
		day_info.insert(pair<int, string>(day, tempGroup.group[0]->getCountry()
			+ " vs " + tempGroup.group[j]->getCountry() + "," + tempPlace[_day * 4 + match]));
		day+=2;
		_day += 2;
		for (unsigned int t = 0; t < tempGroup.group.size(); t++) {
			if (!ok&&t != 0 && t != j) {
				cout << '\t' << tempGroup.group[t]->getCountry() << " vs ";
				ok = true;
				temp1 = t;
			}
			else if (ok&&t != 0 && t != j) {
				cout << tempGroup.group[t]->getCountry() << "," << tempPlace[_day*4+match] << "," << "June " << day << endl;
				temp2 = t;
			}
		}
		day_info.insert(pair<int, string>(day, tempGroup.group[temp1]->getCountry()
			+ " vs " + tempGroup.group[temp2]->getCountry() + "," + tempPlace[_day * 4 + match]));
		day+=2;
		_day += 2;
		j++;
	}
}

vector<string> WorldCup::helpGetMatchPlace()
{
	vector<string>savePlace;
	for (int i = 0; i < 6; i++) {
		vector<string>tempPlace = place;
		while (tempPlace.size()) {
			int index = rand() % tempPlace.size();
			savePlace.push_back(tempPlace[index]);
			tempPlace.erase(tempPlace.begin() + index);
		}
	}
	return savePlace;
}

void WorldCup::helpShowTeam16(Group tempGroup, int winner)
{
	if(winner==2)
		cout << "Group " << tempGroup.groupName<<endl;
	for (int i = 0; i < winner; i++) {
		cout << '\t' << i + 1 << ". " << GA.group[i]->getCountry() << endl;
	}
}

void WorldCup::helpGrouping16(Group tempGroup1, Group tempGroup2,vector<string> tempPlace)
{
	cout << '\t' << tempGroup1.group[0]->getCountry() << " vs " << tempGroup2.group[1]->getCountry();
	cout << " at " << tempPlace[0];
	day_info.insert(pair<int, string>(day, tempGroup1.group[0]->getCountry()
		+" vs "+ tempGroup2.group[1]->getCountry()+","+ tempPlace[0]));
	matchTeam.push_back(tempGroup1.group[0]);
	matchTeam.push_back(tempGroup2.group[1]);
	tempPlace.erase(tempPlace.begin());
}

void WorldCup::helpShowTeam8_4_2(int teamAmount)
{
	cout << "Qualified for round of :" << teamAmount << endl;
	for (int i = 0; i < teamAmount; i++)
		cout << '\t' << matchTeam[i] << endl;
}

void WorldCup::helpGrouping8_4_2(int teamAmount)
{
	day++;
	day_info.clear();
	srand((unsigned)time(NULL));
	cout << "June " << day << endl;
	vector<string>savePlace;
	vector<string>tempPlace = place;
	while (savePlace.size() != teamAmount/2) {
		int index = rand() % tempPlace.size();
		savePlace.push_back(tempPlace[index]);
		tempPlace.erase(tempPlace.begin() + index);
	}
	cout << "Schedule for round of :" << teamAmount << endl;
	for (int i = 0; i < teamAmount; i += 2) {
		day++;
		cout << matchTeam[i] << " vs " << matchTeam[i + 1] << "," << savePlace[0];
		savePlace.erase(savePlace.begin());
	}
}

