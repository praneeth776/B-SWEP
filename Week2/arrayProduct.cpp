#include <iostream>
#include <vector>

using namespace std;

vector<int> solution(vector<int>& nums){
    vector<int> prefix(nums.size(),1); // the putput array

    for(int i = 1; i < prefix.size(); i++){
        prefix[i] = prefix[i-1]*nums[i-1]; // keeps all prefix products
    }
    int suffix = 1; // constant extra space. Used to keep track of suffix product.
    for(int i = nums.size()-1; i >= 0; i--){ // Iterate backwards
        prefix[i] = prefix[i]*suffix;
        suffix *= nums[i];
    }
    return prefix;
}

int main(){
    vector<int> test1 = {-1,1,0,-3,3};
    vector<int> result = solution(test1);
    for(auto x: result) cout << x << "," << endl;
    return 0;
}