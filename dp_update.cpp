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
Entry dpTable [100][100];

int orderGas(int* g, Config config, int gasStored, int day){

//cout << "Day: " << day << " Gas Stored: " << gasStored << endl;

	//initially, we add the night before's storage to the cost
	int cost = gasStored*config.c;
	//cout << gasStored << "con " << config.c << endl;
	//cout << "first: " << cost << endl;

	//base case - last day
	if (day == config.n - 1){
		//if the tank is not empty, return [ideally] inf, because it is an invalid cost
		if ((gasStored - g[day]) > 0){
			return 10000;
		}
		//otherwise, return cost of ordered gas
		//if we have exactly the right amount of gas
		if ((gasStored - g[day]) == 0){
			return cost;
		}
		//otherwise, we'll need to order some gas
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
		int tempCost = cost + orderGas(g, config, gasStored + i - g[day], day + 1);
		if (tempCost < minCost){
			minCost = tempCost;
		}
	}
	return minCost;
}

int main(){
	//first we define all of the given constants
	Config config;
	//fix this too
	config.n = 2;
	config.L = 6;
	config.P = 17;
	config.c = 4;
	//g = gas needed for each of the reamining days
	//int g[] = {4,3,1,4,2,2,4,3,1,6,6,1,5,5,5};
	int g[] = {4,3};

	//initialize the dp table with -1 in every location
	
	int minimumCost = -1;

	minimumCost = orderGas(g, config, 0, 0);

	cout << minimumCost << endl;

	return 0;
}