#include <vector>
#include <iostream>

using namespace std;

void displayStack(vector<string> a){
    for(auto b: a){
        cout << b << endl;
    }
}
/**
 * Given a target array and an integer n. 
 * Perform push or pop operations on the stream [1,n] so that the resultant stack from bottom to top is target
 * Rules:
 * If the stream of the integers is not empty, pick the next integer from the stream and push it to the top of the stack.
 * If the stack is not empty, pop the integer at the top of the stack.
 * If, at any moment, the elements in the stack (from the bottom to the top) are equal to target,
 * do not read new integers from the stream and do not do more operations on the stack.
 */
vector<string> solution(vector<int> target, int n){
    vector<string> result;

    int i = 0; // ptr to iterate over target
    int j = 1; // ptr to iterate over [1,n]
    while(i < target.size() && j <= n){
        for(int k = j; k < target[i]; k++){
            result.push_back("Push");
            result.push_back("Pop");
        }
        result.push_back("Push");
        j = target[i]+1;
        i++;
    }

    return result;
}


int main(){
    vector<int> test1 = {1,2};
    displayStack(solution(test1,4));
    return 0;
}