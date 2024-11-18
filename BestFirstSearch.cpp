#include<bits/stdc++.h>
using namespace std;

// Informed Search :-

struct Compare 
{
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.first > b.first; 
    }
};

vector<int> BestFirstSearch(vector<vector<int>>&graph,  int start , int goal , vector<int>&heuristic)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> open;
    open.push({heuristic[start],start});
    vector<bool> visited(graph.size(), false);
    vector<int>path;

    while(!open.empty())
    {
       int node = open.top().second;

       visited[node] = true;

       open.pop();

       path.push_back(node);

       if(node == goal)
       {
         cout << "Goal node found" << endl;
         return path;
       }
       else if(graph[node].empty())
       {
          path.clear();
          path.push_back(start);
       }
       else
       {
        for(auto neighbor : graph[node])
        {
            if(!visited[neighbor])
            {
                open.push({heuristic[neighbor],neighbor});
            }
        }
       }
    }   
    cout<<"Goal node not found"<<endl;
    return {};
}

int main()
{
    vector<int>heuristic = {10,8,5,7,3,4,0};
    vector<vector<int>>graph = {{1, 2}, {3, 4}, {5}, {}, {6}, {}, {}};
    int g,s;
    cout<<"Enter Start Node: ";
    cin>>s;
    cout<<"Enter Goal Node: ";
    cin>>g;
    vector<int>path = BestFirstSearch(graph,s,g,heuristic);

    if(!path.empty()) 
    {   
    for(auto i : path)
    {
        cout<<i<<" ";
    }
    }
    return 0;
}