#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;


class Twitter {
private:
    class User{
    public:
        int userid;
        unordered_set<int> followers;
        unordered_set<int> following;
        vector<pair<int,int>> tweets; // {tweetid, timestamp}
        int idx;
 
        User(int userid): userid(userid), idx(0){}
    };

    unordered_map<int,User*> usersdb;
    int timestamp;

public:
    Twitter(): timestamp(0) {
        
    }
    
    void postTweet(int userId, int tweetId) {
        if(usersdb.find(userId) == usersdb.end()){
            usersdb[userId] = new User(userId);
        }
        usersdb[userId]->tweets.push_back({tweetId, timestamp});
        timestamp++;
    }
    
    vector<int> getNewsFeed(int userId) {
        // Create user if they dont exist yet
        if(usersdb.find(userId) == usersdb.end()){
            usersdb[userId] = new User(userId);
        }

        // Create a heap to get the news feed for this user
        auto compare = [](vector<int> a, vector<int> b){ // {userid, tweetid, timestamp}
            return a[2] < b[2];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> pq(compare);
        unordered_map<int,int> indices;
        
        // Push the recent tweets of all the users in the following list of this user
        User* thisUser = usersdb[userId];
        indices[userId] = 0;
        if(indices[userId] < thisUser->tweets.size())pq.push({userId,thisUser->tweets.back().first,thisUser->tweets.back().second});
        for(int user : usersdb[userId]->following){
            indices[user] = 0;
            if(indices[user] < usersdb[user]->tweets.size()) pq.push({user, usersdb[user]->tweets.back().first, usersdb[user]->tweets.back().second});
        }

        // Get the top 10 tweets for the news feed
        vector<int> feed;
        while(!pq.empty() && feed.size()<10){
            vector<int> topTweet = pq.top();
            pq.pop();
            // Add this tweetid to the result;
            feed.push_back(topTweet[1]);
            vector<pair<int,int>> &tweetsqueue = usersdb[topTweet[0]]->tweets;
            indices[topTweet[0]]++;
            // Make sure nextTweet is within bounds
            if(indices[topTweet[0]] < tweetsqueue.size()){
                pair<int,int> nextTweet = tweetsqueue[tweetsqueue.size()-1-indices[topTweet[0]]]; // {tweetid, timestamp}
                pq.push({topTweet[0],nextTweet.first,nextTweet.second});
            }
        }

        return feed;

    }
    
    void follow(int followerId, int followeeId) {
        if(usersdb.find(followerId) == usersdb.end()){
            usersdb[followerId] = new User(followerId);
        }
        if(usersdb.find(followeeId) == usersdb.end()){
            usersdb[followeeId] = new User(followeeId);
        }

        User* follower = usersdb[followerId] ;
        User* followee = usersdb[followeeId] ;

        follower->following.insert(followeeId);
        followee->followers.insert(followerId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if(usersdb.find(followerId) == usersdb.end()){
            usersdb[followerId] = new User(followerId);
        }
        if(usersdb.find(followeeId) == usersdb.end()){
            usersdb[followeeId] = new User(followeeId);
        }

        User* follower = usersdb[followerId] ;
        User* followee = usersdb[followeeId] ;

        follower->following.erase(followeeId);
        followee->followers.erase(followerId);
    }
};


/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
void display(vector<int> a){
    for(auto i: a){
        cout << i << " ";
    }
    cout << endl;
}
void test(){
    Twitter twitter;
    twitter.postTweet(1,5);
    display(twitter.getNewsFeed(1));
    twitter.follow(1,2);
    twitter.postTweet(2,6);
    display(twitter.getNewsFeed(1));
    twitter.unfollow(1,2);
    display(twitter.getNewsFeed(1));
    
}

void test2(){
    Twitter twitter;
    twitter.postTweet(1,1);
    display(twitter.getNewsFeed(1));

    twitter.follow(2,1);

    display(twitter.getNewsFeed(2));

    twitter.unfollow(2,1);
    display(twitter.getNewsFeed(2));


}

int main(){
    test2();
    return 0;
}


