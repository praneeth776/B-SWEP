#include <vector>
#include <iostream>

using namespace std;

/**
 * There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].
 * 
 * You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. 
 * You begin the journey with an empty tank at one of the gas stations.
 * 
 * Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, 
 * otherwise return -1. 
 * If there exists a solution, it is guaranteed to be unique.
 */
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    vector<int> diff(gas.size(),0);
    int total = 0;
    diff[0] = gas[0]-cost[0];
    for(int i = 1; i < gas.size(); i++){
        diff[i] = diff[i-1] + gas[i] - cost[i];
        total += gas[i] - cost[i];
    }
    if(total < 0) return -1;

    int idx = 0;
    int max = INT_MIN;
    for(int i = 0; i<diff.size();i++){
        if(diff[i] > max){
            idx = i;
            max = diff[i];
        }
    }

    return idx;


}

int main(){
    return 0;
}