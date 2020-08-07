#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <vector>
#include <tuple>
#include <algorithm>
#include <stdlib.h>
#include "PreAction.h"
#include "ForwardSimulation.h"
#include <random>
#include <bitset>
#include <chrono>
using namespace std;

class Push
{
public:
	Push(string& u, char& num) : objectiveUnit(u), obNum(num) {
		vector<tuple<string, string, string>> allUnits = getUnitsFromTechTree(objectiveUnit);
		eliteNum = 200;
		//initialize random seed
		srand(0);

		//get and save the productionStruct and dependency
		for (tuple<string, string, string>& t : allUnits) {
			if (get<0>(t) == objectiveUnit)
			{
				ProductionStruct = get<1>(t);
				dependency = get<2>(t);
			}
		}
		//cout <<"here push 35" <<endl;
		//cout <<"Objective Unit:" << objectiveUnit <<endl;
		//cout <<"produce_by: "<<ProductionStruct <<endl<<endl;
		//cout <<"dependency :" << dependency<<endl<<endl;
		if (dependency == "") 
		{skeleton = formSkeleton(ProductionStruct, allUnits);}
		else 
		{
			
			skeleton = formSkeleton(dependency, allUnits);
			
		}
		if(objectiveUnit == "Battlecruiser")
			skeleton.push_back("StarportTechLab");
		if(objectiveUnit == "SiegeTank")
			skeleton.insert(skeleton.begin()+3,"Starport");
				

		for (char i = 0; i < obNum; i++){skeleton.push_back(objectiveUnit);}
		//for(string s:skeleton){cout<<s<<endl;}
		
		
		//cout<<"************"<<endl;
		//for (string s : skeleton) cout << s << endl;
		canBeBuilt = {  worker,supply, ProductionStruct };
		baseUnits = { supply };

		if (vespene > 0) {
			canBeBuilt.push_back(assimilator);
			baseUnits.push_back(assimilator);
		}
		if (objectiveUnit == worker) canBeBuilt.push_back(baseCamp);//zerg ignore
		//if(objectiveUnit == "Battlecruiser") skeleton.push_back("StarportTechLab");

	};
	vector<string> push(vector<vector<string>>& generation, int& loops) {
		vector<vector<string>> newGeneration;
		ForwardSimulation fS(obNum, objectiveUnit);
		//cout <<"After forwardsimulation 71"<<endl;
		vector<tuple<size_t, tuple<char, char, size_t, char>, vector<string>>> result;
		tuple<char, char, size_t, char> temp;
		//cout <<"in the oush method)" <<endl;
		for (vector<string>& individual : generation) {
			temp = fS.ForwardSim(individual);
			
			if (get<0>(temp) >= 0) {

				result.push_back(make_tuple(size_t(0), temp, individual));
			}
		}
		
		vector<string> kinglist;
		
		if(result.size()>0) {
			generation = selection(result);
	
		
			//cout <<"****selection*******"<<endl;
			size_t minTime = 1000;
		
			for (char i = 0; i < loops; i++) {
				//cout << "loop " << i + 1 << endl;
				if(result.size() > 0)
				{
					//cout<<"the kinglist size is:"<<kinglist.size()<<endl;
					vector<tuple<size_t, tuple<char, char, size_t, char>, vector<string>>>().swap(result);

					mutation(generation);
					filter(generation);
					//cout<<"the generation size is :"<<generation.size()<<endl;
					//cout<<"after generation and filter"<<endl;
					newGeneration = Reproduction(generation);
					//cout<<"the newGeneration size is 1: "<<newGeneration.size()<<endl;
					auto end =  chrono::system_clock::now();
					auto duration = chrono::duration_cast<chrono::seconds>(end - start);
					
					if (duration.count() >= 170) {
						vector<vector<string>>().swap(generation);
						return kinglist;
					}
					vector<vector<string>>().swap(generation);

					filter(newGeneration);
					//cout<<"the newGeneration size is 2:"<<newGeneration.size()<<endl;
					//cout<<"after second filter"<<endl;
					for (vector<string>& individual : newGeneration) {
						temp = fS.ForwardSim(individual);
						//cout<<"in the loop temp" << get<0>(temp)<<endl;
						if (get<0>(temp) > 0) {
							//temp = fS.ForwardSim();
							result.push_back(make_tuple(size_t(0), temp, individual));
						}
					}
					//cout<<"temp" <<endl;
					vector<vector<string>>().swap(newGeneration);
					end = chrono::system_clock::now();
					duration = chrono::duration_cast<chrono::seconds>(end - start);
					if (duration.count() >= 170) {
						vector<vector<string>>().swap(generation);
						return kinglist;
					}
					//cout<<"kinglist"<<endl;
				
					if(result.size()>0){
					generation = selection(result);
					
				
					//cout<<"kinglist"<<endl;
					size_t& unitNum = get<2>(get<1>(result[0]));
					//cout<<"generation2"<<endl;
					if (unitNum < minTime) {//cout<<"generation3"<<endl;
						minTime = unitNum;
						kinglist = get<2>(result[0]);
					}//cout<<"the kinglist size is 2:"<<kinglist.size()<<endl;
					//cout<<"kinglist11111"<<endl;
					generation.push_back(kinglist);
					end = chrono::system_clock::now();
					duration = chrono::duration_cast<chrono::seconds>(end - start);
					if (duration.count() >= 170) {
						vector<vector<string>>().swap(generation);
						return kinglist;
					}
				
				}
		
			}
		}
	}
		
		return kinglist;
}
	vector<tuple<string, string, string>> getUnitsFromTechTree(string& unit) {
		vector<tuple<string, string, string>> aU;
		ifstream outfile(techTree, ifstream::in);
		string name = "";
		string pass;
		getline(outfile, pass, '\n');
		getline(outfile, pass, '\n');
		while (!outfile.eof())//if has not been the end of the file
		{
			getline(outfile, name, ',');
			if (name != "#buildings" && name !="")
			{
				if (name == unit)
				{
					getline(outfile, pass, ',');
					getline(outfile, pass, ',');
					vespene = stoi(pass);
					for (size_t i = 0; i < 6; i++)
					{
						getline(outfile, pass, ',');
					}
				}
				else
				{
					for (size_t i = 0; i < 8; i++)
					{
						getline(outfile, pass, ',');
					}
				}
				getline(outfile, ProductionStruct, ',');
				getline(outfile, dependency, '\n');
				aU.push_back(make_tuple(name, ProductionStruct, dependency));
			}
			else{getline(outfile, pass, '\n');}
		}
		outfile.close();
		return aU;
	}
	string randomUnit(vector<string>& canBeBuilded) {
		char length = canBeBuilded.size();
		string unit = canBeBuilded[rand() % length];
		return unit;
	}

