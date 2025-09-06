#include <vector>
#include <iostream>

using namespace std;

int solution(string s){
    // Use Dynamic Programming
    // Consider s = s_a_b. a and b are the last 2 digits in s.
    // Case 1: number of decodings of s = decodings of s_a (if b is valid)
    // Case 2: number of decosings of s also = decodings of s (if a_b is valid)
    vector<int> memo(s.size()+1,0);
    memo[0] = 1; // Represents empty string
    if(s[0] != '0') memo[1] = 1; // Represents the first digit only. A digit by itself is valid if ist from 1-9

    for(int i = 2; i < memo.size(); i++){
        int case1 = 0, case2 = 0;
        if(s[i-1] != '0'){
            // The digit by itself is valid.
            case1 = memo[i-1];
        }
        if(s[i-2] == '1' || (s[i-2] == '2' && ((s[i-1]-'0')<7))){
            case2 = memo[i-2];
        }
        memo[i] = case1 + case2;
    }

    return memo.back();
}

int main(){
    string s = "30";
    cout << solution(s) << endl;
    return 0;
}