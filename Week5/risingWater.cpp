#include <vector>
#include <iostream>

using namespace std;



/**
 * You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
 * It starts raining, and water gradually rises over time. At time t, the water level is t,
 * meaning any cell with elevation less than equal to t is submerged or reachable.
 * You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t.
 *  You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
 * Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).
 */
int solution(vector<vector<int>>& grid){
    // Reduction: Find the path with minimum elevation along the way from top left to bottom right
    
    // Approach: modified dikstra's 
    int n = grid.size();

    auto compare = [](const vector<int>& a, const vector<int>& b) {
        return a[0] > b[0];
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> pq(compare);
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    // The directions for 4-directional movement.
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // Start at the top-left corner. The time to reach it is its own elevation.
    pq.push({grid[0][0], 0, 0});

    while (!pq.empty()) {
        // Get the cell with the minimum maximum elevation so far.
        vector<int> current = pq.top();
        pq.pop();

        int max_elev = current[0];
        int r = current[1];
        int c = current[2];

        if (visited[r][c]) {
            continue;
        }
        visited[r][c] = true;

        // Reached the destination
        if (r == n - 1 && c == n - 1) {
            return max_elev;
        }

        // Explore neighbors.
        for (auto dir : directions) {
            int nr = r + dir[0];
            int nc = c + dir[1];

            // Check if the neighbor is within grid boundaries.
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                int new_elev_cost = max(max_elev, grid[nr][nc]);
                pq.push({new_elev_cost, nr, nc});
            }
        }
    }

    return -1;
}



int main(){
    return 0;
}