	vector<string> formSkeleton(string& dependency, vector<tuple<string, string, string>>& allUnits) {
		vector<string> skeleton;
		string d = "";
		//string producer="";
			//cout <<"in the form process: dependency is" << dependency <<endl; 
		if (dependency != supply && dependency !="")//"pylon" for protoss; "supply_depot" for terren; "hatchery" for zerg
		{
				//cout<<"THe first dependency" << dependency <<endl;
				if(dependency == "Starport/StarportTechLab/StarportReactor") {dependency = "Starport";}
				if(dependency == "Factory/FactoryReactor/FactoryTechLab") {dependency = "Factory";}
				if(dependency == "Barracks/BarracksTechLab/BarracksReactor") {dependency = "Barracks";}	
				
					
					
			//cout <<"the thing to be built"<<dependency<<endl;
			for (tuple<string, string, string>& t : allUnits) {
				
				if (get<0>(t) == dependency) {
					if(get<2>(t) =="")
					{
						d =get<1>(t);
					}
					else{d = get<2>(t);}
				}
			}
			//cout <<" the nect building : " << d << endl;
			skeleton = formSkeleton(d, allUnits);
			//if(dependency == "FusionCore" ) {skeleton.push_back("StarportTechLab");}
			skeleton.push_back(dependency);
			return skeleton;
		} 
		
		else {
			skeleton.push_back(supply);		
			return skeleton;
		}
		
		
		
	
		
		//skeleton.push_back(dependency);
		//cout <<"form compelete"<<endl;
		//return skeleton;
	}
	vector<string> buildListGenerator() {
		char refinery = 0;
		char proDuc = 0;
		vector<string> buildList = skeleton;

		string unit = "";
		char length = rand() % 10 + 15;
		char availLength = length - buildList.size();
		for (char j = 0; j < availLength; j++)
		{
			char i = 0;
			char k = 0;
			for (i = 0; i < buildList.size(); i++)
			{
				if (buildList[i] == ProductionStruct) {
					break;
				}
			}
			if (dependency == "") k = i;
			else {
				for (k = 0; k < buildList.size(); k++)
				{
					if (buildList[k] == dependency) {
						break;
					}
				}
			}
			char position = rand() % buildList.size();
			if (position <= i)
			{
				if (refinery >= 2)
				{
					do
					{
						unit = randomUnit(baseUnits);
					} while (unit == assimilator);
				}
				else {
					char possibility = rand() % 5;
					if (possibility < 2) unit = randomUnit(baseUnits);
					else unit = worker;
					buildList.insert(buildList.begin() + position, unit);
				}
			}
			else {
				if (refinery >= 2)
				{
					do
					{
						unit = randomUnit(canBeBuilt);
					} while (unit == assimilator);
				}
				else {
					bool pass = true;
					do {
						pass = true;
						unit = randomUnit(canBeBuilt);
						if (proDuc == obNum && unit == ProductionStruct) pass = false;
					} while (!pass);
				}
				buildList.insert(buildList.begin() + position, unit);
			}
			if (unit == assimilator) refinery++;
			if (unit == ProductionStruct) proDuc++;
		}
		return buildList;
	}

