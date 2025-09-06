#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <numeric>

using namespace std;

/**
 * 
 */
void displayVector(vector<int> nums){
    for(auto num: nums){
        cout << num << " ";
    }
    cout << endl;
}

/**
 * Take the top card of the deck, reveal it, and take it out of the deck.
 * If there are still cards in the deck then put the next top card of the deck at the bottom of the deck.
 * If there are still unrevealed cards, go back to step 1. Otherwise, stop.
 * 
 * Give an ordering of the deck that reveals the cards in increasing order according to the rules.
 */
vector<int> solution(vector<int>& deck){
    // Algorithm: We definitely have to sort the deck. If this way of revealing functions on a deck is f(deck),
    // then we need to do inverse f() on sorted array
    sort(deck.begin(),deck.end(),[](int a, int b){return a<b;});

    // How do we find the inverse function of this.
    // Solution for [2,3,5,7,11,13,17] is [2,13,3,11,5,17,7]
    queue<int> q; // Map the sorted index to the result index;
    vector<int> indices(deck.size());
    iota(indices.begin(),indices.end(),0); // [0,1,2,3,..,n-1]

    int i = 0;
    while(q.size()!= deck.size()){
        if(i%2 == 0){
            q.push(indices[i]);
        } else{
            indices.push_back(indices[i]);
        }
        i++;
    }

    vector<int> result(deck.size(),0);
    i = 0;
    while(!q.empty()){
        result[q.front()] = deck[i];
        q.pop();
        i++;
    }

    return result;
}


int main(){
    vector<int> test1 = {17,13,11,2,3,5,7};
    vector<int> test2 = {3,9,18,4,6,10};
    displayVector(solution(test1));
    displayVector(solution(test2));
    return 0;
}