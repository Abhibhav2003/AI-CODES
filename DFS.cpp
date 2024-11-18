#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>createList()
{   int nums;
    cout<<"Enter Number of Nodes : ";
    cin>>nums;
    int i=0 , neighbor;
    vector<vector<int>>list(nums);

   for(int i=0 ; i < nums ; i++)
   {
    cout<<"Enter Node "<<i<<": ";
    while(true)
    {
    cin>>neighbor;

    if(neighbor == -1)
    {
        break;
    }
    list[i].push_back(neighbor);
    }
   }
   return list;
}

void DFS(vector<vector<int>>&graph , int start)
{
    stack<int>st;
    vector<bool>visited(graph.size(),false);
    st.push(start);
    
    while(!st.empty())
    {
       int node = st.top();
       cout<<node<<" ";
       visited[node] = true;
       st.pop();

       for(auto neighbor : graph[node])
       {
           if(!visited[neighbor])
           st.push(neighbor);
       }
    }
}

int main()
{
    vector<vector<int>>graph = createList();

    DFS(graph,0);
}