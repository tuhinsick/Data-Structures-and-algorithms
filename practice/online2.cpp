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
    int n1,m1,n2,m2;
    cin>>n1>>m1>>n2>>m2;
    int m = m1+m2;
    vector<pair<string,int>> firstComp;
    vector<pair<string,int>> secondComp;
    for(int i=0;i<m;i++){
        string s1,s2;
        int w;
        cin>>s1>>s2>>w;
        dist[s1] = INF;
        dist[s2] = INF;
        graph[s1].push_back({s2,w});
        graph[s2].push_back({s1,w});
    }


    int p1,p2;
    cin>>p1;
    for(int i=0;i<p1;i++){
        string s;
        int w;
        cin>>s>>w;
        firstComp.push_back({s,w});
    }
    cin>>p2;

    for(int i=0;i<p2;i++){
        string s;
        int w;
        cin>>s>>w;
        secondComp.push_back({s,w});
    }

    for(auto f : firstComp){
        for(auto s : secondComp){
            int w = f.second + s.second;
            string s1 = f.first;
            string s2 = s.first;
            graph[s1].push_back({s2,w});
            graph[s2].push_back({s1,w});

        }
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
        cout<<st.top()<<" ";
        st.pop();
    }

}