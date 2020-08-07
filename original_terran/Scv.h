#pragma once
#include <string>
#define MINERALS "minerals"
#define VESPENE "vespene"
#define CONSTRUCT "construct"
#define IDLE "idle"
#define BUSY "busy"
using namespace std;

class Scv {
public:
	Scv(string n, string s):name(n), status(s) {}
	string getName() { return name; }
	string getStatus() { return status; }
	void goMineral() { status = MINERALS; }
	void goVespene() { status = VESPENE; }
	void setStatus() { status = BUSY; }


private:
	string name;
	string status;
	
	//int wMinerals;
	//int wVespene;
};

class Medivac {
public:
	Medivac(string n, string s):name(n), status(s) , energy(50), maxEnergy(200){}
	string getName() { return name; }
	string getStatus() { return status; }
	
	bool skillLaunchable() { if (energy >= 50)return true; else { return false; } }
	void energyRecovery() { 
		if ((maxEnergy - energy) >= 0.5625)energy += 0.5625f;
		else energy = maxEnergy;
	}
	
private:
	string name;
	string status;
	float energy;
	float maxEnergy;
};


class Ghost {
public:
	Ghost(string n, string s):name(n), status(s) , energy(75), maxEnergy(200){}
	string getName() { return name; }
	string getStatus() { return status; }
	
	bool skillLaunchable() { if (energy >= 75)return true; else { return false; } }
	void energyRecovery() { 
		if ((maxEnergy - energy) >= 0.5625)energy += 0.5625f;
		else energy = maxEnergy;
	}
	
private:
	string name;
	string status;
	float energy;
	float maxEnergy;
};


class Banshee {
public:
	Banshee(string n, string s):name(n), status(s) , energy(50), maxEnergy(200){}
	string getName() { return name; }
	string getStatus() { return status; }
	
	bool skillLaunchable() { if (energy >= 50)return true; else { return false; } }
	void energyRecovery() { 
		if ((maxEnergy - energy) >= 0.5625)energy += 0.5625f;
		else energy = maxEnergy;
	}
	
private:
	string name;
	string status;
	float energy;
	float maxEnergy;
};


class Raven {
public:
	Raven(string n, string s):name(n), status(s) , energy(50), maxEnergy(200){}
	string getName() { return name; }
	string getStatus() { return status; }
	
	bool skillLaunchable() { if (energy >= 50)return true; else { return false; } }
	void energyRecovery() { 
		if ((maxEnergy - energy) >= 0.5625)energy += 0.5625f;
		else energy = maxEnergy;
	}
	
private:
	string name;
	string status;
	float energy;
	float maxEnergy;
};










