#include <vector>
#include <iostream>
#include <unordered_set>


using namespace std;

class Node{
    public:
    int course; // This is the course index [0,n)
    int postOrder;
    bool visited;
    bool pathVisited;
    unordered_set<Node*> vertices;

    Node(int course): course(course), postOrder(INT_MAX){}
};

bool dfs(Node* node, unordered_set<int>& unvisited){
    node->visited = true;
    unvisited.erase(node->course);
    node->pathVisited = true;
    for(Node* neighbor: node->vertices){
        if(!neighbor->visited){
            bool status = dfs(neighbor, unvisited);
            // if(status) return true;
        }
        if(neighbor->visited && neighbor->pathVisited) return true; // cycle detected
    }
    node->pathVisited = false;
    return false;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    //Algotithm: Use Dsds
    unordered_map<int,Node*> graph;
    unordered_set<int> unvisited;
    for(int i = 0; i<numCourses; i++){
        unvisited.insert(i);
        graph[i] = new Node(i);
    }

    for(auto prereq: prerequisites){
        graph[prereq[0]]->vertices.insert(graph[prereq[1]]);
    }

    // DFS:
    // Node x -> vertices. Lets say I have a order. 
    while(!unvisited.empty()){
        Node* start = graph[*unvisited.begin()];
        bool status = dfs(start, unvisited);
        if(status) return false;
    }

    return true;

}

int main(){
    return 0;
}