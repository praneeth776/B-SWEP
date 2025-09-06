#include <vector>
#include <iostream>

using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* rotateRight(ListNode* head, int k) {
    if(head == nullptr) return nullptr;
    ListNode* curr = head;
    int length = 1;

    while(curr->next != nullptr){
        curr = curr->next;
        length++;
    }
    // curr is the tail now.
    curr->next = head;
    k = k%length;
    k = length - k;

    while(k-->0){
        curr = curr->next;
    }
    ListNode* newHead = curr->next;
    curr->next = nullptr;
    return newHead;
}


int main(){
    return 0;
}