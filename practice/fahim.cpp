#include <bits/stdc++.h>

using namespace std;

#define MAX 100

int fcost[MAX];
vector<pair<int, int>> edges[MAX];

void DFS(int current, bool visited[], int capacity, int src, int dest, int last, int cost, int &min)
{
    visited[src] = true;
    if (src == dest)
    {
        cost = cost - current * fcost[last];
        if (min > cost)
            min = cost;
    }
    else
    {
        if(fcost[src]<fcost[last])
        {
            cost=cost-current*fcost[last];
            current=0;
        }
        for (int i = 0; i < edges[src].size(); i++)
        {
            pair<int, int> neighbour = edges[src][i];
            if (!visited[neighbour.first])
            {
                if (fcost[neighbour.first] > fcost[src])
                {
                    DFS(capacity - neighbour.second, visited, capacity, neighbour.first, dest, src, cost + (capacity - current) * fcost[src], min);
                }
                else
                {
                    int req = neighbour.second - current;
                    if (req > 0)
                    {
                        DFS(0, visited, capacity, neighbour.first, dest, src, cost + req * fcost[src], min);
                    }
                    else
                    {
                        DFS(current - neighbour.second, visited, capacity, neighbour.first, dest, last, cost, min);
                    }
                }
            }
        }
    }
    visited[src] = false;
    return;
}

int main()
{
    freopen("in.txt","r",stdin);
    int n, m, c;
    cin >> n >> m >> c;
    fcost[0]=INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cin >> fcost[i + 1];
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if(w>c)
        continue;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }
    int src, dest;
    cin >> src >> dest;
    bool visited[n+1];
    memset(visited,false,sizeof(visited));
    int min=INT_MAX;
    DFS(0,visited,c,src,dest,0,0,min);
    if(min==INT_MAX)
    cout<<"impossible"<<endl;
    else
    cout<<min<<endl;
}