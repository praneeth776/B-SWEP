#include <vector>
#include <iostream>

using namespace std;

/**
 * Only one repeated number in nums. Have to find it. The number can be repeated any number of times though size n. numbers from 1 to n-1 will be there
 * for num in nums 1<=num <= n-1. 
 * You must solve the problem without modifying the array nums and using only constant extra space.
 */
int solution(vector<int>& nums){
    // Had to learn Floyd's Cycle Detection from Youtube - https://www.youtube.com/watch?v=wjYnzkAhcNk 
    // https://www.geeksforgeeks.org/dsa/floyds-cycle-finding-algorithm/
    
    int slow = nums[0];
    int fast = nums[nums[0]];
    while(slow != fast){
        slow = nums[slow];
        fast = nums[nums[fast]];
    }

    // Now slow = fast.
    // Set slow to nums[0]
    slow = 0;
    while(slow != fast){
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;

}

int main(){
    vector<int> test1 = {1,2,3,4,2};
    cout << solution(test1) << endl;
    return 0;
}