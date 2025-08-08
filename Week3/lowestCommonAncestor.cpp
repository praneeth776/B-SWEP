#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;


class Node{
    public:
        int val;
        Node* left;
        Node* right;
        Node(int val){
            this->val = val;
            this->left = nullptr;
            this->right = nullptr;
        }
};


/**
 * Given the root of a Binary Tree with all unique values and two node values n1 and n2, 
 * the task is to find the lowest common ancestor of the given two nodes. 
 * The Lowest Common Ancestor (or LCA) is the lowest node in the tree that has both n1 and n2 as descendants. 
 * In other words, the LCA of n1 and n2 is the shared ancestor of n1 and n2 that is located farthest from the root.
 * We may assume that either both n1 and n2 are present in the tree or none of them are present.  
 */
Node* solution(Node* root, int a, int b){ // int a and b are the values of 2 nodes whose lowest common ancestor is to be returned.
    if(root == nullptr) return nullptr;

    if(root->val == a || root->val == b){ // This node is a or b
        return root;
    }

    Node* leftTree = solution(root->left,a,b);
    Node* rightTree = solution(root->right,a,b);

    // Atleast one of the above 2 would be not a nullptr.

    if(leftTree!=nullptr && rightTree!=nullptr){ // Implies a is in 1 subtree and b is in the other
        return root;
    }

    if(leftTree != nullptr) return leftTree; // Both a and b are in leftTree.
    return rightTree;
}

int test(){
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);


    return solution(root,7,6)->val;
}

int main(){
    cout << test() << endl;
    return 0;
}