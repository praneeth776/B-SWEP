#include <vector>
#include <iostream>

using namespace std;


void displayStockSpan(vector<int> spans){
    for(auto span: spans){
        cout << span << " ";
    }
    cout << endl;
}


/**
 * The span of the stock's price in one day is the maximum number of consecutive days (starting from that day and going backward)
 * for which the stock price was less than or equal to the price of that day.
 */
class StockSpanner {
private:
    vector<int> stocks;
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        stocks.push_back(price);
        int i = 1;
        int curr = stocks.size()-2;
        while(curr>=0){
            if(stocks[curr] <= price) i++;
            else break;
            curr--;
        }
        return i;
    }
};

/**
 * Method to test the StockSpanner class.
 * Initiates the class and passes a list of prices to the next function. 
 * Stores the return value of next function for each of the prices and returns it.
 */
vector<int> tester(vector<int> stocks){
    vector<int> results;
    StockSpanner* obj = new StockSpanner();
    for(auto stock: stocks){
        int result = obj->next(stock);
        results.push_back(result);
    }
    return results;
}


int main(){
    vector<int> test1 = {100,40,50,60,35,25,45};
    displayStockSpan(tester(test1));
    return 0;
}