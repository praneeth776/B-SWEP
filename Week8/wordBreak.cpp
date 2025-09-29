#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void display(vector<bool> vec){
    unordered_map<bool,string> map = {{false,"False"},{true,"True"}};
    for(auto b: vec){
        cout << map[b] << endl;
    }
}

/**
 * Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 */
bool wordBreak(string s, vector<string>& wordDict){
    unordered_set<string> dict;
    for(auto word: wordDict){
        dict.insert(word);
    }

    vector<bool> memo(s.size()+1,false);
        memo[0] = true;
        
        for(int i = 1; i < memo.size(); i++){
            for(int j = i-1; j>=0; j--){
                if(memo[j]){ // Implies substring from index 0 to j-1 can be broken into words in dict. 
                    // Check if substring from index j to i is in the wordDict
                    string sub = s.substr(j,i-j);
                    if(dict.find(sub) != dict.end()){
                        memo[i] = true;
                        break;
                    }
                }
            }
        }

        display(memo);

        return memo.back();
}

bool wordBreak2(string s, vector<string>& wordDict){
    unordered_set<string> dict;
    for(auto word: wordDict){
        dict.insert(word);
    }

    // vector<int> memo(s.size()+1,false);
    // memo[0] = true;

    vector<int> trueIndices = {0};
    
    for(int i = 1; i <= s.size(); i++){
        for(int j = trueIndices.size()-1; j>=0; j++){
            int idx = trueIndices[j]+1;
            string sub = s.substr(idx,i-idx);
            if(dict.find(sub) != dict.end()){
                trueIndices.push_back(i-1);
            }
        }
    }

    return trueIndices.back() == s.size()-1;
}

int main(){
    vector<string> test = {"aaa","aaaa"};
    cout << wordBreak("aaaaaaa",test) << endl;
    return 0;
}