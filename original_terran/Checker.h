#pragma once
#include "Timer.h"
#include "Resources.h"
#include "BuildedList.h"
#include <vector>
#include <map>
#include <thread>
#include <iostream>
#include "Buildings.h"
#define IDLE "idle"
#define BUSY "busy"
#define MINERALS "minerals"
#define VESPENE "vespene"
#define CONSTRUCT "construct"
using namespace std;
class Checker {
public:
	Checker(Timer* t, Resources* r, BuildedList* b, vector<map<string, string>> tobulist) : timer(t), resources(r), buildedList(b), toBuildList(tobulist) {}
	string CheckMaster(int i) {
		map<string, string> item = toBuildList[i];
		string name = item["name"];
		//cout<<"now check  is :"<<i<<"name is:"<<name<<endl;
		int minerals = stoi(item["minerals"]);
		int vespene = stoi(item["vespene"]);
		int supply_cost = stoi(item["supply_cost"]);
		string produced_by = item["produced_by"];
		string dependency = item["dependency"];
		string type = item["type"];
		if (resourceSupplyCheck(minerals, vespene, supply_cost)) {
			//cout<<"Resourcescheck Pass" <<endl;
			if (dependencyCheck(dependency)) {
				//cout <<"dependecny check pass!"<<endl;
				//cout<<"in checker the producer is "<<produced_by<<endl;
				 return availCheck(produced_by);
			}
		}
		return BUSY;
	}
	bool resourceSupplyCheck(int minerals, int vespene, int supply_cost) {
		if ((resources->getMinerals() >= minerals) && (resources->getVespene() >= vespene) && ((resources->getSupply() - resources->getSupplyUsed()) >= supply_cost)) return true;
		else return false;
	}
	bool dependencyCheck(string d) {
		if (d == "") return true;
		else if (d == "FusionCore")return buildedList-> hasFusion();
		else if (d == "GhostAcademy") return buildedList->hasGhostAc();
		else if (d == "Armory") return buildedList-> hasArmory();
		else if (d == "Barracks/BarracksTechLab/BarracksReactor")return (!buildedList->getBarracksList().empty()||!buildedList->getTechLabOnBarracksList().empty()||buildedList->hasReactorOnBarracks());
		else if (d == "EnginneringBay") return buildedList->hasEnBay();
		else if (d == "CommandCenter/OrbitalCommand/PlanetaryFortress") return (!buildedList->getCommandCenterList().empty()||!buildedList->getOrbitalCmdList().empty()||!buildedList->getPlanetartForList().empty());
		else if (d == "SupplyDepot")return buildedList->hasDepot();
		else if (d == "Starport/StarportTechLab/StarportReactor") return (!buildedList->getStarportList().empty()||buildedList->hasReactorOnStarport()||!buildedList->getTechLabOnStarportList().empty());
		else if (d == "Factory/FactoryReactor/FactoryTechLab") return (!buildedList->getFactoryList().empty()||buildedList->hasReactorOnFactory()||!buildedList->getTechlabOnfactoryList().empty()) ;
		else return false;
	}
	string availCheck(string pb) {
		//cout<<" in ++++++++++++availCheck"<<endl;
		if (pb == "CommandCenter/OrbitalCommand/PlanetaryFortress") {
			vector<commandCenter>& c = buildedList->getCommandCenterList();
			for (commandCenter &co : c)
			{//cout<<"in checker and in availcheck! the commandcenter status is:"<<co.getStatus()<<endl;
				if (co.getStatus() == IDLE) return co.getName();
			}
			vector<orbitalCommand>& orb = buildedList->getOrbitalCmdList() ;
			for (orbitalCommand &o : orb)
			{
				if (o.getStatus() == IDLE) return o.getName();
			}
			vector<planetaryFortress>& p = buildedList->getPlanetartForList();
			for (planetaryFortress &pl : p)
			{
				if (pl.getStatus() == IDLE) return pl.getName();
			}
			return BUSY;
		}
		else if (pb == "Barracks/BarracksTechLab/BarracksReactor") {
			//string s ="BarracksReactor";
			vector<barracks>& b = buildedList->getBarracksList();
			for (barracks &ba : b) {
				if (ba.getStatus() == IDLE) return ba.getName();
			}
			vector<techLabOnBarracks>& t = buildedList->getTechLabOnBarracksList();
			for (techLabOnBarracks &te : t) {
				if (te.getStatus() == IDLE) return te.getName();
			}
			//if(buildedList->hasReactorOnBarracks())return s;
			return BUSY;
		}
		else if (pb == "StarportTechLab") {
			//cout<<"in checker enter StarportTechLab"<<endl;
			vector<techLabOnStarport>& t = buildedList->getTechLabOnStarportList();
			for (techLabOnStarport &te : t) {
				//cout<<te.getName()<<" and "<<te.getStatus()<<endl;
				if (te.getStatus() == IDLE) return te.getName();
			}
			return BUSY;
		}
		else if (pb == "BarracksTechLab") {
			vector<techLabOnBarracks>& t = buildedList->getTechLabOnBarracksList();
			for (techLabOnBarracks &te : t) {
				if (te.getStatus() == IDLE) return te.getName();
			}
			return BUSY;
		}
		else if (pb == "FactoryTechLab") {
			vector<techLabOnFactory>& t = buildedList->getTechlabOnfactoryList() ;
			for (techLabOnFactory &te : t) {
				if (te.getStatus() == IDLE) return te.getName();
			}
			return BUSY;
		}
		else if (pb == "Starport/StarportTechLab/StarportReactor") {
			vector<starport>& s = buildedList->getStarportList();
			for (starport &st : s) {
				if (st.getStatus() == IDLE) return st.getName();
			}
			vector<techLabOnStarport>& t = buildedList->getTechLabOnStarportList();
			for (techLabOnStarport &te : t) {
				if (te.getStatus() == IDLE) return te.getName();
			}
			return BUSY;
		}
		else if (pb == "Factory/FactoryTechLab/FactoryReactor") {
			vector<factory>& f = buildedList->getFactoryList();
			for (factory &fa : f) {
				if (fa.getStatus() == IDLE) return fa.getName();
			}
			vector<techLabOnFactory>& t = buildedList->getTechlabOnfactoryList() ;
			for (techLabOnFactory &te : t) {
				if (te.getStatus() == IDLE) return te.getName();
			}
			return BUSY;
		}
		else if (pb == "SCV") {
			//vector<Scv>&s = buildedList->getScvList() ;
			for (Scv &sc : buildedList->getScvList() ) {//cout<<sc.getName()<<endl;cout<<sc.getStatus()<<endl;
				if (sc.getStatus() == MINERALS) {//cout<<"there is scv which is idle!!"<<endl;
					sc.setStatus();
					return sc.getName();
					}
			}
			return BUSY;
		}
		else if (pb == "CommandCenter") {
			vector<commandCenter>& c = buildedList->getCommandCenterList();
			for (commandCenter &co : c)
			{
				if (co.getStatus() == IDLE) return co.getName();
			}
			return BUSY;
		}
		else if (pb == "Barracks") {
			//cout<<"check producer Barracks"<<endl;
			vector<barracks>& b = buildedList->getBarracksList();
			for (barracks &ba : b) {
				if (ba.getStatus() == IDLE) return ba.getName();
			}
			return BUSY;
		}
		else if (pb == "Factory") {
			vector<factory>& f = buildedList->getFactoryList();
			for (factory &fa : f) {
				if (fa.getStatus() == IDLE) return fa.getName();
			}
			return BUSY;
		}
		else if (pb == "Starport") {
			vector<starport>& s = buildedList->getStarportList();
			for (starport &st : s) {
				if (st.getStatus() == IDLE) return st.getName();
			}
			return BUSY;
		}
		
		else return BUSY;
	}
	vector<map<string, string>> getEvents() { return events; }
private:
	Timer* timer;
	Resources* resources;
	BuildedList* buildedList;
	vector<map<string, string>> toBuildList;
	vector<map<string, string>> events;
};
