#pragma once
#include "BuildedList.h"
#include "Timer.h"
#include "Resources.h"
#include "Buildings.h"
#include "Scv.h"
#include <map>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm> 

using namespace std;



class proceedManager {
public:
	proceedManager(building* p, string& pderID,string& pdID, string& pN, float& bT, BuildedList* bdl, int& sp) : producedID(pdID),producerID(pderID), producedName(pN), buildTime(bT), startTime(0), buildedList(bdl), supplyProvided(sp), scv("scv1") {
		if (p != NULL) producer = p;
		else producer = NULL;
	}
	bool proceedOneSec() {
		if (producer != NULL)
		{
			startTime = startTime + producer->getSpeed();
		}
		else {
			startTime++;
		}
		//cout<<"startTime is:"<<startTime<<endl;
		//cout<<"buildTIme is:"<<buildTime<<endl;
		if (startTime >= buildTime)
		{
			if (producer != NULL)
			{
				
			}
			else
			{
				//cout<<"produced by SCV_________________---------------------------:" <<producer<<endl;
				if (producedName == "SCV")
				{
				//Scv?
					buildedList->getScvList().push_back(Scv(producedID, MINERALS));
					vector<commandCenter>& c = buildedList->getCommandCenterList();
					for (commandCenter &co : c)
					{	//cout<<"in checker and in availcheck! the commandcenter status is:"<<co.getStatus()<<endl;
						if (co.getName() == producerID) co.idle();
					}
				}
			
				else if (producedName == "CommandCenter")
				{
					buildedList->getCommandCenterList().push_back(commandCenter(producedID));
				}
				 else if (producedName == "OrbitalCommand")
				{
					buildedList->getOrbitalCmdList().push_back(orbitalCommand(producedID));
				}
				else if (producedName == "PlanetaryFortress")
				{
					buildedList->getPlanetartForList().push_back(planetaryFortress(producedID));
				}

				else if (producedName == "EngineeringBay")
				{
					buildedList->addEngBay();
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}
				else if (producedName == "MissileTurret")
				{
					buildedList->addMissile();
					//buildedList->getGatewayList().push_back(gateway(producedID));
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}
				else if (producedName == "SensorTower")
				{
					buildedList->addSensor();
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}
				else if (producedName == "SupplyDepot")
				{
					buildedList -> addDepot();
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}

					//buildedList->getRobfacList().push_back(robotics_facility(producedID));
				}
				else if (producedName == "Refinery")
				{
					buildedList->addRefinery();
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}

				}
				else if (producedName == "Barracks")
				{
					buildedList->getBarracksList().push_back(barracks(producedID));
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
					//cout<<"XXXXXXXXXXXXXXXXXXX"<<buildedList->getBarracksList().size()<<endl;
				}
				else if (producedName == "BarracksTechLab")
				{
					buildedList->getTechLabOnBarracksList().push_back(techLabOnBarracks(producedID));
				}
				else if (producedName == "Marine")
				{
					vector<barracks>& b = buildedList->getBarracksList();
					for (barracks &ba : b) {
						if (ba.getName() == producerID) {ba.idle();}
					}
				}
				else if (producedName == "HellionTank")
				{
					vector<factory>& f = buildedList->getFactoryList();
					for (factory &fa : f) {
						if (fa.getName() == producerID)  fa.idle();
					}
				}
				else if (producedName == "BarracksReactor")
				{
					buildedList->addReactorOnBarracks();
				}
				else if (producedName == "Factory")
				{
					buildedList->getFactoryList().push_back(factory(producedID));
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}
				else if (producedName == "FactoryTechLab")
				{
					buildedList->getTechlabOnfactoryList().push_back(techLabOnFactory(producedID));
				}
				else if (producedName == "FactoryReactor") {
					buildedList->addReactorOnFactory();
				}
				else if (producedName == "Armory") {
					buildedList->addArmory();
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}
				else if (producedName == "Starport") {
					buildedList->getStarportList().push_back(starport(producedID));
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}
				else if (producedName == "StarportTechLab") {
					//cout<<"int prosecond the StarporTechLab will be builded :"<<endl;
					buildedList->getTechLabOnStarportList().push_back(techLabOnStarport(producedID));
				}
				else if (producedName == "StarportReactor") {
					buildedList->addReactorOnStarport();
				}
				else if (producedName == "FusionCore") {
					buildedList->addFusionCore();
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}
				else if (producedName == "Bunker") {
					buildedList->addBunker();
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}
				else if (producedName == "GhostAcademy")
				{
					buildedList->addGhostAc();
					for(Scv& scv : buildedList->getScvList())
					{
					    if(scv.getName() == producerID)
					    {
					        scv.goMineral();
					    }
					}
				}//cout<<"now "<<producedName<<" is produced!"<<endl;
			}
			
