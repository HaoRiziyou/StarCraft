#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class PreAction {
public:
	PreAction():refinery(0), needVespene(0){}
	//read the build list and store it in a vector<string>
	vector<string> readList(string buildList) {
		vector<string> toBuildList;
		ifstream outfile(buildList, ifstream::in);
		string store;
		while (!outfile.eof())
		{
			getline(outfile, store, '\n');
			if (store.length() < 2) continue;
			toBuildList.push_back(store);

		}
		outfile.close();
		return toBuildList;
	}
	//dependency precheck
	bool preCheck(vector<string> &toBuildList, string techTree) {
		string store;
		string success = "Congratulations! Passed the pre check!";
		string error = "Did not pass the pre check. The build list is invalid.";
		bool passCheck = true;
		string toBuild;
		//cout<<"precheck"<<endl;
		//int mothership = 0;
		for (int i = 0; i < toBuildList.size(); ++i)
		{
			
			string titles[] = {"name", "minerals", "vespene", "build_time", "supply_cost", "supply_provided", "start_energy", "max_energy", "race", "produced_by", "dependency"};
			
			//cout<<toBuildList[i]<<endl;

			toBuild = toBuildList[i];
			passCheck = true;
			ifstream outfile(techTree, ifstream::in);
			getline(outfile, store, '\n');
			getline(outfile, store, '\n');
			string type = "Unit";
			//cout<<"prechek loop"<<endl;
			while (!outfile.eof())//if has not been the end of the file
			{	
				getline(outfile, store, ',');
				//pass the "#building" line
				if (store == "#buildings")
				{
					type = "Building";
					getline(outfile, store, '\n');
					getline(outfile, store, ',');
				}
				//if match the name of the building or unit to be built

				if (store == toBuild)
				{
					//cout<<"prechek loop456"<<endl;

					if (store == "Refinery") {
						refinery++;
						if (refinery > 2) {
							error.append("\nMore than two refinery.");
							passCheck = false; break; }
					}
					map<string, string> M;
					M.insert(pair<string, string>(titles[0], store));
					//store the whole line of the data
					for (int j = 1; j <= 9; ++j) {
						getline(outfile, store, ',');

						//cout<<store<<endl;
						M.insert(pair<string, string>(titles[j], store));
						if (titles[j] == "vespene")
						{
							if (stoi(store) > 0)needVespene = 1;
						}
 						

					}
					getline(outfile, store, '\n');
					
					M.insert(pair<string, string>(titles[10], store));
					 
					M.insert(pair<string, string>("type", type));
					 
					detailedBuildList.push_back(M);
					//implement "produced_by" check
					bool producerCheck = false;
					for (int j = 0; j <= i; ++j) {
						
						if ((M["produced_by"] == toBuildList[j]) || (M["produced_by"] == "CommandCenter/OrbitalCommand/PlanetaryFortress")||(M["produced_by"] == "CommandCenter")) { producerCheck = true; break; }
						else if(M["produced_by"] == "Barracks/BarracksTechLab/BarracksReactor"){
							for(size_t j=0;j<i;++j){
								if( (toBuildList[j] == "Barracks")||(toBuildList[j] == "BarracksTechLab") ||(toBuildList[j] == "BarracksReactor")){ producerCheck = true; break;}
							}
						}else if(M["produced_by"] == "Starport/StarportTechLab/StarportReactor"){
							for(size_t j=0;j<i;++j){
								if( (toBuildList[j] == "Starport")||(toBuildList[j] == "StarportTechLab") ||(toBuildList[j] == "StarportReactor")){ producerCheck = true; break;}
							}
						}else if(M["produced_by"] == "Factory/FactoryTechLab/FactoryReactor"){
							for(size_t j=0;j<i;++j){
								if( (toBuildList[j] == "Factory")||(toBuildList[j] == "FactoryTechLab") ||(toBuildList[j] == "FactoryReactor")){ producerCheck = true; break;}
							}
						}
					}
					if (producerCheck == false){error.append("\nProducerCheck: Build a ").append(M["produced_by"]).append(" before building ").append(M["name"]);
					//cout<<error<<endl;
					}
					//cout<<"dependency is:"<<store<<endl;
					//implement dependency check
					if (store != "")
					{
						bool existCheck = false;
						if((store == "CommandCenter/OrbitalCommand/PlanetaryFortress"))
						{
							existCheck = true; 
						}
						else if(store == "Barracks/BarracksTechLab/BarracksReactor"){
						for(size_t j=0;j<i;++j){
								if( (toBuildList[j] == "Barracks")||(toBuildList[j] == "BarracksTechLab")||(toBuildList[j] == "BarracksReactor")){ existCheck = true; break;}
								}
						}
						else if(store == "Starport/StarportTechLab/StarportReactor"){
							for(size_t j=0;j<i;++j){
								if( (toBuildList[j] == "Starport")||(toBuildList[j] == "StarportTechLab") ||(toBuildList[j] == "StarportReactor")){ existCheck = true; break;}
							}
						}else if(store == "Factory/FactoryReactor/FactoryTechLab"){
							for(size_t j=0;j<i;++j){
								if( (toBuildList[j] == "Factory")||(toBuildList[j] == "FactoryReactor") ||(toBuildList[j] == "FactoryTechLab")){ existCheck = true; break;}
							}
						}
						else{
							for (int j = 0; j < i; ++j) {
							
								if (store == toBuildList[j]) { existCheck = true; break; }
							
							}
						}
						if (existCheck == false){error.append("\nDependency check: Build a ").append(store).append(" before building ").append(M["name"]);//cout<<error<<endl;
						}
						passCheck = (existCheck&&producerCheck);
						//cout<<passCheck<<existCheck<<endl;
					}
					else { passCheck = producerCheck;  break; }
					getline(outfile, store, '\n');
				}
				//go to the end of the line
				else getline(outfile, store, '\n');
			}
			outfile.close();
			if (needVespene > 0) {
				//cout<<"needVespene"<<endl;
					//cout<<"refinery is :"<<refinery<<endl;
				if (refinery == 0)
				{
					passCheck = false;
					error.append("\nSome units need vespene. No Refinery in the list.");
				}
			}
			if (!passCheck)
			{
				//cout<<"passcheck"<<passCheck<<endl;
				//cout << error << endl;
				
				return false;
			}
		}
		//cout << success << endl;
		return true;
	}
	vector<map<string, string>> getDetailedBuildList() { return detailedBuildList; }
private:
	vector<map<string, string>> detailedBuildList;
	int refinery;
	int needVespene;
};
