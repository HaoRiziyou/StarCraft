#pragma once
#include <vector>
#include "Scv.h"
#include "Buildings.h"
#define MINERALS "minerals"
#define VESPENE "vespene"
#define CONSTRUCT "construct"
#define IDLE "idle"
class BuildedList {
public:
	BuildedList() :scv(0), marine(0), siegeTank(0), thor(0), hellion(0), medivac(0), viking(0), raven(0), banshee(0), battlecruiser(0), marauder(0), reaper(0), ghost(0), orbitalCmd(0), planetaryFor(0), engineeringBay(0), engineeringBayName(0), missileTurret(0), missileTurretName(0), sensorTower(0), sensorTowerName(0), depot(0), depotName(0), refinery(0), refineryName(0), barracks_(0), techLabOnBarracks_(0), reactorOnBarracks(0), reactorOnBarracksName(0), factory_(0), techLabOnFactory_(0), reactorOnFactory(0), reactorOnFactoryName(0),armory(0), armoryName(0),starport_(0),techLabOnStarPort_(0),reactorOnStarport(0),reactorOnStarportName(0),fusionCore(0),fusionCoreName(0),bunker(0),bunkerName(0),ghostAcademy(0),ghostAcademyName(0){
		for (int i = 1; i <= 12; ++i) {
			Scv scv0("init_scv_" + to_string(i), MINERALS);
			scvList.push_back(scv0);
			scv++;
		}
		commandCenter cmdCenter ("init_command_center");
		commandCneterList.push_back(cmdCenter);
	}
	int workersInMineral() {
		int i = 0;
		for(Scv scv: scvList)
		{
			if (scv.getStatus() == MINERALS) ++i;
		}
		return i;
	}
	int workersInVespene() {
		int i = 0;
		for (Scv scv : scvList)
		{
			if (scv.getStatus() == VESPENE) ++i;
		}
		return i;
	}

	vector<Scv>& getScvList() { return scvList; }
	int buildScv() { scv++; return scv; }
	int buildMarine() { marine++; return marine; }
	int buildSiegeTank() { siegeTank++; return siegeTank; }
	int buildThor() { thor++; return thor; }
	int buildHellion() { hellion++; return hellion; }
	int buildMedivac() { medivac++; return medivac; }
	int buildViking() { viking++; return viking; }
	int buildRaven() { raven++; return raven; }
	int buildBanshee() { banshee++; return banshee; }
	int buildBattlecruiser() { battlecruiser++; return battlecruiser; }
	int buildMarauder() { marauder++; return marauder; }
	int buildReaper() { reaper++; return reaper; }
	int buildGhost() { ghost++; return ghost; }
	

	int buildCmdCenter() { cmdCenter++; return cmdCenter; }
	int buildOrbitalCmd() { orbitalCmd++; return orbitalCmd; }
	int buildPlanetaryFor() { planetaryFor++; return planetaryFor; }
	int buildEnBay() { engineeringBayName++; return engineeringBayName; }
	int buildMissile() { missileTurretName++; return missileTurretName; }
	int buildSensor() { sensorTowerName++; return sensorTowerName; }
	int buildDepot() { depotName++; return depotName; }
	int buildRefinery() { refineryName++; return refineryName; }
	
	int buildBarracks() { barracks_++; return barracks_; }
	int buildTechLabOnBarracks() { techLabOnBarracks_++; return techLabOnBarracks_; }
	int buildReactorOnBarracks() { reactorOnBarracksName++; return reactorOnBarracksName; }

	int buildFactorys() { factory_++; return factory_; }
	int buildTechLabOnFactorys() { techLabOnFactory_++; return techLabOnFactory_; }
	int buildReactorOnFactorys() { reactorOnFactoryName++; return reactorOnFactoryName; }

	int buildStarport() { starport_++; return starport_; }
	int buildTechLabOnStarport() { techLabOnStarPort_++; return techLabOnStarPort_; }
	int buildReactorOnStarport() { reactorOnStarportName++; return reactorOnStarportName; }

	int buildArmory() { armoryName++; return armoryName; }
	int buildFusion() { fusionCoreName++; return fusionCoreName; }
	int buildBunker() { bunkerName++; return bunkerName; }
	int buildGhostAc() { ghostAcademyName++; return ghostAcademyName; }

