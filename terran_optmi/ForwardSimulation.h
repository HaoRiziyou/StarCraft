//Optimization
//ForwardSimulation.h
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "PreAction.h"
#include "Resources.h"
#include "Timer.h"
#include "JsonMaster.h"
#include "Buildings.h"
#include "BuildedList.h"
#include "Checker.h"
#include "Builder.h"
#include "ScvManager.h"
using namespace std;
class ForwardSimulation {
public:
	ForwardSimulation(string targetUnit, size_t Time = 700): unit(targetUnit), maxTime(Time) {

	}
	ForwardSimulation(char obNum, string targetUnit) : unit(targetUnit), unitNumber(obNum), maxTime(700) {

	}
	bool checkAndBuild(char i, Checker& checker, Builder& builder) {
		string s = checker.CheckMaster(i);
		if (s != "busy")
		{
			builder.build(i,s);
			return true;
		}
		else return false;
	}
	tuple<char, char, size_t, char> ForwardSim(vector<string>& rawList) {//cout<<"now in foewardsim"<<endl;
		//for(string s:rawList){cout<<s<<endl;}
		PreAction pAction("terran.csv");
		//cout<<"now in foewardsim "<<endl;
		vector<map<string, string>> toBuildList;
		Resources resources;
		Timer timer;
		string productionStruct = pAction.getProductionStruct(unit);
			//cout<<"now in foewardsim 2"<<endl;
		if (!pAction.preCheck(rawList)) {
			//cout<<"Do not pass the precheck"<<endl;
			return make_tuple(char(0), char(0), char(0), char(0));
		}
		else toBuildList = pAction.getDetailedBuildList();

		BuildedList buildedList;
		Checker checker(timer, resources, buildedList, toBuildList);
		Builder builder(timer, resources, buildedList, toBuildList, productionStruct, unit, maxTime, false, unitNumber);
		//cout<<"Passing the resources"<<endl<<endl;
		char listLength = toBuildList.size();
		ScvManager scvManager(resources, toBuildList, buildedList, listLength);
		//cout<<"Forwarding Start******"<<endl;
		vector<map<string, string>>().swap(toBuildList);
		size_t extendedMaxTime = maxTime + 60;
		char i = 0;
		for (; timer.getCurrentTime() <= extendedMaxTime; timer.timeIncf())
		{
			resources.collectResources(buildedList.getScvList());
			builder.proceed();//build one second
			//cout<<"now in foewardsim 5"<<endl;
			scvManager.manageScvs(i);//adjust the number of scvs in minerals and vespene
			if (!builder.chronoBoost()) {
				if (i < listLength) {
					if (checkAndBuild(i, checker, builder))i++;
				}
			}

			if (!builder.hasEvents() && builder.proceedListEmpty() && i == listLength)
			{
				break;
			}
		}
		if (!builder.proceedListEmpty() || i < listLength) {
			builder.deleteProceedList();
		}//cout<<"*****nding Simulation*********"<<endl;
		tuple<char, char, size_t, char> temp = builder.getdata();//cout<<"pass check"<<endl;
		return temp;
	}
	bool ForSimulation(vector<string>& rawList, bool json = false) {
		PreAction pAction("terran.csv");
		vector<map<string, string>> toBuildList;

		Resources resources;
		Timer timer;
		JsonMaster jsonmaster(timer, resources);

		string productionStruct = pAction.getProductionStruct(unit);
		if (!pAction.preCheck(rawList)) {
			return false;
		}
		else toBuildList = pAction.getDetailedBuildList();

		BuildedList buildedList;
		Checker checker(timer, resources, buildedList, toBuildList);
		Builder builder(timer, resources, buildedList, toBuildList, productionStruct, unit, maxTime, json);

		char listLength = toBuildList.size();
		ScvManager scvManager(resources, toBuildList, buildedList, listLength);
		char i = 0;
		for (; timer.getCurrentTime() <= maxTime; timer.timeIncf())
		{
			resources.collectResources(buildedList.getScvList());
			builder.proceed();//build one second
			scvManager.manageScvs(i);//adjust the number of scvs in minerals and vespene
			if (!builder.chronoBoost()) {
				if (i < listLength) {
					if (checkAndBuild(i, checker, builder))
					{
						i++;
						//if (i == listLength) { cout << "the end of the build list" << endl; }
					}
				}
			}
			if (json) {
				if (builder.hasEvents() || scvManager.scvChanged())
				{
					size_t workersInMineral = buildedList.workersInMineral();
					size_t workersInVespene = buildedList.workersInVespene();
					jsonmaster.statusMaster(workersInMineral, workersInVespene);
					if (builder.hasEvents())
					{
						vector<map<string, const char*>>& events = builder.getEvents();
						jsonmaster.eventMaster(events);
						builder.cleanEvents();
					}
				}
			}
			if (!builder.hasEvents() && builder.proceedListEmpty() && i == listLength)
			{
				break;
			}
		}
		if (!builder.proceedListEmpty() || i < listLength) {
			builder.deleteProceedList();
			return false;
		}
		if (json) jsonmaster.jsonPWriter();
		return true;
	}
	tuple<char, char, char, char> ForwardSim() {
		return make_tuple(1, 1, 1, 1);
	}
private:
	string unit;
	int maxTime;
	char unitNumber = 100;
};
