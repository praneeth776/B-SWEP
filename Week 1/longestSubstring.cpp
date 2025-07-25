#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int solution(string s){
    unordered_set<char> map;
    int left, right = 0;
    int max = 1;
    int curr_size = 1;
    map.insert(s[0]);

    while(right < s.size()-1){
        if(map.find(s[right + 1]) == map.end()){
            map.insert(s[right+1]);
            curr_size++;
            if(curr_size > max) max = curr_size;
            right++;
        } else{
            map.erase(s[left]);
            curr_size--;
            left++;
        }
    }
    
    return max;
}

int main(){
    cout << solution("abcabba") << endl; // Should be 3
    cout << solution("aaaaaa") << endl;  // 1
    cout << solution("abcdefg") << endl; // 7
    return 0;
}