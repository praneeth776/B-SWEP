#include <vector>
#include <iostream>
#include <queue>

using namespace std;

/**
 * There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
 * You are giving candies to these children subjected to the following requirements:
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 * @return the minimum number of candies you need to have to distribute the candies to the children.
 */
int solution(vector<int>& ratings){
    if(ratings.size() == 1) return 1;

    vector<int> candies(ratings.size(),1);

    for(int i = 1; i < candies.size(); i++){
        if(ratings[i]>ratings[i-1]) candies[i] = candies[i-1]+1;
    }

    for(int i = candies.size()-2; i>=0; i--){
        if(ratings[i]>ratings[i+1]) candies[i] = max(candies[i],candies[i+1] + 1);
    }

    int total = 0;
    for(auto candy: candies){
        total+= candy;
    }
    return total;
}

int main(){
    vector<int> ratings = {1,0,2};
    cout << solution(ratings);
    return 0;
}

// Example Cases:
// [1,0,2] - 5 (2,1,2)
// [1,0,2,2]
// 1,3,4,2