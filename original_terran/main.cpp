#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

bool checkAndBuild(int i, Checker& checker, Builder& builder) {
	string s = checker.CheckMaster(i);
	if (s!=BUSY)
	{
		//cout << "check complete" << endl;
		builder.build(i,s);
		//cout << "check complete" << endl;
		return true;
	}
	else return false;
}


int main(int argc, char*argv[]) {
	string titles[] = { "name", "minerals", "vespene", "build_time", "supply_cost", "supply_provided", "start_energy", "max_energy", "race", "produced_by", "dependency" };

	PreAction pAction;
	vector<map<string, string>> toBuildList;
	string techTree;

	if (argc == 3)
	{
		//cout << "Usage:" << argv[0] << "SOURCE DESTINATION" << endl;
		//cout << "The argument is: " << argv[1] << " " << argv[2] << endl;
		string race = argv[1];
		//check race
		if (race == "terran") {
			techTree = "terran.csv";
			vector<string> rawList = pAction.readList(argv[2]);
			Resources resources;
			Timer timer;
			
			JsonMaster jsonmaster(&timer, &resources);
		

			if (!pAction.preCheck(rawList, techTree)) {
				jsonmaster.invalid();
				jsonmaster.jsonPWriter();
				return 0;
			}
			else toBuildList = pAction.getDetailedBuildList();
			//cout<<"Main function******************"<<endl;
			BuildedList buildedList;
			Checker checker(&timer, &resources, &buildedList, toBuildList);
			Builder builder(&timer, &resources, &buildedList, toBuildList);
			//cout<<"Main function******************"<<endl;
			int listLength = toBuildList.size();
			ScvManager scvManager(&resources, toBuildList, &buildedList, listLength);
			int maxTime = 500;
			int i = 0;
			
			for (; timer.getCurrentTime() <= maxTime; timer.timeIncf())
			{
				resources.collectResources(buildedList.getScvList());
				builder.proceed();//build one second
				scvManager.manageScvs(i);//adjust the number of probes in minerals and vespene
					//cout<<"Main function******************"<<endl;
				if (!builder.chronoBoost()) {
					
					if (i < listLength) {

						if (checkAndBuild(i, checker, builder))
						{
							//cout<<"into mule<<" <<endl;
							i++;
							//if (i == listLength) { cout << "the end of the build list" << endl; }
						}
					}
				}
				
				if (builder.hasEvents() || scvManager.scvChanged())
				{
					int workersInMineral = buildedList.workersInMineral();
					int workersInVespene = buildedList.workersInVespene();
					jsonmaster.statusMaster(workersInMineral, workersInVespene);
					if (builder.hasEvents())
					{
						vector<map<string, const char*>>& events = builder.getEvents();
						jsonmaster.eventMaster(events);
						builder.cleanEvents();
					}
				}
			}//cout<<"Main function******************"<<endl;
			if (!builder.proceedListEmpty() || i < listLength) {
				//cout << "Time exceed!" << endl;
				jsonmaster.invalid();
				builder.deleteProceedList();
				//delete &builder;
				//delete &checker;

			}
			//cout<<"Main function******************"<<endl;
			jsonmaster.jsonPWriter();
		}
		else {
			//cout << "This is the simulation for sc2-hots-protoss! Plz input the corrent race name." << endl;
			return 0;
		}
	}
	else {
		//cout << "The argument input is incorrect." << endl;
		return 0;
	}
	return 0;
}