	vector<vector<string>> firstGeneration() {
		vector<vector<string>> fG;
		for (size_t i = 0; i < individual; i++)
		{
			fG.push_back(buildListGenerator());
		}
		return fG;
	}
	vector<vector<string>> selection(vector<tuple<size_t, tuple<char, char, size_t, char>, vector<string>>>& r) {
		vector<vector<string>> elites;
		vector<tuple<size_t, tuple<char, char, size_t, char>, vector<string>>> results;
		PreAction pA(techTree);

		
		for (tuple<size_t, tuple<char, char, size_t, char>, vector<string>>& ind : r) {
			vector<string>& indi = get<2>(ind);
			if (pA.preCheck(indi)) {
				results.push_back(ind);
			}
		}
		int eliteNum = min(this->eliteNum, results.size());

		
		sort(results.begin(), results.end(), sortByWorker);
		
		for (int i = eliteNum; i >= 0; i--) {
			get<0>(results[eliteNum - i]) += i;
		}
		
		sort(results.begin(), results.end(), sortByUnit);
		reverse(results.begin(), results.end());
		for (int i = eliteNum; i >= 0; i--) {
			get<0>(results[eliteNum - i]) += i;
		}
		
		int maxOb = get<2>(get<1>(results[0]));

		sort(results.begin(), results.end(), sortByRate);
		
		//if(results.size()>eliteNum){
			for (int i = 0; i < eliteNum; i++) {
				elites.push_back(get<2>(results[i]));
			}
		//}
		/*else{
			for (int i = 0; i < results.size(); i++) {
				elites.push_back(get<2>(results[i]));
			}
		}*/

		sort(results.begin(), results.end(), sortByUnit);
		reverse(results.begin(), results.end());
		r = results;
		return elites;
	}
	void mutation(vector<vector<string>>& generation) {
		char randNumber;
		char i = 0;
		char k = 0;
		string unit = "";
		for (vector<string>& indi : generation) {
			randNumber = rand() % 20;
			if (randNumber == 0 || randNumber == 1)
			{
				randNumber = rand() % 2;
				if (randNumber == 0)// add units
				{
					for (i = 0; i < indi.size(); i++)
					{
						if (indi[i] == ProductionStruct) {
							break;
						}
					}
					if (dependency == "") k = i;
					else {
						for (k = 0; k < indi.size(); k++)
						{
							if (indi[k] == dependency) {
								break;
							}
						}
					}

					randNumber = rand() % (indi.size() + 1);
					if (randNumber <= i)
					{
						unit = randomUnit(baseUnits);
						indi.insert(indi.begin() + randNumber, unit);
					}
					else {
						unit = randomUnit(canBeBuilt);
						indi.insert(indi.begin() + randNumber, unit);
					}
				}
				else// remove units
				{
					randNumber = rand() % indi.size();
					indi.erase(indi.begin() + randNumber);
				}
			}
		}
	}
	void filter(vector<vector<string>>& generation) {
		char length = 0;
		if(generation.size()>=1){
			for (size_t i = 0; i < generation.size() - 1; i++) {
				for (size_t j = i + 1; j < generation.size(); j++) {
					bool same = true;
					length = min(generation[i].size(), generation[j].size());
					for (char k = length - 1; k >= 0; k--) {
						if (generation[i][k] != generation[j][k]) {
							same = false; break;
						}
					}
					if (same == true) {
						swap(generation[j], generation[generation.size() - 1]);
						generation.pop_back();
						j--;
					}
				}
			}
		}
	}
	bool filter(vector<vector<string>>& generation, vector<string>& vString) {
		char length = 0;
		for (size_t i = 0; i < generation.size(); i++) {
			length = min(generation[i].size(), vString.size());
			bool same = true;
			for (char k = length - 1; k >= 0; k--) {
				if (generation[i][k] != vString[k])
				{
					same = false;
					break;
				}
			}
			if (same)
			{
				return true;
			}
		}
		return false;
	}
	vector<vector<string>> Reproduction(vector<vector<string>>& oldGeneration)
	{
		vector<vector<string>> newGeneration;
		vector<vector<string>> babies;
		tuple<size_t, size_t> selected;
		vector<size_t> indexS;
		for (size_t i = 0; i < oldGeneration.size(); i++) indexS.push_back(i);
		shuffle(indexS.begin(), indexS.end(), seed);
		while (indexS.size() > 0) {
			auto end = chrono::system_clock::now();
			auto duration = chrono::duration_cast<chrono::seconds>(end - start);
			if (duration.count() >= 175) {
				return newGeneration;
			}
			if (indexS.size() >= 3)
			{
				int size = oldGeneration.size();
				vector<size_t> index(indexS.begin(), indexS.begin() + min(4, size));
				
				selected = distanceSelection(oldGeneration, index);
				vector<size_t>().swap(index);
				for (char i = 0; i < 2; i++) {
					for (size_t pos = 0; pos < indexS.size(); pos++) {
						if (indexS[pos] == get<0>(selected) || indexS[pos] == get<1>(selected))
						{
							swap(indexS[pos], indexS[indexS.size() - 1]);
							indexS.pop_back();
						}
					}
				}
				shuffle(indexS.begin(), indexS.end(), seed);
				vector<string>& father = oldGeneration[get<0>(selected)];
				vector<string>& mother = oldGeneration[get<1>(selected)];
				babies = makeBabies(father, mother);
				newGeneration.insert(newGeneration.end(), babies.begin(), babies.end());
			}
			else if (indexS.size() == 1)
			{
				vector<size_t>().swap(indexS);
				if (!filter(oldGeneration, oldGeneration[0]))
					newGeneration.push_back(oldGeneration[0]); \
					break;
			}
			else if (indexS.size() == 2) {
				vector<size_t>().swap(indexS);
				babies = makeBabies(oldGeneration[0], oldGeneration[1]);
				newGeneration.insert(newGeneration.end(), babies.begin(), babies.end());
				break;
			}
			vector<vector<string>>().swap(babies);
		}
		vector<string>list;
		for (size_t i = 0; i < (individual / 20); i++) {
			list = buildListGenerator();
			newGeneration.push_back(list);
		}
		return newGeneration;
	}

	