			return true;
		}
		else return false;
	}
	string& getProducedID() { return producedID; }
	string& getProducedName() { return producedName; }
	string& getProducerID() {
		if (producer == NULL)
		{
			return producerID;
		}
		else return producer->getName();
	}
	int& getSupplyProvided() { return supplyProvided; }
	float getRemainTime() { return (buildTime - startTime); }
	building* getProducer() { return producer; }
private:
	building* producer;
	string producerID;
	string producedID;
	string producedName;
	float buildTime;
	float startTime;
	BuildedList* buildedList;
	int supplyProvided;
	string scv;
};



class ChronoBoost {
public:
	ChronoBoost(Resources* b) : _resources(b), timeRemain(64), timeUp(false) {}
	bool passOneSec() {
		timeRemain--;
		if (timeRemain == 1) 
		timeUp = true;
		return timeUp;
	}
	//void boostEnd() { }
	bool checktimeUp() { return timeUp; }
private:
	Resources* _resources;
	int timeRemain;
	bool timeUp;
};





class Builder {
public:
	Builder(Timer* t, Resources* r, BuildedList* b, vector<map<string, string>> tbl) :timer(t), resources(r), toBuildList(tbl), buildedList(b) {}
	void build(int i,string& s) {
		map<string, string> item = toBuildList[i];
		string& name = item["name"];
		string producedBy = item["produced_by"];
		string producedID = "";
		string producerID = s;
		building* IDLEBuilding;


		float build_time = stof(item["build_time"]);
		int supplyProvided = stoi(item["supply_provided"]);
		//cout<<"now build name is:"<<name<<endl;
		if (producedBy == "SCV" )
		{
			if (name == "CommandCenter")
			{
				producedID = "commandCenter";
				producedID += ('0' + buildedList->buildCmdCenter());
			}
			/*else if (name == "OrbitalCommand")
			{
				producedID = "orbitalCommand";
				producedID += ('0' + buildedList->buildOrbitalCmd());
			}
			else if (name == "PlanetaryFortress")
			{
				producedID = "planetartFortress";
				producedID += ('0' + buildedList->buildPlanetaryFor());
			}*/
			else if (name == "EngineeringBay")
			{
				producedID = "EngineeringBay";
				producedID += ('0' + buildedList->buildEnBay());
			}
			else if (name == "MissleTurret")
			{
				producedID = "MissleTurret";
				producedID += ('0' + buildedList->buildMissile());
			}
			else if (name == "SensorTower")
			{
				producedID = "SensorTower";
				producedID += ('0' + buildedList->buildSensor());
			}
			else if (name == "SupplyDepot")
			{
				producedID = "SupplyDepot";
				producedID += ('0' + buildedList->buildDepot());
			}
			else if (name == "Refinery")
			{
				producedID = "Refinery";
				producedID += ('0' + buildedList->buildRefinery());
			}
			else if (name == "Barracks")
			{
				producedID = "Barracks";
				producedID += ('0' + buildedList->buildBarracks());
			}
			/*else if (name == "BarracksTechLab")
			{
				producedID = "BarracksTechLab";
				producedID += ('0' + buildedList->buildTwiCon());
			}
			else if (name == "BarracksReactor")
			{
				producedID = "BarracksReactor";
				producedID += ('0' + buildedList->buildTemArch());
			}*/
			else if (name == "Factory")
			{
				producedID = "Factory";
				producedID += ('0' + buildedList->buildFactorys());
			}
			/*else if (name == "FactoryTechLab")
			{
				producedID = "FactoryTechLab";
				producedID += ('0' + buildedList->buildFleetBeacon());
			}
			else if (name == "FactoryReactor")
			{
				producedID = "FactoryReactor";
				producedID += ('0' + buildedList->buildAssimilator());
			}*/
			else if (name == "Armory")
			{
				producedID = "Armory";
				producedID += ('0' + buildedList->buildArmory());
			}
			else if (name == "Starport")
			{
				producedID = "Starport";
				producedID += ('0' + buildedList->buildStarport());
			}
			/*else if (name == "StarporTechLab")
			{
				producedID = "StarporTechLab";
				producedID += ('0' + buildedList->buildPhotonCannon());
			}
			else if (name == "StarportReactor")
			{
				producedID = "StarportReactor";
				producedID += ('0' + buildedList->buildPhotonCannon());
			}*/
			else if (name == "FusionCore")
			{
				producedID = "FusionCore";
				producedID += ('0' + buildedList->buildFusion());
			}
			else if (name == "Bunker")
			{
				producedID = "Bunker";
				producedID += ('0' + buildedList->buildBunker());
			}
			else if (name == "GhostAcademy")
			{
				producedID = "GhostAcademy";
				producedID += ('0' + buildedList->buildGhostAc());
			}
			
				IDLEBuilding = NULL;
				//IDLEBuilding->setStatus();
				//inScv ->setStatus() ;
				proceedManager pM(IDLEBuilding,producerID, producedID, name, build_time, buildedList, supplyProvided);
				proceedList.push_back(pM);

		}
		else if(producedBy == "CommandCenter/OrbitalCommand/PlanetaryFortress")
		{
			
			
			if(name == "PlaneetaryFortress")
			{
				producedID = "planetartFortress";
				producedID += ('0' + buildedList->buildPlanetaryFor());
			}
			if(name == "SCV")
			{
				producedID = "scv_";
				producedID += (to_string( buildedList->buildScv()));
			}
			for (commandCenter& n : buildedList->getCommandCenterList())
			{
				if (n.getStatus() == IDLE)
				{
					IDLEBuilding = NULL;
					n.constructing();
					proceedManager pM(IDLEBuilding, producerID,producedID, name, build_time, buildedList, supplyProvided);
					proceedList.push_back(pM);
					break;
				}
			}
						
			
			
		}
		else if(producedBy == "CommandCenter")
		{
			
			//cout<<"in build and orbitalVCommand1"<<endl;
			if(name == "OrbitalCommand")
			{//cout<<"in build and orbitalVCommand1"<<endl;
				producedID = "orbitalCommand";
				producedID += ('0' + buildedList->buildOrbitalCmd());
			}
			
			if(name == "PlaneetaryFortress")
			{
				producedID = "planetartFortress";
				producedID += ('0' + buildedList->buildPlanetaryFor());
			}
			
			for (commandCenter& n : buildedList->getCommandCenterList())
			{
				if (n.getStatus() == IDLE)
				{
					IDLEBuilding = NULL;
					n.constructing();
					proceedManager pM(IDLEBuilding, producerID,producedID, name, build_time, buildedList, supplyProvided);
					proceedList.push_back(pM);
					break;
				}
			}
						
			
			
		}
		else if((producedBy == "Barracks") || (producedBy == "Barracks/BarracksTechLab/BarracksReactor"))
		{
			
			if(name == "BarracksTechLab")
			{
				producedID = "BarracksTechLab";
				producedID += ('0' + buildedList->buildTechLabOnBarracks());
			}
			
			else if (name == "BarracksReactor")
			{
			
				producedID = "BarracksReactor";
				producedID += ('0' + buildedList->buildReactorOnBarracks());
			
			}
			else if (name == "Marine")
			{
			
				producedID = "Marine";
				producedID += ('0' + buildedList->buildMarine());
			
			}
			for (barracks& n : buildedList->getBarracksList())
			{
			//cout<<"find if there are idle barracks!!"<<endl;
				if (n.getStatus() == IDLE)
				{
					//cout<<"jin ru barracks check"<<endl;
					IDLEBuilding = NULL;
					n.constructing();
					proceedManager pM(IDLEBuilding, producerID,producedID, name, build_time, buildedList, supplyProvided);
					proceedList.push_back(pM);
					break;
				}
			}
			
			
			
			
			/*for (barracksRector& n : buildedList->getBarracksList())
			{*/
			//cout<<"find if there are idle barracks!!"<<endl;
				/*if (buildedList->hasReactorOnBarracks())
				{
					//cout<<"jin ru barracks... check"<<endl;
					IDLEBuilding = NULL;
					//n.constructing();
					proceedManager pM(IDLEBuilding,producerID, producedID, name, build_time, buildedList, supplyProvided);
					proceedList.push_back(pM);
					//break;
				}*/
			//}*/
			//cout<<"producer is barracks in build!!!"<<endl;			

		}

		else if(producedBy == "Factory" || producedBy == "Factory/FactoryTechLab/FactoryReactor" )
		{
			if(name == "FactoryReactor")
			{
				producedID = "FactoryReactor";
				producedID += ('0' + buildedList->buildReactorOnFactorys());
			}
			
			if (name =="FactoryTechLab"){
				producedID = "FactoryTechLab";
				producedID += ('0' + buildedList->buildTechLabOnFactorys());
			}
			for (factory& n : buildedList->getFactoryList())
			{
				if (n.getStatus() == IDLE)
				{
					IDLEBuilding = NULL;
					n.constructing();
					proceedManager pM(IDLEBuilding, producerID,producedID, name, build_time, buildedList, supplyProvided);
					proceedList.push_back(pM);
					break;
				}
			}


			
		}
		else if (producedBy == "Starport" || producedBy == "Starport/StarportTechLab/StarportReactor"){
			if(name == "StarportReactor")
			{
				producedID = "StarportReactor";
				producedID += ('0' + buildedList->buildReactorOnStarport());
			}
			
			if(name == "StarportTechLab")
			{
				producedID = "StarportTechLab";
				producedID += ('0' + buildedList->buildTechLabOnStarport());
			}


			for (starport& n : buildedList->getStarportList())
			{
				if (n.getStatus() == IDLE)
				{
					IDLEBuilding = NULL;
					n.constructing();
					proceedManager pM(IDLEBuilding,producerID, producedID, name, build_time, buildedList, supplyProvided);
					proceedList.push_back(pM);
					break;
				}
			}


		}else if (producedBy == "StarportTechLab"){
			if(name == "Battlecruiser")
			{
				producedID = "Battlecruiser";
				producedID += ('0' + buildedList->buildBattlecruiser());
			}
			

			for (techLabOnStarport& n : buildedList->getTechLabOnStarportList())
			{
				if (n.getStatus() == IDLE)
				{
					IDLEBuilding = NULL;
					n.constructing();
					proceedManager pM(IDLEBuilding,producerID, producedID, name, build_time, buildedList, supplyProvided);
					proceedList.push_back(pM);
					break;
				}
			}


		}
		
		
		
		
		
        /*else if(producedBy == "FactoryTechLab")
		{
			if(name == "FactoryReactor")
			{
				producedID = "FactoryReactor";
				producedID += ('0' + buildedList->buildReactorOnFactorys())
			}
			/*if(name == "WidowMine")  && cyclone liberator
			{
				producedID = "FactoryReactor";
				producedID += ('0' + buildedList->buildTechLabOnFactorys())
			}
			if (name =="FactoryTechLab"){
				producedID = "FactoryTechLab";
				producedID += ('0' + buildedList->buildTechLabOnFactorys())
			}
			for (factory& n : buildedList->getFactoryList())
			{
				if (n.getStatus() == IDLE)
				{
					IDLEBuilding = &n;
					IDLEBuilding->constructing();
					proceedManager pM(IDLEBuilding, producedID, name, build_time, buildedList, supplyProvided);
					proceedList.push_back(pM);
					break;
				}
			}



		}*/
		//cout<<"build end!"<<endl;
		//if (IDLEBuilding == NULL) { string scv = "init_scv_01"; buildStartEvent(name, scv); }
		//else {
			//cout<<"build end0!"<<endl;
			//string& buildingID = IDLEBuilding->getName();cout<<"build end!1"<<endl;
			//form build-start event
			buildStartEvent(name, producerID);
			//cout<<"build end!2"<<endl;
		//}

		int minerals = stoi(item["minerals"]);
		int vespene = stoi(item["vespene"]);
		int supply_cost = stoi(item["supply_cost"]);
		resources->subMinerals(minerals);
		resources->subVespene(vespene);
		resources->addSuppluUsed(supply_cost);
		//cout<<"build end!"<<endl;
	}



