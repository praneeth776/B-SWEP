#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;



class MovieRentingSystem {
private:
    /**
     * Movie class to store info regarding a movie
     */
    class Movie{
        public:
        int movieid;
        int price;
        bool rented;
        Movie(int movie, int price): movieid(movie),rented(false),price(price){};
    };

    /**
     * Shop class to store info regarding a shop
     */
    class Shop{
        public:
        int shopid;
        unordered_map<int, Movie*> movies; // Maps movie id to Movie* ptr
        Shop(int shop): shopid(shop){

        };
        Shop(){};

        ~Shop(){
            for(auto movie: movies){
                delete movie.second;
            }
            delete this;
        }
    };

    vector<Shop*> shops; // Keeps track of all the shops
    vector<unordered_map<int,int>> rentedMovies;// Index i corresponds to ith shop. rentedMovies[i] = {key = movieid,val = price}

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries): shops(n), rentedMovies(n) {
        for(auto entry: entries){
            int shopid = entry[0];
            int movieid = entry[1];
            int price = entry[2];

            Movie* movie = new Movie(movieid,price); // Created a movie with id and price
            if(shops[shopid] == nullptr) shops[shopid] = new Shop(shopid); // Created shop if it did not exist before
            Shop* shop = shops[shopid];

            shop->movies[movieid] = movie; // Inserted this movie into the shop and at most one movie with movieid at a shop
        }
    }
    
    /**
     * Finds the cheapest 5 shops that have an unrented copy of a given movie.
     */
    vector<int> search(int movie) {
        struct query{
            int shop;
            int price;
        };
        vector<query> queries;
        for(auto shop: shops){
            if(shop == nullptr) continue;

            if(shop->movies.find(movie) != shop->movies.end() && !shop->movies[movie]->rented){ // Found the movie at this shop
                queries.push_back({shop->shopid,shop->movies[movie]->price});
            }
        }

        // Now results has all the shops with movie available
        // Optimize. Find the 5 minimum rather than sorting

        // sort(queries.begin(),queries.end(),[](query a, query b){
        //     if(a.price == b.price) return a.shop < b.shop;
        //     return a.price < b.price;
        // });

        auto compare = [](query a , query b){
            if(a.price == b.price) return a.shop < b.shop;
            return a.price < b.price;
        };

        priority_queue<query,vector<query>,decltype(compare)> pq(compare);

        for(int i = 0; i < queries.size(); ++i){
            if(i<5){
                pq.push(queries[i]);
            } else{
                if(compare(queries[i], pq.top())){
                    pq.pop();
                    pq.push(queries[i]);
                }
            }
        }


        vector<int> result(min(5,(int)queries.size()),0);
        for(int i=min(4,(int)queries.size()-1); i>=0; i--){
            result[i] = pq.top().shop;
            pq.pop();
        }

        return result;
    }
    
    /**
     * Rents an unrented copy of a given movie from a given shop.
     */
    void rent(int shop, int movie) {
        unordered_map<int,Movie*>::iterator it = shops[shop]->movies.find(movie);
        if(it == shops[shop]->movies.end()) return;
        shops[shop]->movies[movie]->rented = true; // Setting rented to true
        rentedMovies[shop][movie] = shops[shop]->movies[movie]->price; // Key Value pair
    }
    
    /**
     * Drops off a previously rented copy of a given movie at a given shop.
     */
    void drop(int shop, int movie) {
        //  unordered_map<int,Movie*>::iterator it = shops[shop]->movies.find(movie);
        if(shops[shop]->movies.find(movie) == shops[shop]->movies.end()) return;
        shops[shop]->movies[movie]->rented = false; // Setting rented to false
        rentedMovies[shop].erase(movie);
    }
    
    /**
     * Returns the cheapest 5 rented movies
     */
    vector<vector<int>> report() {
        vector<vector<int>> results;
        for(int i = 0; i<rentedMovies.size(); i++){ // Corresponds to rented movies at this shop
            for(auto movie: rentedMovies[i]){
                vector<int> a = {i ,movie.first,movie.second}; // {shop, movieid, price}
                results.push_back(a);
            }
        }

        // Optimize
        // rather than sorting find the 5 minimums
        // sort(results.begin(),results.end(),[](vector<int> a, vector<int> b){
        //     if(a[2]==b[2]){ // same price
        //         if(a[0]==b[0]) return a[1] < b[1];
        //         return a[0] < b[0];
        //     }
        //     return a[2] < b[2];
        // });

        auto compare = [](vector<int> a, vector<int> b){
            if(a[2]==b[2]){ // same price
                if(a[0]==b[0]) return a[1] < b[1];
                return a[0] < b[0];
            }
            return a[2] < b[2];
        };
        priority_queue<vector<int>,vector<vector<int>>, decltype(compare)> pq(compare);

        for(int i = 0; i < results.size(); ++i){
            if(i<5){
                pq.push(results[i]);
            } else{
                if(compare(results[i], pq.top())){
                    pq.pop();
                    pq.push(results[i]);
                }
            }
        }


        vector<vector<int>> report(min(5,(int)results.size()));
        for(int i = min(4,(int)results.size()-1); i>= 0; i--){
            report[i] = (vector<int>({pq.top()[0],pq.top()[1]}));
            pq.pop();
        }
        

        return report;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */

void test(){
    vector<vector<int>> x = {{0,418,3},{9,5144,46},{2,8986,29},{6,1446,28},{3,8215,97},{7,9105,34},{6,9105,30},{5,1722,94},{9,528,40},{3,850,77},{3,7069,40},{8,1997,42},{0,8215,28},{7,4050,80},{4,7100,97},{4,9686,32},{4,2566,93},{2,8320,12},{2,5495,56}};
    MovieRentingSystem* m = new MovieRentingSystem(10,x);

    cout << "fine" << endl;
    vector<int> query = m->search(7837);
    cout << "\nSearch Results for movie 7837" << endl;
    for(int i = 0; i<query.size(); i++){
        cout << query[i] << " ";
    }
    cout << endl;
    
    cout << "fine" << endl;
    vector<int> query2 = m->search(5495);
    cout <<"\nSearch Results for movie 5495" << endl;
    for(int i = 0; i<query2.size(); i++){
        cout << query2[i] << " ";
    }
    cout << endl;
    
    m->rent(4,7100);

    vector<int> query3 = m->search(9105);
    cout << "\nSearch Results for movie 9105" << endl;
    for(int i = 0; i<query3.size(); i++){
        cout << query3[i] << " ";
    }
    cout << endl;

    vector<int> query4 = m->search(1446);
    cout << "\nSearch Results for movie 1446" << endl;
    for(int i = 0; i<query4.size(); i++){
        cout << query4[i] << " ";
    }
    cout << endl;
    
    
    
    vector<vector<int>> result2 = m->report();
    cout << "\n ------- Report ---------" << endl;
    for(int i = 0; i < result2.size(); i++){
        cout << "{" << result2[i][0] <<"," << result2[i][1] << "} ";
    }
    cout << endl;
    

    vector<int> query5 = m->search(9869);
    cout << "\nSearch Results for movie 9869" << endl;
    for(int i = 0; i<query5.size(); i++){
        cout << query5[i] << " ";
    }
    cout << endl;

    m->drop(4,7100);


}

int main(){
    test();
    return 0;
}