#include <iostream>
#include <vector>
using namespace std;

//config struct to store the given values
struct Config {
	int n, L, P, c;
	Config(){};
	Config(int n, int L, int P, int c){
		this -> n = n;this -> L = L; this -> P = P; this -> c = c;
	}
};
//first we define all of the given constants in a new config
static const Config config (15, 6, 17, 4);
//g = gas needed for each of the reamining days
static const int g[] = {4,3,1,4,2,2,4,3,1,6,6,1,5,5,5};
//entry for the dpTable
struct Entry {
	int cost;
	int stored;
	Entry(){cost = -1;}	
};
//we need a dpTable that is n x L+1
Entry dpTable [15][7];

int orderGas(int gasStored, int day){

	//base case for DP
	if (dpTable[day][gasStored].cost != -1){
		return dpTable[day][gasStored].cost;
	}

	//initially, we define the storage cost from the night before
	int storageCost = gasStored*config.c;

	//base case - last day
	if (day == config.n - 1){
		//if the tank is not empty, return [ideally] inf, because it is an invalid cost
		if ((g[day] - gasStored) < 0) return 10000;

		//otherwise, return cost of ordered gas
		//if we have exactly the right amount of gas
		if ((g[day] - gasStored) == 0) return storageCost;

		//otherwise, we'll need to order some gas
		dpTable[day][gasStored].cost = storageCost + config.P;
		dpTable[day][gasStored].stored = 0;
		return (storageCost + config.P);
	}

	//find out how much gas we need for the day, if we need less than zero gallons, the tank is empty
	int gasNeeded = g[day] - gasStored;
	if (gasNeeded < 0) gasNeeded = 0;
	//initialize the minimum cost to a large number, [ideally] inf
	int minCost = 10000;
	//for 0 extra gallons to the maximum capacity, order gas for the day and make a recursive call 
	for (int i = gasNeeded; i <= (config.L - gasStored + g[day]); i++){
		//iff the gas we need is zero, we will not need to add a delivery cost at this stage
		int deliveryCost;
		i == 0 ? deliveryCost = 0 : deliveryCost = config.P;
		//the cost can now be found with a recursive call
		int tempCost = storageCost + deliveryCost + orderGas(gasStored + i - g[day], day + 1);
		if (tempCost < minCost){
			minCost = tempCost;
			dpTable[day][gasStored].cost = minCost;
			dpTable[day][gasStored].stored = gasStored + i - g[day];
		}
	}
	return minCost;
}

int main(){
	//run the algorithm to find minCost
	cout << orderGas(0, 0) << endl;
	//run the traceback code to find the purchase days
	//we need to store this in a vector due to the output reaquirements
	int nextStored = 0;
	vector <pair <int, int> > traceback;
	for (int day = 0; day < (config.n - 1); day ++){
		//first we set the amount currently in the tank to the amount in the tank from the last iteration
		int currentStored = nextStored;
		//then we get the amount in the tank on the next day
		nextStored = dpTable[day][nextStored].stored;
		//if the amount currently in the tank subtracted from the amount in the tank on the next day
		//plus the amount required is not equal to zero, we must have filled the tank
		if (nextStored - currentStored + g[day] != 0)
			traceback.push_back(make_pair(day + 1, nextStored-currentStored+g[day]));
	}

	cout << traceback.size() << endl;
	for (pair<int, int> tbp : traceback)
		cout << tbp.first << " " << tbp.second << endl;

	return 0;
}