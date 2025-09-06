#include <vector>
#include <iostream>
#include <deque>

using namespace std;


// Definition for singly-linked list.
struct Node {
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

void levelTraversal(vector<Node*> &nodes, Node* curr){
    if(curr == nullptr) return;
    nodes.push_back(curr);
    levelTraversal(nodes, curr->child);
    levelTraversal(nodes, curr->next);
}

Node* flatten(Node* head) {
    vector<Node*> nodes;
    nodes.push_back(nullptr);
    levelTraversal(nodes,head);
    nodes.push_back(nullptr);

    for(int i = 1; i < nodes.size()-1; i++){
        nodes[i]->child = nullptr;
        nodes[i]->prev = nodes[i-1];
        nodes[i]->next = nodes[i+1];
    }

    return head;
}

int main(){
    return 0;
}