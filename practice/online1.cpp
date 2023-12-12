#include<bits/stdc++.h>
using namespace std;

// dijkstra algorithm is a type of greedy algorithm...

const int N = 1e5+10;
const int INF = 1e9+10;
vector<int> dist(N,INF);
#define iPair pair<int,int>

vector<iPair> g[N]; // how to store weighted graph...
vector<int> parent(N,INF);

void dijkstra(int source){

    priority_queue<iPair,vector<iPair>,greater<iPair>> pq;
    dist[source] = 0;
    pq.push({0,source});
    while(!pq.empty()){
        int v = pq.top().second;
        pq.pop();
        for(auto x : g[v]){
            int child_v = x.first;
            int wt = x.second;
            if(dist[child_v] > dist[v] + wt){
                dist[child_v] = dist[v] + wt;
                pq.push({dist[child_v],child_v});
                parent[child_v] = v;
            }
        }

    }


}


int main(){
    freopen("in.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        g[x].push_back({y,w});
    }

    int source;
    cin>>source;
    dijkstra(source);
    cout<<"dijkstra"<<endl;
    vector<int> fromFarhan(n+1);
    for(int i=0;i<n;i++){
        fromFarhan[i] = dist[i];
    }
    dist.assign(N,INF);
    int minDis = INF, minVertex=-1;
    for(int i=0;i<n;i++){
        if(i == source){
            continue;
        }
        dijkstra(i);
        cout<<"calling dijkstra "<<i<<endl;
        if(dist[source]+fromFarhan[i] < minDis){
            minDis = fromFarhan[i]+dist[source];
            minVertex = i;
        }
        dist.assign(N,INF);
    }

    cout<<minDis<<" "<<minVertex<<endl;
    dist.assign(N,INF);
    dijkstra(source);

    stack<int> path1;
    int i = minVertex;

    while(i != source){
        path1.push(i);
        i = parent[i];
    }

    cout<<"printing path1 : ";
    cout<<source<<"->";
    while(!path1.empty()){
        cout<<path1.top();
        path1.pop();
        if(!path1.empty()){
            cout<<"->";
        }
    }
    cout<<" time : "<<dist[minVertex];
    cout<<endl;

    dist.assign(N,INF);
    dijkstra(minVertex);

    while(i != minVertex){
        path1.push(i);
        i = parent[i];
    }

    cout<<"printing path2 : ";
    cout<<minVertex<<"->";
    while(!path1.empty()){
        cout<<path1.top();
        path1.pop();
         if(!path1.empty()){
            cout<<"->";
        }
    }

    cout<<" time : "<<dist[source]<<endl;


    return 0;
}