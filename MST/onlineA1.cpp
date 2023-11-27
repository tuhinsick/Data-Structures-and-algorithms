#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
vector<int> parent(N),size(N,0);

void make(int v){
    parent[v] = v;
    size[v] = 1;
}

int find(int v){
    if(v == parent[v]){
        return v;
    }

    return parent[v] = find(parent[v]);
}


void union_set(int u, int v){
    u = find(u);
    v = find(v);
    if(u != v){
        if(size[u] < size[v]){
            swap(u,v);
        }

        parent[v] = u;
        size[u] += v;
    }
}
int main(){
    freopen("in.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        make(i);
    }

    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<m;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back({wt,{u,v}});
    }

    sort(edges.begin(), edges.end());
    int total = 0;
    cout<<"Edges in MST"<<endl;
    for(auto edge : edges){
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if(find(u) != find(v)){
            union_set(u,v);
            cout<<"("<<u<<","<<v<<")"<<endl;
            total += wt;
        }
    }

    cout<<total<<endl;

}