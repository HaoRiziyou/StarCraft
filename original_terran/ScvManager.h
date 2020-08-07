#pragma once
#include "Resources.h"
#include "BuildedList.h"
#include "Scv.h"
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
class ScvManager {
public:
	ScvManager(Resources* r, vector<map<string, string>>& tbl, BuildedList* bdl, int& lL) : resources(r), toBuildList(tbl), buildedList(bdl), mNeed(0), vNeed(0), listLength(lL), scvInM(12), scvInV(0), scvDisChanged(false), scvCounter(0) {}
	void manageScvs(int& tb) {
		tobuild = tb;
		int SIM = 0;
		int SIV = 0;
		if (tobuild < listLength) {
			if (buildedList->hasRefinery())
			{
				scvInM = 0;
				scvInV = 0;
				for (Scv p : buildedList->getScvList()) {
					if (p.getStatus() == VESPENE) scvInV++;
					else scvInM++;
				}
				int refinery = buildedList->getRefinery();
				int maxSCVInRefinery = refinery * 3;
				double minerals = resources->getMinerals();
				float vespene = resources->getVespene();
				mNeed += stof(toBuildList[tobuild]["minerals"]);
				vNeed += stof(toBuildList[tobuild]["vespene"]);
				if ((minerals >= mNeed) || (vespene >= vNeed))
				{


					if (tobuild < listLength - 1)
					{
						int next = tobuild + 1;
						manageScvs(next);
					}
					else if (vespene < vNeed)
					{
						scvCounter = 0;
						for (Scv& scv : buildedList->getScvList()) {
						    if(scv.getStatus() != "busy")
						    {
							    if (scvCounter < maxSCVInRefinery) {
								    scv.goVespene();
								    scvCounter = scvCounter + 1;
							    }
							    else { scv.goMineral(); }
							}
						}
						if (maxSCVInRefinery != scvInV)
						{
							scvDisChanged = true;
						}
						else scvDisChanged = false;
					}
					else if (minerals < mNeed)
					{
						SIM = 0;
						for (Scv& scv : buildedList->getScvList()) {
						    if(scv.getStatus() != "busy"){
							    scv.goMineral();
							    SIM++;
							}
						}
						if (SIM != scvInM) {
							scvDisChanged = true;
						}
						else scvDisChanged = false;
					}
				}
				else
				{


					int scvNumber = buildedList->getScvList().size();
					double mTime = 0;
					double vTime = 0;
					int scvInVespene = 1;
					int time = 0;
					for (int i = 1; i <= maxSCVInRefinery; i++)
					{
						vTime = (vNeed - vespene) / (i*0.63);
						mTime = (mNeed - minerals) / ((scvNumber - i)*0.7);
						int maxTime = max(vTime, mTime);
						if (time == 0) { time = maxTime; }
						else {
							if (time > maxTime) {
								time = maxTime; scvInVespene = i;
							}
						}
					}

					scvCounter = 0;
					for (Scv& scv : buildedList->getScvList()) {
					  if(scv.getStatus() != "busy"){
						if (scvCounter < scvInVespene)
						{

							scv.goVespene();
							scvCounter++;

						}
						else scv.goMineral();
						}
					}
					if (scvInVespene != scvInV)
					{
						scvDisChanged = true;
					}
					else scvDisChanged = false;
				}
			}
			mNeed = 0;
			vNeed = 0;
		}
		else scvDisChanged = false;
	}
	bool scvChanged() { return scvDisChanged; }
private:
	vector<Scv> SCVs;
	Resources* resources;
	vector<map<string, string>> toBuildList;
	BuildedList* buildedList;
	int tobuild;
	double mNeed;
	float vNeed;
	int listLength;
	bool scvDisChanged;
	int scvInM;
	int scvInV;
	int scvCounter;
};
