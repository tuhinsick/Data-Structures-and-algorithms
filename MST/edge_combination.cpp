#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
vector<int> parent(N),size(N,0);

int weight(vector<pair<int,pair<int,int>>> childs){
    int wt = 0;
    for(auto child : childs){
        wt += child.first;
    }

    return wt;
}

void help(int i, int k, vector<pair<int,pair<int,int>>> subSet,vector<pair<int,pair<int,int>>> edges,vector<vector<pair<int,pair<int,int>>>> &ans){
    if(k == 0){
        cout<<"inside k0"<<endl;
        ans.push_back(subSet);
    }

    if(i>=edges.size()){
        return;
    }
    

    subSet.push_back(edges[i]);
    help(i+1,k-1,subSet,edges,ans);
    subSet.pop_back();
    help(i+1,k,subSet,edges,ans);

}

void combinations(int n,int total, vector<pair<int,pair<int,int>>> edges){
    vector<pair<int,pair<int,int>>> subSet;
    vector<vector<pair<int,pair<int,int>>>> ans;
    help(0,n,subSet,edges,ans);
    cout<<ans.size()<<endl;
    int count = 0;
    for(auto child : ans){
        int wt = weight(child);
        if(wt>total) continue;
        count++;
        for(auto x : child){
            cout<<"["<<x.second.first<<","<<x.second.second<<","<<x.first<<"]";
        }

        cout<<endl;
    }

    cout<<count<<endl;
}



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
        size[u] += size[v];
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
    int count = 0;
    cout<<"Edges in MST"<<endl;
    for(auto edge : edges){
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if(find(u) != find(v)){
            union_set(u,v);
            cout<<"("<<u<<","<<v<<")"<<endl;
            total += wt;
            count++;
        }
    }
    cout<<count<<endl;
    cout<<total<<endl;

    cout<<"Calling combinations : "<<endl;
    combinations(count,total,edges);

    fclose(stdin);

}
