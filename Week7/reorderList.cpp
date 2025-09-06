#include <vector>
#include <iostream>
#include <deque>

using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void reorderList(ListNode* head) {
    deque<ListNode*> nodes;
    vector<ListNode*> order;

    ListNode* curr = head;
    while(curr != nullptr){
        nodes.push_back(curr);
        curr = curr->next;
    }

    bool front = true;
    while(!nodes.empty()){
        if(front){
            order.push_back(nodes.front());
            nodes.pop_front();
        } else{
            order.push_back(nodes.back());
            nodes.pop_back();
        }
        front = !front;
    }

    for(int i = 0; i < order.size()-1; i++){
        order[i]->next = order[i+1];
    }
    order.back()->next = nullptr;
}

int main(){
    return 0;
}