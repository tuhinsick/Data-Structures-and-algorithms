#include<bits/stdc++.h>
using namespace std;

const int N = 100;
#define INF (1e9+10)
#define iPair pair<int,int>
vector<iPair> graph[N];

vector<int> dijkstra(int source){
    vector<int> dist(N,INF);
    dist[source] = 0;
    priority_queue<iPair,vector<iPair>,greater<iPair>> pq;
    pq.push({0,source});
    while(!pq.empty()){
        auto u = pq.top().second;
        pq.pop();
        for(auto child : graph[u]){
            int w = child.second;
            int v = child.first;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v],v});
            }
        }
    }

    return dist;
}

int main(){
    freopen("in.txt","r",stdin);
    int n,m,threshold;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }

    cin>>threshold;
    vector<iPair> city;
    for(int i=1;i<=n;i++){
        int count = 0;
        auto dist = dijkstra(i);
        for(auto distance : dist){
            if(distance <= threshold){
                count++;
            }
        }
        city.push_back({count,i});

    }

    sort(city.begin(),city.end());
    for(auto cities : city){
        if(cities.first == city[0].first){
            cout<<cities.second<<" ";
        }

        else{
            break;
        }
    }

    return 0;
}