	bool hasEvents() {
		if (events.size() > 0) return true;
		else return false;
	}
	void cleanEvents() { vector<map<string, const char* >>().swap(events); }

	void buildStartEvent(string& name, string& producerID) {
		map<string, const char*> event_;
		const char *s = "build-start";
		
		event_.insert(pair<string, const char*>("type", s));
		c = new char[20];
		strcpy(c, name.c_str());
		event_.insert(pair<string, const char*>("name", c));

		c = new char[20];
		strcpy(c, producerID.c_str());
		event_.insert(pair<string,const char*>("producerID", c));

		events.push_back(event_);
	}
	void buildEndEvent(string& name, string& producerID, string& producedIDs) {
		map<string, const char*> event;
		const char *s = "build-end";
		event.insert(pair<string, const char*>("type", s));

		c = new char[20];
		strcpy(c, name.c_str());
		event.insert(pair<string, const char*>("name", c));

		c = new char[20];
		strcpy(c, producerID.c_str());
		event.insert(pair<string, const char*>("producerID", c));

		c = new char[20];
		strcpy(c, producedIDs.c_str());
		event.insert(pair<string, const char*>("producedIDs", c));
		//event.insert(pair<string, const char*>("producedIDs", c));
		events.push_back(event);
	}
	void specialEvent(string& triggeredBy, string& targetBuilding) {
		map<string, const char*> event_;
		const char *s = "special";
		const char *s1 = "mule";
		event_.insert(pair<string, const char*>("type", s));
		event_.insert(pair<string, const char*>("name", s1));

		c = new char[20];
		strcpy(c, triggeredBy.c_str());
		event_.insert(pair<string, const char*>("triggeredBy", c));
		c = new char[20];
		strcpy(c, targetBuilding.c_str());
		event_.insert(pair<string, const char*>("targetBuilding", c));
		events.push_back(event_);
	}
	bool chronoBoost() {
		cleanBoostList();
		for (ChronoBoost& cB : boostList)cB.passOneSec();
		//Resources* toboost;
		bool hasSuchBuilding = false;
		for (orbitalCommand& n : buildedList->getOrbitalCmdList()) {
			n.energyRecovery();
			//n.outPower();
			if (n.skillLaunchable())
			{
				int remainTime = 0;
				/*for (proceedManager pM : proceedList) {
					if ((pM.getProducer() != NULL) && (pM.getRemainTime() > remainTime)) {
						if (pM.getProducer()->getSpeed() != 1.5)
						{
							hasSuchBuilding = true;
							remainTime = pM.getRemainTime();
							//toboost = pM.getProducer();
						}
					}
				}*/
				int lowerBound = min(64, (int)(1000 - timer->getCurrentTime()));
				if ((remainTime >= lowerBound) )
				{
					n.launchMule();
					resources->mule();
					string s = "Mule";
					specialEvent(n.getName(), s);
					boostList.push_back(ChronoBoost(resources));
					return true;
				}
				else return false;
			}
			else return false;
		}
		return false;
	}
	void cleanBoostList() {
		for (auto i = boostList.begin(); i != boostList.end(); ++i) {
			if ((*i).checktimeUp())
			{
				//(*i).boostEnd();
				boostList.erase(i);
				cleanBoostList();
				break;
			}
		}
	}

