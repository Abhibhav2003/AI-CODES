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
void BFS(vector<vector<int>>&graph , int start)
{
    queue<int>q;
    vector<bool>visited(graph.size(),false);
    q.push(start);

    while(!q.empty())
    {
        int node = q.front();
        visited[node] = true;
        cout<<node<<" ";
        q.pop();

        for(auto neighbor : graph[node])
        {
            if(!visited[neighbor])
            {
                q.push(neighbor);
            }
            else
            break;
        }

    }
}

int main()
{
    vector<vector<int>>graph = createList();
    BFS(graph,0);

    return 0;
}
