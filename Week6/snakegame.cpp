#include <vector>
#include <iostream>

using namespace std;

/**
 * 
 */
class SnakeGame {
private:
    int height;
    int width;
    int score;
    int itr; // To keep track of the food
    vector<int> head; // To keep track of the head
    vector<int> tail; // To keep track of the tail
    vector<vector<char>> game; // is 0 if empty, -1 if occupied by snake, +1 if it has food.
    vector<vector<char>> next;
    vector<vector<int>> food;

public:
    SnakeGame(int width, int height, vector<vector<int>>& food): game(vector<vector<char>>(height,vector<char>(width,0))), 
    food(food), itr(0), score(0), head(vector<int>(2,0)), tail(vector<int>(2,0)), height(height), width(width),
    next(vector<vector<char>>(height,vector<char>(width,'X'))){
        game[0][0] = -1; // Occupied by Snake
    }
    
    /**
     * Returns the score of the game after applying one direction move by the snake. If the game is over, return -1.
     */
    int move(string direction) {

        // head = head + direction. 
        // If out of bounds  return -1;
        // If its food, do nothing.
        // If its a part of snake, return -1;
        // If its just an empty space, update the tail; 
        unordered_map<char,vector<int>> directions({{'D',{1,0}},{'U',{-1,0}},{'L',{0,-1}},{'R',{0,1}},{'X',{0,0}}});
        
        next[head[0]][head[1]] = direction[0]; // Indicates the direction 
        head[0] = head[0] + directions[direction[0]][0];
        head[1] = head[1] + directions[direction[0]][1];

        if(head[0] < 0 || head[0] >= height || head[1] < 0 || head[1] >= width) {
            cout << endl << "Boundary" << endl;
            return -1;
        };

        if(game[head[0]][head[1]] == -1){ 
            if(head[0] != tail[0] || head[1] != tail[1]) return -1; // Already a part of snake
        }

        if(itr < food.size() && head[0] == food[itr][0] && head[1] == food[itr][1]){ // Snake ate food;
            score++;
            itr++;
        } else{ // Not food cell
            // Have to move the tail
            vector<int> dir = directions[next[tail[0]][tail[1]]];
            game[tail[0]][tail[1]] = 0;
            next[tail[0]][tail[1]] = 'X'; // Marked as an empty cell
            tail[0] = tail[0] + dir[0];
            tail[1] = tail[1] + dir[1];
        }
        game[head[0]][head[1]] = -1; // Marks this cell as occupied by snake;
    
        
        return score;
    }
};

void test(){
    vector<vector<int>> food = {{2,0},{0,0},{0,2},{2,2}};
    SnakeGame sg(3,3,food);
    cout << sg.move("D") << endl;
    cout << sg.move("D") << endl;
    cout << sg.move("R") << endl;
    cout << sg.move("U") << endl;
    cout << sg.move("U") << endl;
    cout << sg.move("L") << endl;
    cout << sg.move("D") << endl;
    cout << sg.move("R") << endl;
    cout << sg.move("R") << endl;
    cout << sg.move("U") << endl;
    cout << sg.move("L") << endl;
    cout << sg.move("D") << endl;
}

int main(){
    test();
    return 0;
}