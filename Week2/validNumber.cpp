#include <vector>
#include <iostream>

using namespace std;

/**
 * Helper function to check if the number is a decimasl.
 * Decimal is defined as either (dig).(dig) or (dig). or (.dig)
 */
bool isDecimal(string number){
    if(number.size()==0) return false;
    if(number[0] == '+' || number[0] == '-') number = number.substr(1,number.size()-1);
    bool containsDigit = false;
    int dot = 0;
    for(char c: number){
        if(c == '.') dot++;
        else if(c>='0' && c <= '9') containsDigit = true;
        else return false;
    }
    return (containsDigit&&(dot==1));
}

/**
 * Helper function to check if a number is an integer.
 * AN integer is defined as just digits
 */
bool isInteger(string number){
    if(number.size()==0) return false;
    if(number[0]=='+' || number[0]=='-') number = number.substr(1,number.size()-1);
    for(auto c: number){
        if(c<'0' || c > '9') return false;
    }
    return true;
}

/**
 * Have to make sure that number is valid.
 * Valid is defined as a decimal or integer followed by an optional exponential(e or E) and an integer.
 * So something like - (optional)"(+/-)" + (mandatory)(Integer/Decimal) + (optional) "(e/E)"+(Integer) 
 */
bool solution(string number){
    // if(number[0]=='+' || number[0]=='-') number = number.substr(1,number.size()-1); // This just eliminated the +/- from the process making process simpler
    int left = 0;
    int exp = 0;
    while(exp < number.size()){
        if(number[exp] == 'e' || number[exp] =='E') break;
        exp++;
    }

    if(exp == number.size()){ // There is no e/E in number.
        return (isInteger(number) || isDecimal(number));
    } else{
        string left (number.begin(), number.begin()+exp);
        cout << "Left:" << left << endl;
        string right (number.begin()+ exp + 1, number.end());
        cout << "Right:" << right << endl;
        return ((isDecimal(left) || isInteger(left)) && isInteger(right));
    }
}

int main (){
    string test1 = "e";
    string test2 = "++5";
    cout << solution(test1) << endl;
    cout << solution(test2) << endl;
    cout << isInteger(test2) << endl;
    cout << isDecimal(test2) << endl;
    

    return 0;
}