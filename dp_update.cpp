#include <iostream>
#include <vector>
using namespace std;

struct Config {
	int n, L, P, c;
	int g[];
};

int orderGas(vector<vector <int> > & dpTable, int* g, Config config){

	for (int i = 0; i < config.n; i++){
		cout << g[i] << " ";
	}
	cout << endl;


/*
	//if we already have the cost stored in the table, return it
	if (dpTable[day][gallons] != -1){
		cost += dpTable[][];
	}
	else {
		gallonsOrdered += 1;
		if (gallonsOrdered > 0){
			cost += 
		}
	}

	//base case - if we reach the end of all of the days
	if (currentDay == TOTAL_DAYS - 1){
		//if we have gas stored
		if (storedGas != 0){
			//return a very large number, ideally infinity
			return 10000;
		}
		//otherwise, this is a valid solution
		return cost;
	}

	
	else if (gallonsOrdered < 0){
		return orderGas(dpTable, n, g, day, gallonsOrdered + 1, cost);
	}
*/

	return 0;


}

int main(){
	//first we define all of the given constants
	Config config;
	config.n = 15;
	config.L = 6;
	config.P = 17;
	config.c = 4;
	//g = gas needed for each of the reamining days
	int g[] = {4,3,1,4,2,2,4,3,1,6,6,1,5,5,5};

	//initialize the dp table with -1 in every location
	vector < vector<int> > dpTable (config.n, vector<int> (config.n, -1));
	int minimumCost = -1;

	minimumCost = orderGas(dpTable, g, config);

	return 0;
}