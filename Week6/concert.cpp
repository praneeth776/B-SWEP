#include <vector>
#include <iostream>

using namespace std;


/**
 * A concert hall has n rows numbered from 0 to n - 1, each with m seats, numbered from 0 to m - 1. 
 * You need to design a ticketing system that can allocate seats in the following cases:
 * 
 * If a group of k spectators can sit together in a row.
 * If every member of a group of k spectators can get a seat. They may or may not sit together.
 * 
 * Note that the spectators are very picky. Hence:
 * 
 * They will book seats only if each member of their group can get a seat with row number less than or equal to maxRow. maxRow can vary from group to group.
 * In case there are multiple rows to choose from, the row with the smallest number is chosen. 
 * If there are multiple seats to choose in the same row, the seat with the smallest number is chosen.
 */

class BookMyShow {
private:
    int n;
    int m;
    vector<int> ptrs; // Points to the index with the first available seat in a row. [0,m]. m means no seat available
public:
    /**
     *  Initializes the object with n as number of rows and m as number of seats per row.
     */
    BookMyShow(int n, int m): n(n), m(m), ptrs(n,m){
        
    }
    
    /** 
     *  Returns an array of length 2 denoting the row and seat number (respectively) of the first seat being allocated to the k members of the group, 
     * who must sit together. In other words, it returns the smallest possible r and c such that all [c, c + k - 1] seats are valid and empty in row r,
     *  and r <= maxRow. Returns [] in case it is not possible to allocate seats to the group.
    */
    vector<int> gather(int k, int maxRow) {
        vector<int> result;
        for(int i = 0; i <= maxRow; i++){
            if(ptrs[i] >= k){
                result.push_back(i); // row
                result.push_back(m-ptrs[i]); // column
                ptrs[i] -= k;
                break;
            }
        }
        return result;
    }
    
    /**
     * Returns true if all k members of the group can be allocated seats in rows 0 to maxRow, who may or may not sit together. If the seats can be 
     * allocated, it allocates k seats to the group with the smallest row numbers, and the smallest possible seat numbers in each row. Otherwise, returns false.
     */
    bool scatter(int k, int maxRow) {
        int totalSeats = 0;
        for(int i = 0; i <= maxRow; i++){
            totalSeats += ptrs[i];
            if(totalSeats >= k) break;
        }
        if(totalSeats < k) return false;

        int allotSeats = 0;
        int ptr = 0;
        while(ptr <= maxRow && allotSeats != k){
            int seats  =  min(ptrs[ptr],k-allotSeats);
            ptrs[ptr] -= seats;
            allotSeats += min(seats,k-allotSeats);
            ptr++;
        }
        return true;
    }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */


void test(){
    BookMyShow bms(2,5);
    bms.gather(4,0);
    bms.gather(2,0);
    bms.scatter(5,1);
    bms.scatter(5,1);
}


int main(){
    test();
    return 0;
}