#include <iostream>
#include <vector>
using namespace std;

int orderGas(vector<int> & gasNeeded, int storageCost, int maxGallonsStored, int deliveryCost);

int main(){
	

	static const int gasNeededArr[] = {4,3,1,4,2,2,4,3,1,6,6,1,5,5,5};
	//static const int gasNeededArr[] = {4,3,1,4};
	vector<int> gasNeeded (gasNeededArr, gasNeededArr + sizeof(gasNeededArr) / sizeof(gasNeededArr[0]));
	int storageCost = 4, maxGallonsStored = 6, deliveryCost = 17;

	cout << endl;
	orderGas(gasNeeded, storageCost, maxGallonsStored, deliveryCost);




	return 0;
}


int orderGas(vector<int> & gasNeeded, int storageCost, int maxGallonsStored, int deliveryCost){
	
	vector < vector<int> > lookupTable (gasNeeded.size(), vector<int> (gasNeeded.size(),0));
	for (int i = 0; i < lookupTable.size(); i++){
		int currGalStored = 0;
		for (int j = i + 1; j < lookupTable.size(); j++){
			currGalStored += gasNeeded[j];
			if (currGalStored <= maxGallonsStored)
				lookupTable[i][j] = lookupTable[i][j-1] + storageCost*(j-i)*gasNeeded[j];
			else
				lookupTable[i][j] = -1;
		}
	}

	/*for (int i = 0; i < lookupTable.size(); i++){
		for (int j = 0; j < lookupTable.size(); j++){
			cout << lookupTable[i][j] << " ";
		}
		cout << endl;
	}*/

	vector <int> optCost (gasNeeded.size() + 1, 0);
	optCost.at(optCost.size() - 1) = 0;
	optCost.at(optCost.size() - 2) = deliveryCost + gasNeeded.at(gasNeeded.size()-1);
	vector <int> daysBought;
	for (int i = gasNeeded.size() - 2; i >= 0; i--){
		int min = -1;
		for (int j = i; j < gasNeeded.size(); j++){
			if (lookupTable.at(i).at(j) != -1){
				cout << lookupTable.at(i).at(j) << endl;
				if (lookupTable.at(i).at(j) + optCost.at(j + 1) < min || min == -1){
					min = lookupTable.at(i).at(j) + optCost.at(j + 1);
					daysBought.push_back(j);
					cout << "Bought" << endl;
				}
			}
		}
		optCost.at(i) = deliveryCost + gasNeeded.at(i) + min;
		cout << "Added to optCost" << endl;
	}

	cout << optCost.at(0);
	cout << endl;
	for (int day : daysBought){
		cout << day << " ";
	}
	cout << endl;


	return 0;

}

