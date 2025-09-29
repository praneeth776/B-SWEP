#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

void display(vector<vector<int>> grid){
    for(int i = 0; i< grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int findMinTime(vector<vector<int>> grid){
    int m = grid.size();
    int n = grid[0].size();

    queue<pair<int,int>> q;
    vector<vector<int>> time(m,vector<int>(n,INT_MAX));
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 2){
                q.push(pair<int,int>(i,j));
                time[i][j] = 0;
            }
        }
    }

    
    int maxTime = 0;
    
    while(!q.empty()){
        pair<int,int> orange = q.front();
        q.pop();
        int row = orange.first; //1
        int col = orange.second; //0
        int currentTime = time[row][col]; // 1
        if(currentTime > maxTime) maxTime = currentTime;
        
        vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};
        
        for(auto direction: directions){
            int nr = row + direction[0];
            int nc = col + direction[1];
            
            if(nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1){
                pair<int,int> adjacent_orange = {nr,nc};
                if(time[nr][nc] > currentTime+1){
                    time[nr][nc] = currentTime + 1;
                    q.push(adjacent_orange);
                }
            }
        }
    }
        
    
    
    // display(time);
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j]  != 0 && time[i][j] == INT_MAX) return -1;
        }
    }

    return  maxTime;
}


int main(){
    vector<vector<int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
    cout << findMinTime(grid) << endl;
    return 0;
}