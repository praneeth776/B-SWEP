#include <vector>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void inOrder(TreeNode* node, vector<int>& order){
    if(node == nullptr) return;
    inOrder(node->left, order);
    order.push_back(node->val);
    inOrder(node->right, order);
}

int kthSmallest(TreeNode* root, int k) {
    vector<int> elements;
    inOrder(root, elements);
    return elements[k-1];
}

void test(){
    TreeNode a(5);
    TreeNode b(3);
    TreeNode c(6);
    TreeNode d(4);
    TreeNode e(2);
    TreeNode f(1);

    a.left = &b;
    a.right = &c;
    b.left = &e;
    b.right = &d;
    e.left = &f;

    cout << kthSmallest(&a,3) << endl;
}

int main(){
    test();
    return 0;
}