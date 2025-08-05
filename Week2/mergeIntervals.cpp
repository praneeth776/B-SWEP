#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 
 */
 void displayIntervals(vector<vector<int>> intervals){
    for(auto interval: intervals){
        cout << "[" << interval[0] << ", " << interval[1] << "]" << endl;
    }
 }

/**
 * Custom comparator that sorts the intervals in ascending order of their start times.
 */
bool comparator(vector<int> a, vector<int> b){
    return a[0] < b[0];
}
/**
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
 * and return an array of the non-overlapping intervals that cover all the intervals in the input.
 */
vector<vector<int>> solution(vector<vector<int>> intervals){
    // Algorithm: Sort the intervals based on their start time. 
    // Iterate over the sorted vector and merge successive elements if end_0 >= start_1 => [start_0,max(end_0,end_1)]
    sort(intervals.begin(),intervals.end(),comparator);
    vector<vector<int>> result;
    int i = 0;
    while(i < intervals.size()){
        // New interval.
        int start = intervals[i][0];
        int end = intervals[i][1];
        while(++i && i < intervals.size()){
            if(intervals[i][0] <= end){
                end = max(end,intervals[i][1]); // Merging intervals.
            } else{
                break;
            }
        }
        vector<int> merged = {start,end};
        result.push_back(merged);
    }
    return result;
}

int main(){
    vector<vector<int>> test1 = {{1,3},{2,6},{8,10},{4,13},{15,18}};
    displayIntervals(solution(test1));
    return 0;
}