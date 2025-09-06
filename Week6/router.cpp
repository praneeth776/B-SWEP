#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;


class Router {
private:

    class Packet{
        public:
        int source;
        int destination;
        int timestamp;
        Packet(int source, int destination, int timestamp): source(source), destination(destination), timestamp(timestamp) {};

        bool operator==(const Packet& p) const{
            return this->source == p.source && this->destination == p.destination && this->timestamp == p.timestamp;
        }

        void display(){
            cout << this->source << " " << this->destination << " " << this->timestamp << endl;
        }
    };

// struct Hash{
//         size_t operator()(const Router::Packet& p)  {
//             return hash<int>{}(p.source) ^ hash<int>{}(p.destination << 1) ^ hash<int>{}(p.timestamp << 2) ;
//         }
//     };
    struct PacketHash{
        size_t operator()(const Packet &p) const {
            return hash<int>{}(p.source) ^ hash<int>{}(p.destination)<<1 ^ hash<int>{}(p.timestamp)<<2;
        }
    };

    // struct PairComparator{
    //     bool operator()(pair<int, int > a, pair<int,int> b){
    //         return a.second < b.second; // Compares the 
    //     }
    // };

    struct PairComparator{
        bool operator()(const pair<int,int> a, const pair<int,int> b) const{
            if(a.second == b.second) return a.first < b.first;
            return a.second < b.second;
        }
    };


    
    int memoryLimit;
    queue<Packet> q;
    unordered_set<Packet, PacketHash> packetSet;
    unordered_map<int,set<pair<int,int>, PairComparator>> packets;// Maps a destination to source,timestamps.
    public:
    /**
     * Initializes the Router object with a fixed memory limit.
     * memoryLimit is the maximum number of packets the router can store at any given time.
     * If adding a new packet would exceed this limit, the oldest packet must be removed to free up space.
     */
    Router(int memoryLimit): memoryLimit(memoryLimit) {
        
    }
    
    /**
     * A packet is considered a duplicate if another packet with the same source, destination, and timestamp already exists in the router.
     * Return true if the packet is successfully added (i.e., it is not a duplicate); otherwise return false.
     */
    bool addPacket(int source, int destination, int timestamp) {
        Packet p(source,destination,timestamp);
        auto &s = packets[destination];
        if(packetSet.find(p) != packetSet.end()) return false;

        if(q.size() == memoryLimit){
            forwardPacket();
        }
        // Add the new packet to the queue and packetSet
        q.push(p);
        packetSet.insert(p);

        packets[destination].insert({source,timestamp});
        return true;
    }
    
    /**
     * Remove the packet from storage.
     * Return the packet as an array [source, destination, timestamp].
     * If there are no packets to forward, return an empty array.
     */
    vector<int> forwardPacket() {
        vector<int> list;
        if(q.size() == 0) return list;

        Packet p = q.front();
        q.pop();
        packetSet.erase(p);
        packets[p.destination].erase({p.source,p.timestamp});

        list.push_back(p.source);
        list.push_back(p.destination);
        list.push_back(p.timestamp);
        return list;
    }
    
    /**
     * Returns the number of packets currently stored in the router (i.e., not yet forwarded) that have the 
     * specified destination and have timestamps in the inclusive range [startTime, endTime].
     * O(n) runtime
     */
    int getCount(int destination, int startTime, int endTime) {
        int count = 0;
        auto &s = packets[destination]; // A reference to the sorted set for all timestamps with this destination.
        // Binary search
        auto it1 = s.lower_bound({0,startTime}); // Added 0 because we have to pass pair<int,int> <source, timestamp> as an argument. 
        // The ordering is solely based on timestamo so the value of source wouldn't matter while searching. 
        // The source value is to keep track of multiple packets at the same timestamp and destination 
        auto it2 = s.upper_bound({200000,endTime});
        count = distance(it1,it2);
        return count;
    }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */

void test(){
    Router r(3);
    cout << r.addPacket(1,4,90) << " ";
    cout << r.addPacket(2,5,90) << " ";
    cout << r.addPacket(1,4,90) << " ";
    cout << r.addPacket(3,5,95) << " ";
    cout << r.addPacket(4,5,105) << " ";
    
    vector<int> p = r.forwardPacket();
    cout << p[0] << " " << p[1] << " " << p[2] << endl;
    
    cout << r.addPacket(5,2,110);
    cout << r.getCount(5,100,110) << endl;
}

int main(){
    test();
    return 0;
}