#include<bits/stdc++.h>
using namespace std;

#define INF 1e9+10
vector<pair<int,pair<int,int>>> edges;
int main(){
    freopen("in.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y,wt;
        cin>>x>>y>>wt;
        edges.push_back({wt,{x,y}});
    }
    // int node_a, node_b,s,d, L,H;
    // cin>>node_a>>node_b;
    // cin>>L>>H;
    int s,d;
    cin>>s>>d;
    vector<int>dist(n+1,INF);
    dist[s] = 0;
    bool x = true;
    for(int i=0;i<n-1;i++){
        for(auto edge : edges){
            int wt = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            if(dist[u]+wt<dist[v]){
                dist[v] = dist[u]+wt;  // relaxation
            }
        }
    }

     for(auto edge : edges){
            int wt = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            if(dist[u]+wt<dist[v]){
                x = false;
                cout<<"negative cycle detected "<<endl;
                break;
                dist[v] = dist[u]+wt;
            }
        }
        if(x && dist[d] != INF){
            cout<<dist[d]<<endl;
        }
}