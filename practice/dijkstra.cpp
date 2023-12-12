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
        g[y].push_back({x,w});
    }

    int source;
    cin>>source;
    dijkstra(source);


    for(int i=1;i<n;i++){
        cout<<"printing : 0 to "<<i<<" : "<<dist[i]<<" path : ";
        int j = i;
        stack<int> st;
        st.push(j);
        while(parent[j]!=INF){
            j = parent[j];
            st.push(j);
        } 

        while(!st.empty()){
            cout<<st.top()<<" ";
            st.pop();
        }

        cout<<endl;
    }

    return 0;
}