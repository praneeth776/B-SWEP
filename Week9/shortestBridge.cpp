#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>

using namespace std;

struct Pairhash{
    size_t operator () (const pair<int,int>& p) const{
        int h1 = hash<int>{}(p.first);
        int h2 = hash<int>{}(p.second);
        return h1^h2;
    }
};

int shortestBridge(vector<vector<int>> grid){
    int n = grid.size();
	unordered_set<pair<int,int>, Pairhash> island1;
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			if(grid[i][j] == 1){ // land	
				island1.insert(pair<int,int>(i,j));
			}
        }
	}
	
	unordered_set<pair<int,int>, Pairhash> island2;
	pair<int,int> start =* island1.begin(); // (0,1)

	stack<pair<int,int>> st;
	st.push(start);
	
	while(!st.empty()){
		pair<int,int> cell = st.top();
		st.pop();
		island1.erase(cell);
		island2.insert(cell);
		int r = cell.first;
		int c = cell.second;

		// Explore its neighbors in the 4 directions
		vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};

        for(auto dir: directions){
			int nr = r + dir[0];
			int nc = c + dir[1];
			if(nr >= 0 && nr < n && nc >=0 && nc<n && grid[nr][nc] == 1 && island1.find(pair<int,int>(nr,nc)) != island1.end()){
				st.push(pair<int,int>(nr,nc));
            }
        }
    }
		
    // island1 = {{1,0}}
    // island2 = {{0,1}}
    
    // island1 is a set of all land cells belonging to one island and island2 is for the other island.
    
    // 
    queue<pair<int,int>> q; // 
    unordered_set<pair<int,int>, Pairhash> visited;
    vector<vector<int>> distanceGrid(n,vector<int>(n,INT_MAX));
    
    for(auto island: island1){
        q.push(island);
        visited.insert(island);
        distanceGrid[island.first][island.second] = 0;
    }
    
    // q = {{1,1},{0,0}}
    // visited = {{1,0},{1,1},{0,0}}
    // [[1,inf],[0,1]]
    while(!q.empty()){
        pair<int,int> cell = q.front(); // {1,1}
        q.pop();
        int r = cell.first; //1
        int c = cell.second; //1
        int dist = distanceGrid[r][c]; //1
        
        vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};
        for(auto dir: directions){
            int nr = r + dir[0]; // 0
            int nc = c + dir[1]; // 1
            if(nr>=0 && nr<n && nc>=0 && nc<n && visited.find(pair<int,int>(nr,nc)) == visited.end()){
                if(grid[nr][nc] ==1){
                    return dist;
                }else{
                    visited.insert(pair<int,int>(nr,nc));
                    distanceGrid[nr][nc] = dist + 1;
                    q.push(pair<int,int>(nr,nc));
                }
            }
        }
        
    } 

    return -1;
}

int main(){
    vector<vector<int>> grid = {{1,1,1,1,1},
                                {1,0,0,0,1},
                                {1,0,1,0,1},
                                {1,0,0,0,1},
                                {1,1,1,1,1}};
    cout << shortestBridge(grid) << endl;
    return 0;
}