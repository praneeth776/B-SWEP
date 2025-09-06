#include <vector>
#include <stack>
#include <iostream>

using namespace std;


class DinnerPlates {
private:
    stack<int,vector<int>> default_st;
    vector<stack<int,vector<int>>> dinnerPlates;
    int capacity;
    int left; // Ptr to the next empty space. to the left
    int right; // Ptr to the last dinner plate
public:
    DinnerPlates(int capacity): capacity(capacity), left(0), right(0){
        default_st = stack<int,vector<int>>();
        dinnerPlates = vector<stack<int,vector<int>>>();
    }
    
    void push(int val) {
        if(left >= dinnerPlates.size()){ // Left pointer out of bounds
            dinnerPlates.push_back(default_st);
        }
        stack<int,vector<int>> &st = dinnerPlates.at(left); // Getting the stack
        st.push(val); // Push the elemnt to stack

        // Update left and right pointers
        while(left < dinnerPlates.size() && dinnerPlates.at(left).size()== capacity){
            left++;
        }
        if(right < left) right = left;
    }
    
    int pop(){
        // Pop the element that right ptr points to
        stack<int,vector<int>> &st = dinnerPlates.at(right);
        if(st.size()==0) return -1; // Invalid pop
        int val = st.top();
        st.pop();

        //Update the Right and Left pointers
        if(left > right) left = right; // Because now an empty space is created at right and left is ahead, which should be fixed.

        while(dinnerPlates.at(right).size() != 0){ // Move right pointer to the next non empty right most stack
            right--;
        }

        return val;
    }
    
    int popAtStack(int index) {
        if(index < 0 || index >= dinnerPlates.size()) return -1; // Invalid index
        if(index == dinnerPlates.size()-1) return pop();
        stack<int,vector<int>> &st = dinnerPlates.at(index);
        if(st.size()==0) return -1; // Stack at index already empty

        int val = st.top();
        st.pop();

        // Update left and right pointers
        // Left points to the leftmost available empty space which could be at this index now.
        if(left > index) left = index;
        // Right pointer need not be updated if index is not the last stack
        return val;
    }
};


void test(){
    DinnerPlates* obj = new DinnerPlates(2);
    obj->push(1);
    obj->push(2);
    obj->push(3);
    obj->push(4);
    obj->push(5);

    // cout << obj->pop() << endl;
    cout << obj->popAtStack(0) << endl; // 2
    
    obj->push(20);
    obj->push(21);
    
    cout << obj->popAtStack(0) << endl; // 20
    cout << obj->popAtStack(2) << endl; // 21

    cout << obj->pop() << endl; // 5
    cout << obj->pop() << endl; // 4
    cout << obj->pop() << endl; // 3
    cout << obj->pop() << endl; // 1
    cout << obj->pop() << endl; // -1

    free(obj);
}

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */

int main(){
    test();
    return 0;
}