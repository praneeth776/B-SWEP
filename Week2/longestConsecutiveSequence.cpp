#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_set>

using namespace std;

class DisjointSet{
    private:
        vector<int> parent;
        vector<int> size;

    public:

        /**
         * @param size - Number of individual elements to keep track of
         */
        DisjointSet(int size): parent(size,0), size(size,1){
            iota(parent.begin(),parent.end(),0);
        }
        /**
         * Finds the parent of the element at index i.
         * Applies path compression on its way.
         */
        int find(int i){
            int root = parent[i];
            if(root != parent[root]){
                return parent[i] = find(root);
            }
            return root;
        }

        /**
         * Unites the sub trees containing the elements a and b
         */
        void unite(int a, int b){
            int root_a = find(a);
            int root_b = find(b);
            if(root_a == root_b) return;

            if(size[root_a] < size[root_b]){
                parent[root_a] = root_b;
                size[root_b] += size[root_a];
            } else{
                parent[root_b] = root_a;
                size[root_a] += size[root_b];
            }
        }

};

class Node{
    public:
    Node* next;
    int val;
    Node(int val): val(val){}
};

/**
 * Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
 * You must write an algorithm that runs in O(n) time.
 */
int solution(vector<int>& nums){
    // Lets say we have nodes for each of the element in nums.
    // For a node n, we point it to the root of its left.
    unordered_set<Node> set;
    for(auto num: nums){
        Node n(num);
        set.insert(num);
    }
}

int main(){
    return 0;
}