	void addDepot() { depot++; }
	void addEngBay() { engineeringBay++; }
	void addMissile() { missileTurret++; }
	void addSensor() { sensorTower++; }
	void addReactorOnBarracks() { reactorOnBarracks++; }
	void addReactorOnFactory() { reactorOnFactory++; }
	void addReactorOnStarport() { reactorOnStarport++; }
	void addRefinery() { refinery++; }
	int getRefinery(){return refinery;}
	void addBunker() { bunker++; }
	void addGhostAc() { ghostAcademy++; }
	void addArmory() { armory++; }
	void addFusionCore() { fusionCore++; }


	vector<commandCenter>& getCommandCenterList() { return commandCneterList; }
	vector<orbitalCommand>& getOrbitalCmdList() { return orbitalCmdList; }
	vector<planetaryFortress>& getPlanetartForList() { return planetaryFortressList; }
	vector<barracks>& getBarracksList() { return barracksList; }
	vector<techLabOnBarracks>& getTechLabOnBarracksList() { return techLabOnBarracksList; }
	vector<starport>& getStarportList() { return starportList; }
	vector<techLabOnStarport>& getTechLabOnStarportList() { return techLabOnStarportList; }
	vector<factory>& getFactoryList() { return factoryList; }
	vector<techLabOnFactory>& getTechlabOnfactoryList() { return techLabOnFactoryList; }

	bool hasEnBay() { if (engineeringBay > 0) return true; else return false; }
	bool hasMissile() { if(missileTurret > 0) return true; else return false; }
	bool hasSensor() { if(sensorTower > 0) return true; else return false;}
	bool hasDepot() { if (depot > 0) return true; else return false; }
	bool hasRefinery() { if(refinery > 0) return true; else return false;}
	//bool hasBarracks() { if(barracks_; return barracks_; }
	//bool hasTechLabOnBarracks() { techLabOnBarracks_++; return techLabOnBarracks_; }
	bool hasReactorOnBarracks() { if(reactorOnBarracks > 0) return true; else return false;}

	//bool hasFactory() { if(factory_ > 0)++; return factory_; }
	//bool hasTechLabOnFactorys() { techLabOnFactory_++; return techLabOnFactory_; }
	bool hasReactorOnFactory() { if(reactorOnFactory >  0) return true; else return false;}

	//bool hasstarport_() { starport_++; return starport_; }
	//bool hasTechLabOnStarport_() { techLabOnStarPort_++; return techLabOnStarPort_; }
	bool hasReactorOnStarport() { if(reactorOnStarport > 0) return true; else return false;}

	bool hasArmory() { if(armory > 0 ) return true; else return false;}
	bool hasFusion() { if(fusionCore > 0)return true; else return false;}
	bool hasBunker() { if (bunker > 0)  return true; else return false; }
	bool hasGhostAc() { if(ghostAcademy > 0) return true; else return false; }

private:
	vector<Scv> scvList;
	int scv;
	int marine;
	int siegeTank;
	int thor;
	int hellion;
	int medivac;
	int viking;
	int raven;
	int banshee;
    int battlecruiser;
    int marauder;
	int reaper;
	int ghost;


	int cmdCenter;
	vector<commandCenter> commandCneterList;


	int orbitalCmd;
	vector<orbitalCommand> orbitalCmdList;

	int planetaryFor;
	vector<planetaryFortress> planetaryFortressList;

	int engineeringBay;
	int engineeringBayName;

	int missileTurret;
	int missileTurretName;

	int sensorTower;
	int sensorTowerName;

    int depot;
	int depotName;

	int refinery;
    int refineryName;

	int barracks_;
	vector<barracks> barracksList;

	int techLabOnBarracks_;
	vector <techLabOnBarracks> techLabOnBarracksList;

    int reactorOnBarracks;
    int reactorOnBarracksName;


	int factory_;
	vector<factory>factoryList;

	int techLabOnFactory_;
	vector <techLabOnFactory> techLabOnFactoryList;

	int reactorOnFactory;
	int reactorOnFactoryName;

	int armory;
	int armoryName;

	int starport_;
	vector<starport> starportList;

	int techLabOnStarPort_;
	vector<techLabOnStarport> techLabOnStarportList;

	int reactorOnStarport;
	int reactorOnStarportName;

	int fusionCore;
	int fusionCoreName;

	int bunker;
	int bunkerName;


	int ghostAcademy;
	int ghostAcademyName;

	

};

