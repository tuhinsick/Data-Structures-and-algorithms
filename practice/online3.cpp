#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9+10;

unordered_map<string, vector<pair<string,int>>> graph;
unordered_map<string,int> dist;
unordered_map<string,string> parent;
void dijkstra(string source){
    dist[source] = 0;
    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> pq;
    pq.push({0,source});
    while(!pq.empty()){
        auto v = pq.top();
        pq.pop();
        for(auto child : graph[v.second]){
            int wt = child.second;
            string child_v = child.first;
            if(dist[child_v] > dist[v.second] + wt){
                dist[child_v] = dist[v.second] + wt;
                parent[child_v] = v.second;
                pq.push({dist[child_v],child_v});
            }
        }
    }
}

int main(){
    freopen("in.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    unordered_map<string,int> cost;
    for(int i=0;i<n;i++){
        string s;
        int w;
        cin>>s>>w;
        cost[s] = w;
    }
    for(int i=0;i<m;i++){
        string s1,s2;
        int w;
        cin>>s1>>s2>>w;
        dist[s1] = INF;
        dist[s2] = INF;
        graph[s1].push_back({s2,w+cost[s2]});
        graph[s2].push_back({s1,w+cost[s1]});
    }
    string source,dest;
    cin>>source>>dest;
    dijkstra(source);
    cout<<dist[dest]<<endl;
    stack<string> st;
    st.push(dest);
    while(dest != source){
        dest = parent[dest];
        st.push(dest);
    }

    while(!st.empty()){
        cout<<st.top();
        st.pop();
        if(!st.empty()){
            cout<<"->";
        }
    }

}