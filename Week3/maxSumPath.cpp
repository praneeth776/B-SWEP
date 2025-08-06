#include <vector>
#include <iostream>
#include <stack>

using namespace std;


void displayPath(vector<int> path){
    for(auto node: path){
        cout << node << "->";
    }
    cout << endl;
}


/**
 * Node class
 */
class Node{
    public:
        int val;
        Node* left;
        Node* right;
        Node* next; // To keep track of the path

        Node(int val){
            this->val = val;
            this->left = nullptr;
            this->right = nullptr;
            this->next = nullptr;
        }
};

/**
 * Helper function that returns the max sum of the subtree starting at node curr.
 */
int helper(Node* curr){
    if(curr==nullptr) return 0;

    int left = helper(curr->left);
    int right = helper(curr->right);

    if(left > right) curr->next = curr->left;
    else curr->next = curr->right;

    return curr->val + max(left,right);
}

/**
 * Given a Binary Tree, the task is to find the maximum sum path from a leaf to a root.
 */
vector<int> solution(Node* root){
    vector<int> result;
    stack<int> st;

    helper(root);
    Node* curr = root;
    while(curr != nullptr){
        st.push(curr->val);
        curr = curr->next;
    }

    while(!st.empty()){
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

vector<int> test(){
    Node* root = new Node(10);
    Node* a = new Node(30);
    Node* b = new Node(15);
    Node* c = new Node(20);
    Node* d = new Node(5);

    root->left = a;
    root->right = b;
    a->left = c;
    a->right = d;

    return solution(root);
}

int main(){
    displayPath(test());
    return 0;
}

