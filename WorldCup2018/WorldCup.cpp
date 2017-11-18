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
WorldCup::WorldCup()
{
	GA = Group('A');GB = Group('B');GC = Group('C');GD = Group('D');
	GE = Group('E');GF = Group('F');GG = Group('G');GH = Group('H');
	date.day = 14;
	date.month = "June";
}

void WorldCup::getTeamInfo()
{
	file = "data.txt";
	ifstream in(file);
	if (!in) {
		cout << "No such file." << endl;
		exit(0);
	}
	string _country,temp;
	int _rank;
	string _id, _name, _position,_continent;
	int _teamAbility, _playerAbility;
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
		tempTeam.setContinent(_continent);
		tempTeam.setRank(_rank);
		tempTeam.setAbility(_teamAbility);
		tempTeam.setCountry(_country);
		totalTeams.push_back(tempTeam);
	}
	int i = 0;
	for (int j = 0; j < 32; j++)
		for(int k=0;k<teamMember;k++,i++)
			totalTeams[j].setPlayer(&totalPlayers[i]);
	in.close();
}

void WorldCup::getPlaceInfo()
{
	file = "dataPlace.txt";
	ifstream in(file);
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
	file = "team32.txt";
	ofstream out(file);
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
	file = "finalDraw.txt";
	ofstream out;
	out.open(file, ios_base::app);
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
	file = "finalDraw.txt";
	ofstream out(file);
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
	file = "schedule16.txt";
	ofstream out(file);
	srand((unsigned)time(NULL));
	day_info.clear();
	vector<string>savePlace = helpGetMatchPlace();
	cout << "Matches by squads" << endl;
	out << "Matches by squads" << endl;
	int tempDay = date.day;
	int tempDay1 = date.day + 1;
	int i = 0;
	helpSchedule16(out, GA, day_info, savePlace, 0,0);
	date.day = tempDay1;
	helpSchedule16(out, GB, day_info, savePlace, 1,0);
	date.day = tempDay;
	helpSchedule16(out, GC, day_info, savePlace, 0,1);
	date.day = tempDay1;
	helpSchedule16(out, GD, day_info, savePlace, 1,1);
	date.day = tempDay;
	helpSchedule16(out, GE, day_info, savePlace, 0,2);
	date.day = tempDay1;
	helpSchedule16(out, GF, day_info, savePlace, 1,2);
	date.day = tempDay;
	helpSchedule16(out, GG, day_info, savePlace, 0,3);
	date.day = tempDay1;
	helpSchedule16(out, GH, day_info, savePlace, 1,3);
	date.day = tempDay;
	cout << "\nMatches by date" << endl;
	out << "\nMatches by date" << endl;
	for (int i = 0; i < 12; i++, date.day++) {
		cout << date.month << " " << date.day << endl;
		out << date.month << " " << date.day << endl;
		Range range = day_info.equal_range(date.day);
		for (IT j = range.first; j != range.second; j++) {
			cout << '\t' << j->second << endl;
			out << '\t' << j->second << endl;
		}
	}
	out.close();
}

void WorldCup::showTeam16()
{
	file = "team16.txt";
	ofstream out(file);
	cout << "Qualified for round of 16:" << endl;
	out << "Qualified for round of 16:" << endl;
	helpShowTeam16(out, GA);
	helpShowTeam16(out, GB);
	helpShowTeam16(out, GC);
	helpShowTeam16(out, GD);
	helpShowTeam16(out, GE);
	helpShowTeam16(out, GF);
	helpShowTeam16(out, GG);
	helpShowTeam16(out, GH);
	out.close();
}

void WorldCup::grouping16()
{
	file = "schedule8.txt";
	ofstream out(file);
	day_info.clear();
	srand((unsigned)time(NULL));
	vector<string>savePlace;
	vector<string>tempPlace = place;
	while (tempPlace.size()) {
		int index = rand() % tempPlace.size();
		savePlace.push_back(tempPlace[index]);
		tempPlace.erase(tempPlace.begin() + index);
	}
	cout << "Schedule for round of 16:" << endl;
	out << "Schedule for round of 16:" << endl;
	date++;
	cout << date.month << " " << date.day << endl;
	out << date.month << " " << date.day << endl;
	helpGrouping16(out, GA, GB, savePlace);
	helpGrouping16(out, GC, GD, savePlace);
	date++;
	cout << date.month << " " << date.day << endl;
	out << date.month << " " << date.day << endl;
	helpGrouping16(out, GE, GF, savePlace);
	helpGrouping16(out, GG, GH, savePlace);
	date++;
	cout << date.month << " " << date.day << endl;
	out << date.month << " " << date.day << endl;
	helpGrouping16(out, GB, GA, savePlace);
	helpGrouping16(out, GD, GC, savePlace);
	date++;
	cout << date.month << " " << date.day << endl;
	out << date.month << " " << date.day << endl;
	helpGrouping16(out, GF, GE, savePlace);
	helpGrouping16(out, GG, GH, savePlace);
	out.close();
}

void WorldCup::showTeam8()
{
	file = "team8.txt";
	ofstream out(file);
	helpShowTeam8_4_2(out, 8);
	out.close();
}

void WorldCup::grouping8()
{
	file = "schedule4.txt";
	ofstream out(file);
	helpGrouping8_4_2(out, 8);
	out.close();
}