	vector<map<string, const char*>>& getEvents() { return events; }
	void proceed() {
		vector<string> producedIDs;
		if (!proceedList.empty()) {
			for (proceedManager& pM : proceedList) {
				if (pM.proceedOneSec())
				{
				    //for(proceedList.begin(); proceedList.end();)
					resources->addSupply(pM.getSupplyProvided());
					buildEndEvent(pM.getProducedName(), pM.getProducerID(), pM.getProducedID());
					producedIDs.push_back(pM.getProducedID());
				}
			}
		}
		if (!producedIDs.empty())
		{
			for (string& ID : producedIDs) {
				for (vector<proceedManager>::iterator iter = proceedList.begin(); iter != proceedList.end(); ++iter) {
					if ((*iter).getProducedID() == ID)
					{
						proceedList.erase(iter);
						break;
					}
				}
			}
		}
	}
	bool proceedListEmpty() {
		return proceedList.empty();
	}
	vector<proceedManager>& getproceedList() {
		return proceedList;
	}
	void deleteProceedList() {
		delete &proceedList;
	}
private:
	BuildedList* buildedList;
	Timer* timer;
	Resources* resources;
	vector<map<string, string>> toBuildList;
	vector<map<string, const char*>> events;
	building* buildingPtr;
	vector<proceedManager> proceedList;
	char* c;
	vector<ChronoBoost> boostList;
};
