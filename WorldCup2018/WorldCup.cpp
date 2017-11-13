#include "WorldCup.hpp"
#include<fstream>
#include<string>
#include<iostream>
#include <cstdlib> 
#include <ctime>  
using namespace std;

#define hostRank 0
#define teamMember 11
WroldCup::WroldCup()
{

}

void WroldCup::getTeamInfo()
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
			tempTeam.setPlayer(tempPlayer);
			totalPlayers.push_back(tempPlayer);
		}
		tempTeam.setContinent(_continent);
		tempTeam.setRank(_rank);
		tempTeam.setAbility(_teamAbility);
		tempTeam.setCountry(_country);
		totalTeams.push_back(tempTeam);
	}
	in.close();
}

void WroldCup::showTeamInfo()
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
	/*out << "CAF(" << CAF << ")" << endl;
	cout<< "CAF(" << CAF << ")" << endl;
	for (; i < CAF; i++) {
		cout << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
		out << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
	}
	out << "CONMEBOL(" << CONMEBOL << ")" << endl;
	cout << "CONMEBOL(" << CONMEBOL << ")" << endl;
	for (; i < CONMEBOL; i++) {
		cout << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
		out << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
	}
	out << "AFC(" << AFC << ")" << endl;
	cout << "AFC(" << AFC << ")" << endl;
	for (; i < AFC; i++) {
		cout << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
		out << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
	}
	out << "CONCACAF(" << CONCACAF << ")" << endl;
	cout << "CONCACAF(" << CONCACAF << ")" << endl;
	for (; i < CONCACAF; i++) {
		cout << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
		out << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
	}
	out << "UEFA(" << UEFA << ")" << endl;
	cout << "UEFA(" << UEFA << ")" << endl;
	for (; i < UEFA; i++) {
		cout << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
		out << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
	}*/
	out.close();
}

void WroldCup::showGroupInfo()
{
	/*ofstream out;
	out.open("finalDraw.txt", ios_base::app);
	out << "The Final Draw:" << endl;
	cout << "The Final Draw:" << endl;
	out << "group A" << endl;
	cout << "group A" << endl;
	helpPotShow(out, GA);
	out << "group B" << endl;
	cout << "group B" << endl;
	helpPotShow(out, GB);
	out << "group C" << endl;
	cout << "group C" << endl;
	helpPotShow(out, GC);
	out << "group D" << endl;
	cout << "group D" << endl;
	helpPotShow(out, GD);
	out << "group E" << endl;
	cout << "group E" << endl;
	helpPotShow(out, GE);
	out << "group F" << endl;
	cout << "group F" << endl;
	helpPotShow(out, GF);
	out << "group G" << endl;
	cout << "group G" << endl;
	helpPotShow(out, GG);
	out << "group H" << endl;
	cout << "group H" << endl;
	helpPotShow(out, GH);
	out.close();*/
	
}

void WroldCup::showPotInfo()
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

void WroldCup::setPot()
{
	int i = 0;
	helpSetPlot(pot2, CAF + CONMEBOL, i);
	helpSetPlot(pot3, CAF + CONMEBOL+ AFC+ CONCACAF, i);
	helpSetPlot(pot4, CAF + CONMEBOL + AFC + CONCACAF+ UEFA, i);

	/*for (; i < CAF+ CONMEBOL; i++) {
		if(totalTeams[i].getRank()<=7|| totalTeams[i].getRank()==hostRank)
			pot1.push_back(totalTeams[i]);
		else
			pot2.push_back(totalTeams[i]);
	}
	for (; i < AFC + CONCACAF; i++) {
		if (totalTeams[i].getRank() <= 7 || totalTeams[i].getRank() == hostRank)
			pot1.push_back(totalTeams[i]);
		else
		pot3.push_back(totalTeams[i]);
	}
	for (; i < UEFA; i++) {
		if (totalTeams[i].getRank() <= 7 || totalTeams[i].getRank() == hostRank)
			pot1.push_back(totalTeams[i]);
		else
		pot4.push_back(totalTeams[i]);
	}*/
}

