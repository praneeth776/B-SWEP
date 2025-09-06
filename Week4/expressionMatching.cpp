#include <vector>
#include <iostream>

using namespace std;


/**
 * Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
 * '.' Matches any single character.​​​​
 * '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 */
bool solution(string s, string p){
    int i = 0;
    int j = 0;

    while(i < s.length() && j < p.length()){
        char pattern = p[j];
        char letter = s[i];

        if(pattern != '.'){
            if(pattern == '*'){
                char prev = p[j-1]; // * is guaranteed not to come first
                if(prev == '.') return true;
                while(i < s.length() && s[i] == prev){
                    i++;
                }
            } else{
                // Not a * or .
                if(pattern != letter){
                    if(j < p.length()-1 && p[j+1] == '*'){
                        j+= 2;
                        continue;
                    }
                    else {
                        return false;
                    }
                }
            }
        }

        i++;
        j++;
    }
    return i >= s.length() ; // We have reached the end of the string s while comparing with pattern
}


int main(){
    // cout << solution("aa", "a") << endl;
    // cout << solution("aa", "a*") << endl;
    // cout << solution("ab", ".*") << endl;
    // cout << solution("abcd", ".*") << endl;
    cout << solution("aab", "c*a*b") << endl;
    return 0;
}