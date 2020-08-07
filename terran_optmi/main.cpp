//Optimization
//main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "Rush.h"
#include "ForwardSimulation.h"
#include "PreAction.h"
#include "Push.h"
#include <chrono>
using namespace std;
int main(int argc, char*argv[]) {
	string optType = argv[1];
	string unit = argv[2];

	if (optType == "rush") {
		int limitTime = stoi(argv[3]);
		int loops = 30;
		//cout <<"here start RUSH initialize \n"<<endl;
		Rush rush(unit);
		//cout <<"here ****end*** RUSH initialize \n"<<endl;
		ForwardSimulation fS(unit, limitTime);
		//cout <<"end forwardSimulation"<<endl;
		vector<vector<string>> generation = rush.firstGeneration();
		//auto start = chrono::high_resolution_clock::now();
		//cout <<"line 27" << endl;
		//for (char s : generation) cout << s << endl;
		
		vector<string> kinglist = rush.rush(generation, limitTime, loops);
		//cout <<"line 29" << endl;
		//auto end = chrono::high_resolution_clock::now();
		//auto duration = chrono::duration_cast<chrono::seconds>(end - start);
		//cout << "rush end. Time used: " << endl << duration.count() << " sec" << endl;
		

		while (!fS.ForSimulation(kinglist)) {
			
			kinglist.pop_back();
			
		}
		
		fS.ForSimulation(kinglist, true);
	
	}
	else if (optType == "push")
	{
		char unitAmount = stoi(argv[3]);
		int loops = 30;
		//cout <<"here start push initialize \n"<<endl;
		Push push(unit, unitAmount);
		//cout <<"here ****end*** push initialize \n"<<endl;
		ForwardSimulation fS(unitAmount, unit);
		vector<vector<string>> generation = push.firstGeneration();
		//cout <<"the method push.push"<<endl;
		//auto start = chrono::high_resolution_clock::now();
		vector<string> kinglist = push.push(generation, loops);
		//cout <<"find the kinglist"<<endl;
		//auto end = chrono::high_resolution_clock::now();
		//auto duration = chrono::duration_cast<chrono::seconds>(end - start);
		//cout << "push end. Time used: " << endl << duration.count() << " sec" << endl;

		int j = 0;
		for (char i = 0; (i < unitAmount) && (j < kinglist.size()); ) {
			if (kinglist[j] == unit) i++;
			j++;
		}
		while (kinglist.size() > j)
		{
			kinglist.pop_back();
		}

		//cout << "............." << endl;
		//for (string s : kinglist)cout << s << endl;
		//cout << "............." << endl;

		fS.ForSimulation(kinglist, true);
		
	}
	return 0;
}