	tuple<size_t, size_t> distanceSelection(vector<vector<string>>& oldGeneration, vector<size_t>& index)
	{
		char length;
		size_t dis = 0;
		size_t maxDis = 0;
		size_t a = index[0];
		size_t b = index[1];
		vector<string> listA;
		vector<string> listB;
		for (int i = 0; i < index.size() - 1; i++) {
			for (int j = i + 1; j < index.size(); j++) {
				listA = oldGeneration[index[i]];
				listB = oldGeneration[index[j]];
				if (listA.size() != listB.size())
				{
					length = max(listA.size(), listB.size());
					Extension(length, listA);
					Extension(length, listB);
				}
				dis = distance(listA, listB);
				if (dis > maxDis)
				{
					a = index[i]; b = index[j];
				}
			}
		}

		return make_tuple(a, b);
	}

	//extend the buildlist to make the size of the list equal to the length
	vector<string> Extension(char& length, vector<string>& temp) {

		while (temp.size() < length) {
			char index = rand() % canBeBuilt.size();
			temp.push_back(canBeBuilt[index]);
		}
		return temp;
	}

	//calculate the diff between two buildlists. the more different the bigger the score
	size_t distance(vector<string>& tempA, vector<string>& tempB) {
		char length = tempA.size();
		size_t distance = 0;
		for (char i = 0; i < length; i++) {
			if (tempA[i] != tempB[i])
				distance += length - i;
		}
		return distance;
	}
	vector<vector<string>> makeBabies(vector<string>& father, vector<string>& mother) {
		//auto start = chrono::high_resolution_clock::now();
		char length = max(father.size(), mother.size());
		Extension(length, father);
		Extension(length, mother);
		vector<vector<string>> babies;
		PreAction pA(techTree);

		vector<string> skeleton(length);
		char count = 0;
		for (char i = 0; i < length; i++) {
			if (father[i] == mother[i]) {
				skeleton[i] == father[i];
				count++;
			}
		}

		char diff = length - count;
		size_t MAXSIZE = pow(2, diff);
		vector<size_t> indexS;
		for (size_t i = 1; i < MAXSIZE - 1; i++) {
			indexS.push_back(i);
		}
		shuffle(indexS.begin(), indexS.end(), seed);

		vector<string> temp;
		for (size_t i = 0; (i < indexS.size()) && (i < birthControl); i++)
		{
			bitset<sizeof(size_t) * 8> index(indexS[i]);
			temp = skeleton;
			int pos = 0;
			for (unsigned int j = 0; j < length; j++) {
				if (temp[j].empty())
				{
					if (index[pos])	temp[j] = father[j];
					else temp[j] = mother[j];
					pos++;
				}
			}
			if (!filter(babies, temp)) {
				if (pA.preCheck(temp))babies.push_back(temp);
			}
			vector<string>().swap(temp);
		}
		vector<string>().swap(skeleton);
		return babies;
	}
private:
	string objectiveUnit;
	string ProductionStruct;
	string dependency;
	string techTree = "terran.csv";
	vector<string> skeleton;
	size_t individual = 10000;
	size_t eliteNum;
	string baseCamp = "CommandCenter";
	string worker = "SCV";
	string supply = "SupplyDepot";
	string firstBarrack = "Barracks";
	string assimilator = "Refinery";
	vector<string> canBeBuilt;
	vector<string> baseUnits;
	int vespene = 0;
	default_random_engine seed = default_random_engine(0);
	size_t birthControl = 20;
	char obNum;
	chrono::system_clock::time_point start = chrono::system_clock::now();
};
