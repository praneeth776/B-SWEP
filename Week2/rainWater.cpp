#include <iostream>
#include <vector>
#include <span>

using namespace std;

void displayVector(vector<int> vec){
    for(auto item: vec) cout << item << endl;
}
/**
 * Helper function that returns the peak among given heights.
 */
int findPeak(vector<int>& heights){
    int peak = heights[0];
    int peakIdx = 0;
    for(int i = 1; i < heights.size(); i++){
        if(heights[i] > peak){
            peak = heights[i];
            peakIdx = i;
        }
    }
    return peakIdx;
}
/**
 * Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
 */
int trap(vector<int>& heights){
    // Algorithm: Find the peak among heights. Now look at the left part and right part of this peak and find the respective peaks. 
    // Carry on till you reach ends.
    vector<int> lefts;
    vector<int> rights;
    int peak = findPeak(heights);

    int left = peak;
    while(left > 0){
        vector<int> subarray(heights.begin(),heights.begin()+left);
        left = findPeak(subarray);
        lefts.push_back(left);
    }
    
    int right = peak;
    while(right < heights.size()-1){
        vector<int> subarray(heights.begin()+right + 1,heights.end());
        int r = findPeak(subarray);
        rights.push_back(right + r + 1 );
        right = right + r + 1;
    }

    vector<int> peaks;
    for(int i = lefts.size()-1; i>=0; i--){
        peaks.push_back(lefts[i]);
    }
    peaks.push_back(peak);

    for(auto idx: rights){
        peaks.push_back(idx);
    }

    // Now we have to find the water stored between consecutive peaks.
    int total = 0;
    displayVector(peaks);
    for(int i = 0; i < peaks.size()-1; i++){
        int ht = min(heights[peaks[i]],heights[peaks[i+1]]); // max height;
        int pocket = 0;
        cout << "Between " << peaks[i] << " and " << peaks[i+1] << ": ";
        for(int j = peaks[i]+1; j<peaks[i+1]; j++){
            pocket += ht - heights[j];
        }
        cout << pocket << endl;
        total += pocket;
    }

    return total;

}

int main(){
    vector<int> test1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> test2 = {4,2,0,3,2,5};
    vector<int> test3 = {5};
    cout << trap(test1) << endl;
    cout << trap(test2) << endl;
    cout << trap(test3) << endl;
    return 0;
}