#include <vector>
#include <iostream>

using namespace std;

/**
 * You are given an integer array ranks representing the ranks of some mechanics. ranksi  is the rank of the ith mechanic. 
 * A mechanic with a rank r can repair n cars in r * n2 minutes.
 * You are also given an integer cars representing the total number of cars waiting in the garage to be repaired.
 * Return the minimum time taken to repair all the cars.
 * Note: All the mechanics can repair the cars simultaneously.
 */
int repairCars(vector<int> ranks, int n){
    int minRank = INT_MAX;
    for(auto rank: ranks){
        minRank = min(minRank,rank);
    }

    int high = minRank * n * n;
    int low = 0;
    int mid;

    while(low < high){
        mid = (low + high)/2;
        int total = 0;
        for(auto rank: ranks){
            // Give the mechanic with rank r , k cars such that r*k*k <= mid => k = floor(sqrt(mid/r)).
            int k = (int)floor(sqrt(mid*1.0/rank));
            total += k;
        }

        cout << low << " " << high << " " << total << endl;

        if(total >= n) high = mid;
        else low = mid + 1;
    }

    return low;
}

int main(){
    vector<int> test = {4,2,3,1};
    cout << repairCars(test,10) << endl;
    return 0;
}