#include <vector>
#include <unordered_set>
#include <stack>
#include <iostream>

using namespace std;

class Node{
public:
    int val;
    bool visited;
    unordered_set<Node*> neighbors;
    Node(int val): val(val){}

};

vector<int> TopologicalSort(int n, vector<vector<int>> edges){
    unordered_map<int, Node*> graph;
    unordered_set<int> unvisited;
    for(int i = 0; i<n; i++){
        graph[i] = new Node(i);
        unvisited.insert(i);
    }
}

int main(){
    return 0;
}