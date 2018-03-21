#include <iostream>
#include <vector>
using namespace std;

struct Config {
	int n, L, P, c;
	Config(){};
};

struct Entry {
	int cost;
	int nextDay;
	int stored;
};
Entry dpTable [15][6];

int orderGas(int* g, Config config, int gasStored, int day){

	//initially, we add the night before's storage to the cost
	int cost = gasStored*config.c;

	//base case for DP
	if (dpTable[day][gasStored].cost != -1){
		//cout << "Used table. Value: " << day << " " << gasStored << " " << dpTable[day][gasStored].cost << endl;
		return dpTable[day][gasStored].cost + cost;
	}

	//base case - last day
	if (day == config.n - 1){
		//if the tank is not empty, return [ideally] inf, because it is an invalid cost
		if ((gasStored - g[day]) > 0){
			return 10000;
		}
		//otherwise, return cost of ordered gas
		//if we have exactly the right amount of gas
		if ((gasStored - g[day]) == 0){
			dpTable[day][gasStored].cost = cost;
			dpTable[day][gasStored].stored = gasStored;
			dpTable[day][gasStored].nextDay = -1;
			return cost;
		}
		//otherwise, we'll need to order some gas
		dpTable[day][gasStored].cost = cost + config.P;
		dpTable[day][gasStored].stored = gasStored;
		dpTable[day][gasStored].nextDay = -1;
		return (cost + config.P);
	}

	
	//then subtract the gas we need from the gas stored
	int gasNeeded = g[day] - gasStored;
	if (gasNeeded > 0){
		//we need to order gas on this day...pay for delivery
		cost += config.P;
		//cout << cost << endl;
	}
	else if (gasNeeded < 0) gasNeeded = 0;

	int minCost = 10000;
	//for 0 extra gallons to the maximum capacity, order gas for the day
	for (int i = gasNeeded; i <= (config.L - gasStored + g[day]); i++){
		int tempCost = orderGas(g, config, gasStored + i - g[day], day + 1);
		tempCost += cost;
		
		if (tempCost < minCost){
			minCost = tempCost;
			//dpTable[day][gasStored].cost = minCost;
			//dpTable[day][gasStored].stored = gasStored + i - g[day];
			//dpTable[day][gasStored].nextDay = day + 1;
			
		}
	}

	dpTable[day][gasStored].cost = minCost;
	dpTable[day][gasStored].stored = gasStored - g[day];
	dpTable[day][gasStored].nextDay = day + 1;
	//cout << "Current day: " << day << " Stored: " << gasStored << " Cost: " << cost << " MinCost: " << minCost << endl;
	
	return minCost;
}

int main(){
	//first we define all of the given constants
	Config config;
	//fix this too
	config.n = 15;
	config.L = 6;
	config.P = 17;
	config.c = 4;
	//g = gas needed for each of the reamining days
	int g[] = {4,3,1,4,2,2,4,3,1,6,6,1,5,5,5};
	//int g[] = {4,3,1,4,2,2,4,3};

	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 6; j++){
			dpTable[i][j].cost = -1;
		}
	}

	//initialize the dp table with -1 in every location
	

	cout << orderGas(g, config, 0, 0) << endl;

	
	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 6; j++){
			cout << dpTable[i][j].nextDay << " ";
		}
		cout << endl;
	}

	int day = 0;
	for (int gasStored = 0; i < config.L; i++){
		int minCost = 1000;
		for (int i = 0; i < config.L; i++){
			if (dpTable[day][gasStored].cost != -1 && dpTable[day][gasStored].cost < minCost){
				minCost = dpTable[day][gasStored].cost;
			}
		}
		if (dpTable[day][gasStored].stored - g[day] > gasStored[dpTable[day][gasStored].nextDay][0]){
			//we bought gas
		}
	}


	return 0;
}