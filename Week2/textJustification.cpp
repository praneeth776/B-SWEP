#include <vector>
#include <iostream>

using namespace std;


/**
 * Helper Function to print a vector to stdout. Each is printed on a new line.
 */
void displayVector(vector<string> vec){
    for(auto item: vec) cout << item << endl;
}

/**
 * Gives a string of "space" white characters
 */
string Gap(int space){
    string gap(space, ' ');
    return gap;
}

/**
 * Helper function that returns a line fit to width.
 * Have to left justify the last line and if there is only 1 word.
 */
string justify(vector<string>& words, int width){
    // Condition: words.size() + totalChars - 1 <= width. Because we have to ensure 1 space character between each pair of words in worst case.
    string line = words[0];
    // words.size() > 1 // Normal case.
    int totalchars = 0;
    for(auto word: words) totalchars += word.size();
    int whiteSpcae = width - totalchars; // Number of white space characters. 

    // The amount of white space characters have to be distributed evenly and more towards left in case it's not possible to divide evenly
    int space = whiteSpcae/(words.size() - 1);
    int extraSpace = whiteSpcae%(words.size() - 1); // extra space for spaces between words on the left in case of not even.
    for(int i = 1; i < words.size(); i++){
        if(i < extraSpace+1) line+= Gap(1);
        line += Gap(space) + words[i];
    }
    
    return line;
}

/**
 * Helper function to left justify words.
 */
string leftJustify(vector<string>& words, int width){
    // Condition: total characters + words.size() - 1 <= width
    string line = words[0];
    for(int i = 1; i < words.size(); ++i){
        line += Gap(1) + words[i];
    }

    int remaining = width - line.size(); // Padding at the end of the line.
    line += Gap(remaining);
    return line;
}

/**
 * Have to justify all the words. 
 */
vector<string> solution(vector<string>& words, int maxWidth){
    vector<string> result;
    int left = 0; 
    int right = 0;

    while(right < words.size()){
        int total = words[left].size();
        while(total + right - left  <= maxWidth && right < words.size()){
            right++;
            if(right < words.size())total += words[right].size();
        }
        // cout << "Left:" << left << "Right:" << right << endl;
        vector<string> subarray(words.begin() + left, words.begin() + right );
        // displayVector(subarray);

        string s;
        if(right - left == 1 || right == words.size()){
            s = leftJustify(subarray,maxWidth);
        } else{
            s = justify(subarray,maxWidth);
        }
        result.push_back(s);
        left = right ;
    }
    return result;
}


int main(){
    vector<string> test1 = {"This", "is", "an", "example", "of", "text", "justification."};
    vector<string> test2 = {"What","must","be","acknowledgment","shall","be"};
    vector<string> test3 = {"a"};
    int maxWidth1 = 15;
    int maxWidth2 = 16;

    vector<string> result1 = solution(test1,maxWidth1); 
    displayVector(result1);
    vector<string> result2 = solution(test2,maxWidth2); 
    displayVector(result2);
    vector<string> result3 = solution(test3,1); 
    displayVector(result3);
    return 0;
}