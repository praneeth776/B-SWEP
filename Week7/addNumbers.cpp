#include <vector>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int getNumber(ListNode* head){
    int n = 0;

    ListNode* curr = head;
    while(curr != nullptr){
        n*= 10;
        n += curr->val;
        curr = curr->next;
    }

    return n;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
    vector<ListNode*> num1;
    vector<ListNode*> num2;

    ListNode* curr = l1;
    while(curr!= nullptr){
        num1.push_back(curr);
        curr = curr->next;
    }

    curr = l2;
    while(curr != nullptr){
        num2.push_back(curr);
        curr = curr->next;
    }

    int carry = 0;
    ListNode* next = nullptr;

    int ptr1 = 0;
    int ptr2 = 0;

    cout << num1.size() << endl;
    cout << num2.size() << endl;

    while(ptr1 != num1.size() || ptr2 != num2.size()){
        cout << "Entered While Loop" << endl;
        int val1 = 0;
        int val2 = 0;

        if(ptr1 < num1.size()){
            val1 = num1[num1.size() - 1 -ptr1]->val;
            ptr1++;
        }

        if(ptr2 < num2.size()){
            val2 = num2[num2.size() - 1 - ptr2]->val;
            ptr2++;
        }

        curr = new ListNode((val1+val2+carry)%10);
        cout << curr << endl;
        carry = (val1+val2+carry)/10;
        curr->next = next;
        next = curr;
    }

    if(carry == 1){
        curr = new ListNode(1);
        curr->next = next;
    }

    cout << curr << endl;

    return curr;
}

void test(){
    ListNode a(7);
    ListNode b(2);
    ListNode c(4);
    ListNode d(3);
    a.next = &b;
    b.next = &c;
    c.next = &d;

    ListNode zero(0);
    ListNode five(5);
    // cout << getNumber(&zero) << endl;
    ListNode* res = addTwoNumbers(&five,&five);
    cout << res->val << endl;
    cout << res->next->val << endl;
    cout << res->next->next << endl;
    
}

int main(){
    test();
    return 0;
}