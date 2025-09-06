#include <iostream>
#include <vector>
#include <map>

using namespace std;

/**
 * TreeNode struct.
 */
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


void displayTree(vector<vector<int>> levels){
    for(auto level: levels){
        for(auto x: level) cout << x << " ";
        cout << endl;
    }
}
/**
 * This helps travers through the entire tree and add the TreeNodes to the datastructure.
 */
void traverseTree(TreeNode* root, int col, int row, map<int,vector<vector<int>>> &traversals){
    if(root == nullptr) return;

    if(row >= traversals[col].size()) traversals[col].resize(row+1);

    traversals[col][row].push_back(root->val);

    traverseTree(root->left, col-1, row+1, traversals);
    traverseTree(root->right, col+1, row+1, traversals);
}

/**
 * For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. 
 * The root of the tree is at (0, 0).
 *  The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column 
 *          and ending on the rightmost column. 
 * There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.
 * Return the vertical order traversal of the binary tree.
 */
vector<vector<int>> solution(TreeNode* root){
    // Have a map<int,vector<vector<int>>> to store.
    // unordered_map to store for each level.
    // key is the column and vector<int> will be the nodes on the same row and col which would 
    // later be sorted.

    map<int,vector<vector<int>>> traversals;
    traverseTree(root, 0, 0, traversals);
    vector<vector<int>> result;

    for(auto pair: traversals){
        vector<int> column;
        for(auto elements: pair.second){
            sort(elements.begin(),elements.end());
            for(auto element: elements) column.push_back(element);
        }
        result.push_back(column);
    }
    
    return result;

}

vector<vector<int>> test1(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    return solution(root);
}

int main(){
    displayTree(test1());
    return 0;
}