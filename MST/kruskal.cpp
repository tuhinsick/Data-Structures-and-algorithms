#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
vector<int> parent(N);
vector<int> size(N,0);

void make_set(int v){
    size[v] = 1;
    parent[v] = v;
}

int find_set(int a){
    if(a = parent[a]){
        return a;
    }

    return parent[a] = find_set(parent[a]);
}

void union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a!=b){
        if(size[a] < size[b]){
            swap(a,b);
        }

        parent[b] = a;
        size[a]+=size[b];
    }
}

int main() {
    freopen("in.txt","r",stdin);
    int n,m;
    vector<pair<int,pair<int,int>>> edges;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        make_set(i);
    }

    for(int i=0;i<m;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back({wt,{u,v}});
    }

    sort(edges.begin(), edges.end());
    int total = 0;
    for(auto& edge :edges){
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if(find_set(u) != find_set(v)){
            union_set(u,v);
            total += wt;
            cout<<u<<" "<<v<<endl;
        }
    }

    cout<<total<<endl;

}