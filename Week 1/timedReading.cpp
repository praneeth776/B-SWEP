#include <iostream>
#include <vector>

using namespace std;

bool isLetter(char &c){
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

int solution(string s, int k){
    int i = 0;
    int n = s.size();
    
    int numWords = 0;

    while(i < s.size()){
        if(!isLetter(s[i])) { // Skips non letters
            i++;
            continue;
        }
        // s[i] is a letter
        int start = i;

        while(i < n && isLetter(s[i])) i++;

        // Now i - start  is the length of word
        if(i - start <= k) numWords++;
    }

    return numWords;
}

int main(){
    return 0;
}