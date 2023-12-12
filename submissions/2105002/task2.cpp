#include<bits/stdc++.h>
using namespace std;

#define INF 1e9+10
#define iPair pair<int,int>

pair<bool,int> bellman_ford(vector<pair<int,iPair>> edges, int n,int source,int dest) {
    bool x = true;
    vector<int> dist(n+1,INF);
    dist[source] = 0;
    for(int i=0;i<n;i++){
        for(auto edge : edges) {
            int w = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            if(dist[v] > dist[u] + w){
                if(i == n-1){
                    x = false;
                }
                dist[v] = dist[u] + w;
            }
        }
    }

    return {x,dist[dest]};
}


int main(){
    freopen("in.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    vector<pair<int,iPair>> edges;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }

    int node_a,node_b, lower,higher,source,dest; 
    cin>>node_a>>node_b;
    cin>>lower>>higher>>source>>dest;

    int prior_dist = bellman_ford(edges,n,source,dest).second;

    for(int weight = lower; weight<=higher;weight++){
        edges.push_back({weight,{node_a,node_b}});
        pair<bool,int> x = bellman_ford(edges,n,source,dest);
        if(x.first && x.second < prior_dist) {
            cout<<weight<<" "<<x.second;
            return 0;
        }

        edges.pop_back();
    }

    cout<<"impossible"<<endl;
}