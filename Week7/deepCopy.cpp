#include <vector>
#include <stdio.h>
#include <unordered_map>

using namespace std;


class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node* copyRandomList(Node* head) {
    if(head == nullptr) return nullptr;

    unordered_map<Node*, Node*> map;
    Node* curr = head;
    while(curr != nullptr){
        map[curr] = new Node(curr->val);
        curr = curr->next;
    }

    curr = head;
    while(curr != nullptr){
        if(curr->next != nullptr) map[curr]->next = map[curr->next];
        if(curr->random != nullptr) map[curr]->random = map[curr->random];
        curr = curr->next;
    }

    return map[head];
}

int main(){
    return 0;
}