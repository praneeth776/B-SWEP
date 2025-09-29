#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
    int label;
    int distance;
    bool visited;
    unordered_map<int,int> neighbors;
    Node(int label): label(label), distance(INT_MAX), visited(false){};
};

/**
 * You are given a network of n nodes, labeled from 1 to n. 
 * You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), 
 * where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
 *  We will send a signal from a given node k. 
 * Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
 */
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<Node*> nodes(n);
    for(int i = 0; i<n; i++){
        nodes[i] = new Node(i);
    }

    for(auto edge : times){
        nodes[edge[1]]->neighbors[edge[2]] = edge[3];
    }

    auto comparator = [](pair<int,int> a, pair<int,int> b){
        return a.second < b.second;
    };
    priority_queue< pair<int,int>, vector<pair<int,int>>, decltype(comparator)> pq(comparator);

    pq.push(pair<int,int>(k,0));

    while(!pq.empty()){
        auto [label, time] = pq.top();
        pq.pop();
        Node* node = nodes[label];
        if(node->visited) continue;
        node->visited = true;
        node->distance = time;

        for(auto [vertex, cost] : node->neighbors){
            if(nodes[vertex]->visited) continue; // already visited
            pq.push(pair<int,int>(vertex,time+cost));
        }
    }

    int maxTime = -1;
    for(auto node: nodes){
        maxTime = max(maxTime,node->distance);
    }
    if(maxTime == INT_MAX) return -1;
    return maxTime;
}

int main(){
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    cout << networkDelayTime(times,4,2) << endl;
    return 0;
}