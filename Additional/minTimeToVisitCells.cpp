#include <iostream>
#include <vector>

using namespace std;

/**
 * You are given a m x n matrix grid consisting of non-negative integers where grid[row][col] represents the minimum time required to be able to 
 * visit the cell (row, col), which means you can visit the cell (row, col) only when the time you visit it is greater than or equal to grid[row][col].
 * You are standing in the top-left cell of the matrix in the 0th second, and you must move to any adjacent cell in the four directions: up, down, left, 
 * and right. Each move you make takes 1 second.
 * @return the minimum time required in which you can visit the bottom-right cell of the matrix. If you cannot visit the bottom-right cell, then return -1.
 */
int minimumTime(vector<vector<int>>& grid){
    int m = grid.size();
    int n = grid[0].size();

    auto compare = [](tuple<int,int,int> a, tuple<int,int,int> b){
        return get<2>(a) < get<2>(b);
    };
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,decltype(compare)> pq(compare);
    vector<vector<int>> times(m,vector<int>(n,INT_MAX));

    times[0][0] = 0;
    pq.push(make_tuple(0,0,0));

    vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};

    while(!pq.empty()){
        auto [r,c,time] = pq.top();
        pq.pop();

        for(auto dir: directions){
            int nr = r+dir[0];
            int nc = c+dir[1];
            if(nr>=0 && nr<m && nc>=0 && nc<n && times[nr][nc]!=INT_MAX){
                times[nr][nc] = max(time+1, grid[nr][nc]);
                pq.push(make_tuple(nr,nc,times[nr][nc]));
            }
        }
    }

    if(times[m-1][n-1] == INT_MAX) return -1;
    return times[m-1][n-1];
}

int main(){
    return 0;
}