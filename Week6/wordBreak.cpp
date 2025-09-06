#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

bool wordBreak(string s, vector<string>& wordDict){
    unordered_set<string> dictionary;
        vector<bool> memo(false,s.size());

        for(string s : wordDict){
            dictionary.insert(s);
        }
        int ptr = 0;
        for(int i = 1; i < memo.size();i++){
            string sub(s.begin()+ptr, s.begin()+i);
            if(dictionary.find(sub) != dictionary.end()){
                ptr = i+1;
                memo[i] = true;
            }
        }

        return memo.back();
}

int main(){
    vector<string> dict = {"leet","code"};
    cout << wordBreak("leetcode",dict) << endl;
    return 0;
}