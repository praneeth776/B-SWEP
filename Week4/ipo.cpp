#include <vector>
#include <iostream>
#include <queue>

using namespace std;


class Project{
    public:
        int profit;
        int capital;
        Project(int profit, int capital): profit(profit), capital(capital){}
        Project(){}

        string display(){
            string result;
            result = "Project: profit: " + to_string(profit) + " capital: " + to_string(capital) ;
            return result;
        }
};

/**
 * You are given n projects where the ith project has a pure profit profits[i] and a minimum capital of capital[i] is needed to start it.
 * Initially, you have w capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.
 * Pick a list of at most k distinct projects from given projects to maximize your final capital, and return the final maximized capital.
 */
int solution(int k, int w, vector<int>& profits, vector<int>& capital){
    // Algorithm: Create a Project class with profit and capital as private variables. Sort these in ascending order by capital.
    // Have a priority queue, Keep adding from the sorted list if current total capital >= capital of the project

    // TO DO: Add to Reference Docs about this feature.
    auto compare = [](Project a, Project b){return a.profit < b.profit;}; // Lambda function for Priority queue

    vector<Project> projects(profits.size(),Project());
    priority_queue<Project,vector<Project>, decltype(compare)> pq(compare);

    for(int i = 0; i<profits.size(); i++){
        projects[i].capital = capital[i];
        projects[i].profit = profits[i];
    }

    sort(projects.begin(),projects.end(),[](Project a, Project b){return a.capital < b.capital;});

    // for(auto project: projects){
    //     cout << project.display() << endl; 
    // }

    // cout << pq.size() << endl;

    int total_profit = w;
    int num_projects = 0;
    int ptr = 0; // Keep track of which projects are added to pq

    while(num_projects < k){
        while(ptr < projects.size() && projects[ptr].capital <= total_profit){
            pq.push(projects[ptr]);
            // cout << "Pushed " << projects[ptr].display() << endl;
            ptr++;
        }
        if(pq.empty()) break;
        Project p = pq.top();
        total_profit += p.profit;
        // cout << "Popped " << p.display() << endl;
        pq.pop();
        num_projects++;
    }

    return total_profit;

}

void test(){
    vector<int> profits = {1,2,3};
    vector<int> capital = {1,1,2};
    cout << solution(1,0,profits,capital) << endl;
}

int main(){
    test();
    return 0;
}