void WroldCup::grouping()
{
	helpGrouping(pot1,true);
	helpGrouping(pot2,false);
	helpGrouping(pot3, false);
	helpGrouping(pot4, false);
	/*vector<int> label1, label2, label3, label4;
	for (int i = 0; i < 8; i++) {
		label1.push_back(i);
		label2.push_back(i);
		label3.push_back(i);
		label4.push_back(i);
	}
	srand((unsigned)time(NULL));
	int indexNow = 1;
	while(pot1.size()){
		int index = rand() % pot1.size();
		if (pot1[index].getRank() == hostRank) {
			GA.push_back(pot1[index]);
			pot1.erase(pot1.begin() + index);
		}
		else {
			switch (indexNow) {
			case 1:
				GB.push_back(pot1[index]);
				break;
			case 2:
				GC.push_back(pot1[index]);
				break;
			case 3:
				GD.push_back(pot1[index]);
				break;
			case 4:
				GE.push_back(pot1[index]);
				break;
			case 5:
				GF.push_back(pot1[index]);
				break;
			case 6:
				GG.push_back(pot1[index]);
				break;
			case 7:
				GH.push_back(pot1[index]);
				break;
			default:
				break;
			}
			indexNow++;
		}
	}*/
}

void WroldCup::helpTeamShow(ofstream &out,int number, int amount, int &i)
{
	out << "(" << amount << ")" << endl;
	cout << "(" << amount << ")" << endl;
	for (; i < number; i++) {
		cout << '\t' << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
		out << '\t' << totalTeams[i].getCountry() << "(" << totalTeams[i].getRank() << ")" << endl;
	}
}

void WroldCup::helpSetPlot(vector<Team>& tempPot,int amount,int &i)
{
	for (; i < amount; i++) {
		if (totalTeams[i].getRank() <= 7 || totalTeams[i].getRank() == hostRank)
			pot1.push_back(totalTeams[i]);
		else
			tempPot.push_back(totalTeams[i]);
	}
}

void WroldCup::helpGrouping(vector<Team>& tempPot,bool ok)
{
	srand((unsigned)time(NULL));
	int indexNow=0;
	if (ok)indexNow = 1;
	while (tempPot.size()) {
		int index = rand() % tempPot.size();
		if (tempPot[index].getRank() == hostRank) {
			GA.group.push_back(pot1[index]);
			tempPot.erase(pot1.begin() + index);
		}
		else {
			switch (indexNow) {
			case 0:
				GA.group.push_back(tempPot[index]);
				break;
			case 1:
				GB.group.push_back(tempPot[index]);
				break;
			case 2:
				GC.group.push_back(tempPot[index]);
				break;
			case 3:
				GD.group.push_back(tempPot[index]);
				break;
			case 4:
				GE.group.push_back(tempPot[index]);
				break;
			case 5:
				GF.group.push_back(tempPot[index]);
				break;
			case 6:
				GG.group.push_back(tempPot[index]);
				break;
			case 7:
				GH.group.push_back(tempPot[index]);
				break;
			default:
				break;
			}
			tempPot.erase(tempPot.begin() + index);
			indexNow++;
		}
	}
}

void WroldCup::setTeamAmount(int _CAF, int _CONMEBOL, int _AFC,int _OFC, int _CONCACAF, int _UEFA)
{
	CAF = _CAF; CONMEBOL = _CONMEBOL; AFC = _AFC;
	CONCACAF = _CONCACAF; UEFA = _UEFA; OFC = _OFC;
}

void WroldCup::helpPotShow(ofstream & out, vector<Team>& tempPot)
{
	for (int i = 0; i < tempPot.size(); i++) {
		out << '\t' << tempPot[i].getCountry() << endl;
		cout << '\t' << tempPot[i].getCountry() << endl;
	}
}

