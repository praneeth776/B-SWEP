#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
 * Every adjacent pair of words differs by a single letter.
 * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
 * sk == endWord
 * Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence 
 * from beginWord to endWord, or 0 if no such sequence exists.
 */
int ladderLength(string beginWord, string endWord, vector<string>& wordList){
    // bfs starting from beginWord and endWord.
    unordered_set<string> set; // for quick access to the actual words
    for(auto word: wordList){
        set.insert(word);
    }

    queue<pair<string,int>> q;
    unordered_set<string> visited;

    q.push(pair<string,int>(beginWord,1));

    while(!q.empty()){
        string word = q.front().first;
        int dist = q.front().second;
        q.pop();
        visited.insert(word);

        if(word == endWord) return dist;

        for(int i = 0; i < beginWord.size(); i++){
            for(char c = 'a'; c<= 'z'; c++){
                string copy = word;
                copy[i] = c;
                if(set.find(copy) != set.end() && visited.find(copy) == visited.end() && word[i] != c){ // This word exists in wordList
                    q.push(pair<string,int>(copy,dist+1));
                }
            }
        }
    }

    return 0; // No path found

}

int main(){
    return 0;
}