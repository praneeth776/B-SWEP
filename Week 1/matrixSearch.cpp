#include <iostream>
#include <vector>

using namespace std;

int countOccurences(string s, string word){
    int count = 0;
    int wordlen = word.length();

    for (int i = 0; i <= (int)s.size() - wordlen; i++) {
        if (s.substr(i, wordlen) == word) count++;
    }

    return count;
}
/**
 * Given a board of strings. Find the number of occurences of @param word alomg  rows(→), columns(↓) and diagonals(↘) of board.
 */
int solution(vector<vector<char>> board, string word){
    // Go over all rows.
    // Go over all columns.
    int rows = board.size();
    int cols = board[0].size();
    int n = word.size();

    int total = 0;

    // Rows
    for(int i = 0; i < rows; i++){
        string rowStr = "";
        for (int j = 0; j < cols; j++) {
            rowStr += board[i][j];
        }
        total += countOccurences(rowStr, word);
    }

    for (int j = 0; j < cols; j++) {
        string colStr = "";
        for (int i = 0; i < rows; i++) {
            colStr += board[i][j];
        }
        total += countOccurences(colStr, word);
    }

    for (int startCol = 0; startCol < cols; startCol++) {
        string diagonal = "";
        for (int i = 0, j = startCol; i < rows && j < cols; i++, j++) {
            diagonal += board[i][j];
        }
        total += countOccurences(diagonal, word);
    }

    for (int startRow = 1; startRow < rows; startRow++) {
        string diagonal = "";
        for (int i = startRow, j = 0; i < rows && j < cols; i++, j++) {
            diagonal += board[i][j];
        }
        total += countOccurences(diagonal, word);
    }

    return total;
}

int main(){
    vector<vector<char>> board = {
        {'a', 'b', 'c', 'd'},
        {'e', 'b', 'c', 'd'},
        {'a', 'b', 'c', 'd'},
        {'a', 'b', 'c', 'd'}
    };

    vector<vector<char>> board2 = {
    {'s', 'o', 's', 'o'},
    {'s', 'o', 'o', 's'},
    {'s', 's', 's', 's'}
};
    string word = "abc";
    string word2 = "sos";

    cout << solution(board, word) << endl; 
    cout << solution(board2, word2) << endl; 
    return 0;
}