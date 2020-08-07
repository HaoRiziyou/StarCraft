#pragma once
#include "Scv.h"
#include <string>
using namespace std;

class Resources {
public:
	Resources():minerals(50), vespene(0), supply_used(12), supply(15) {}
	void addMinerals(float amount) { minerals += amount; }
	void addVespene(float amount) { vespene += amount; }
	void addSuppluUsed(int amount) { supply_used += amount; }
	void addSupply(int amount) { supply += amount; }
	void subMinerals(float amount) { minerals -= amount; }
	void subVespene(float amount) { vespene -= amount; }
	void subSuppluUsed(int amount) { supply_used -= amount; }
	void subSupply(int amount) { supply -= amount; }
	double getMinerals() { return minerals; }
	float getVespene() { return vespene; }
	int getSupplyUsed() { return supply_used; }
	int getSupply() { return supply; }
	
	void mule() {ability = true; }
	void collectResources(vector<Scv>& scvList) {
		if(ability ){
			minerals += 0.7*3.8;
		}
		for (Scv scv : scvList) {
			string status = scv.getStatus();
			if (status == MINERALS) minerals = minerals + 0.7;
			else if (status == VESPENE) vespene += 0.63;
			
		}//cout<<"Minerals:" <<minerals<<endl;
			//cout<<"Vespene" <<vespene <<endl;
	}
private:
	bool ability = false;
	double minerals;
	float vespene;
	int supply_used;
	int supply;
};
