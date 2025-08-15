#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;


class ThroneInheritance {
    private:
    class Node{
        public:
        string name;
        bool dead;
        vector<Node*> children;
        Node(): dead(false){};
        Node(string name): name(name), dead(false){};
    };

    public:
    string kingName;
    Node* king;
    unordered_map<string,ThroneInheritance::Node*> members;

    ThroneInheritance(string kingName): kingName(kingName){
        king = new Node(kingName);
        members.insert({kingName, king});
    }
    
    void birth(string parentName, string childName) {
        auto pair = members.find(parentName);
        if(pair == members.end()) return; // We don't have such parent
        Node* parent = pair->second;
        Node* n = new Node(childName);
        parent->children.push_back(n);
        members[childName]= n;
    }
    
    void death(string name) {
        auto pair = members.find(name);
        if(pair == members.end()) return;
        pair->second->dead = true;
    }
    
    // DFS
    vector<string> getInheritanceOrder() {
        vector<string> inheritanceOrder;
        if(!king->dead) inheritanceOrder.push_back(kingName);
        traverse(king,inheritanceOrder);
        return inheritanceOrder;
    }
    
    void traverse(Node* king, vector<string>& order){
        for(Node* child: king->children){
            if(!child->dead) order.push_back(child->name);
            traverse(child,order);
        }
    }

    ~ThroneInheritance(){
        for(auto pair: members){
            delete pair.second;
        }
    }


};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */

void test(){
    ThroneInheritance th("king");

    th.birth("king","andy");
    th.birth("king","bob");
    th.birth("king","catherine");
    th.birth("andy","matthew");
    th.birth("bob","alex");
    th.birth("bob","asha");

    
    vector<string> order =  th.getInheritanceOrder() ;


    for(auto s: order){
        cout << s << " ";
    }
    cout << endl;
    
    th.death("bob");
    
    vector<string> order2 =  th.getInheritanceOrder() ;


    for(auto s: order2){
        cout << s << " ";
    }
    cout << endl;
}

 int main(){
    test();
    return 0;
 }