void WorldCup::showTeam4()
{
	file = "team4.txt";
	ofstream out(file);
	helpShowTeam8_4_2(out, 4);
	out.close();
}

void WorldCup::grouping4()
{
	file = "schedule2.txt";
	ofstream out(file);
	helpGrouping8_4_2(out, 4);
	out.close();
}

void WorldCup::showTeam2()
{
	file = "team2.txt";
	ofstream out(file);
	helpShowTeam8_4_2(out, 2);
	out.close();
}

void WorldCup::grouping2()
{
	file = "schedule1.txt";
	ofstream out(file);
	helpGrouping8_4_2(out, 2);
	out.close();
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

void WorldCup::helpSchedule16(ofstream &out, Group tempGroup, multimap<int,string>& day_info, const vector<string>&tempPlace, int _day,int match)
{
	cout << "Group " << tempGroup.groupName << endl;
	out << "Group " << tempGroup.groupName << endl;
	int j = 1,temp1,temp2; bool ok;
	while (j != 4) {
		ok = false;
		cout << '\t' << tempGroup.group[0]->getCountry() << " vs " << tempGroup.group[j]->getCountry();
		out << '\t' << tempGroup.group[0]->getCountry() << " vs " << tempGroup.group[j]->getCountry();
		cout << "," << tempPlace[_day * 4 + match] << "," << date.month << date.day << endl;
		out << "," << tempPlace[_day * 4 + match] << "," << date.month << date.day << endl;
		day_info.insert(pair<int, string>(date.day, tempGroup.group[0]->getCountry()
			+ " vs " + tempGroup.group[j]->getCountry() + "," + tempPlace[_day * 4 + match]));
		date +=2;
		_day += 2;
		for (unsigned int t = 0; t < tempGroup.group.size(); t++) {
			if (!ok&&t != 0 && t != j) {
				cout << '\t' << tempGroup.group[t]->getCountry() << " vs ";
				out << '\t' << tempGroup.group[t]->getCountry() << " vs ";
				ok = true;
				temp1 = t;
			}
			else if (ok&&t != 0 && t != j) {
				cout << tempGroup.group[t]->getCountry() << "," << tempPlace[_day * 4 + match] << "," << date.month << date.day << endl;
				out << tempGroup.group[t]->getCountry() << "," << tempPlace[_day * 4 + match] << "," << date.month << date.day << endl;
				temp2 = t;
			}
		}
		day_info.insert(pair<int, string>(date.day, tempGroup.group[temp1]->getCountry()
			+ " vs " + tempGroup.group[temp2]->getCountry() + "," + tempPlace[_day * 4 + match]));
		date+=2;
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

void WorldCup::helpShowTeam16(ofstream &out, Group tempGroup)
{
		cout << "Group " << tempGroup.groupName<<endl;
		out << "Group " << tempGroup.groupName << endl;
	for (int i = 0; i < 2; i++) {
		cout << '\t' << i + 1 << ". " << tempGroup.group[i]->getCountry() << endl;
		out << '\t' << i + 1 << ". " << tempGroup.group[i]->getCountry() << endl;
	}
}

void WorldCup::helpGrouping16(ofstream &out, Group tempGroup1, Group tempGroup2,vector<string>& tempPlace)
{
	cout << '\t' << tempGroup1.group[0]->getCountry() << " vs " << tempGroup2.group[1]->getCountry();
	out << '\t' << tempGroup1.group[0]->getCountry() << " vs " << tempGroup2.group[1]->getCountry();
	cout << " at " << tempPlace[0] << endl;
	out << " at " << tempPlace[0] << endl;
	day_info.insert(pair<int, string>(date.day, tempGroup1.group[0]->getCountry()
		+" vs "+ tempGroup2.group[1]->getCountry()+","+ tempPlace[0]));
	matchTeam.push_back(tempGroup1.group[0]);
	matchTeam.push_back(tempGroup2.group[1]);
	tempPlace.erase(tempPlace.begin());
}

void WorldCup::helpShowTeam8_4_2(ofstream &out, int teamAmount)
{
	cout << "Qualified for round of :" << teamAmount << endl;
	out << "Qualified for round of :" << teamAmount << endl;
	for (int i = 0; i < teamAmount; i++) {
		cout << '\t' << matchTeam[i]->getCountry() << endl;
		out << '\t' << matchTeam[i]->getCountry() << endl;
	}
}

void WorldCup::helpGrouping8_4_2(ofstream &out, int teamAmount)
{
	date++;
	day_info.clear();
	srand((unsigned)time(NULL));
	vector<string>savePlace;
	vector<string>tempPlace = place;
	while (savePlace.size() != teamAmount/2) {
		int index = rand() % tempPlace.size();
		savePlace.push_back(tempPlace[index]);
		tempPlace.erase(tempPlace.begin() + index);
	}
	cout << "Schedule for round of :" << teamAmount << endl;
	out << "Schedule for round of :" << teamAmount << endl;
	for (int i = 0; i < teamAmount; i += 2) {
		date++;
		cout << date.month << " " << date.day << endl;
		out << date.month << " " << date.day << endl;
		cout << '\t' << matchTeam[i]->getCountry() << " vs " << matchTeam[i + 1]->getCountry() << ","
			<< savePlace[0] << endl;
		out << '\t' << matchTeam[i]->getCountry() << " vs " << matchTeam[i + 1]->getCountry() << ","
			<< savePlace[0] << endl;
		savePlace.erase(savePlace.begin());
	}
}

