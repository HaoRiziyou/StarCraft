#pragma once
#include <string>
#include <iostream>
#define CONSTRUCT "construct"
#define IDLE "idle"
using namespace std;
class building {
public:
	virtual void constructing() = 0;
	virtual void idle() = 0;
	virtual string getStatus() = 0;
	virtual string& getName() = 0;
	virtual float& getSpeed() = 0;
	virtual void energyRecovery() = 0;
	//virtual void mule() = 0;
	//virtual void muleEnd() = 0;
protected:
	string name;
	string status;
	float buildSpeed;
	float energy;
};

class commandCenter: public building {
public:
	commandCenter(string n) :status(IDLE), name(n), buildSpeed(1.0f), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }

	void energyRecovery() { energy += 0.5625f; }
	
private:
	string name;
	string status;
	float buildSpeed;
	float energy;
	//float maxEnergy;
};
class engineeringBay :public building {
public:
	engineeringBay (string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }
	
private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};

/*class scv {
public:
	scv (string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	//float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }

private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};
*/



class orbitalCommand: public building {
public:
	orbitalCommand(string n) :status(IDLE), name(n), buildSpeed(1.0f), energy(50), maxEnergy(200) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { 
		if ((maxEnergy - energy) >= 0.5625)energy += 0.5625f;
		else energy = maxEnergy;
	}
	bool skillLaunchable() { if (energy >= 50)return true; else { return false; } }
	void launchMule() { energy -= 50; }
	//int outPower(){cout<<"Energy: " <<energy <<endl;}
	//void mule() { buildSpeed = 3.8f; }
	//void muleEnd() { buildSpeed = 1.0f; }
private:
	string name;
	string status;
	float buildSpeed;
	float energy;
	float maxEnergy;
};

	
class planetaryFortress :public building {
public:
	planetaryFortress(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }
	
private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};


class factory :public building {
public:
	factory(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }
	
private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};

class techLabOnFactory : public building{
public:
	techLabOnFactory(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }
	
private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};


class techLabOnBarracks : public building
{
public:
	techLabOnBarracks(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }
	
private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};


class barracks : public building{
public:
	barracks(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }
	
private:
	string name;
	string status;
	float buildSpeed;
	float energy;
	
	
};
class starport : public building{
public:
	starport(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }

private:
	string name;
	string status;
	float buildSpeed;
	float energy;


};
class techLabOnStarport : public building
{
public:
	techLabOnStarport(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }

private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};

class reactorOnStarport : public building
{
public:
	reactorOnStarport(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }

private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};

class reactorOnBarracks : public building
{
public:
	reactorOnBarracks(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }

private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};
class reactorOnFactory : public building
{
public:
	reactorOnFactory(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }

private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};

class barracksReactor : public building
{
public:
	barracksReactor(string n) :status(IDLE), name(n), buildSpeed(1), energy(0.0f) {}
	void constructing() { status = CONSTRUCT; }
	void idle() { status = IDLE; }
	string getStatus() { return status; }
	string& getName() { return name; }
	float& getSpeed() { return buildSpeed; }
	void energyRecovery() { energy += 0.5625f; }

private:
	string name;
	string status;
	float buildSpeed;
	float energy;
};






