#pragma once
class Timer {
public:
	Timer():time(1) {}
	float& getCurrentTime() { return time; }
	void timeIncf() { time++;/*cout<<"//////////////////////now time is  :"<<time<<endl;*/}
		
private:
	float time;
};
