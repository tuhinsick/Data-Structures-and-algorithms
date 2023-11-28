#include "header.h"


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
    for(auto edge : edges){
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if(find(u) != find(v)){
            union_set(u,v);
            total += wt;
        }
    }
    set<vector<pair<int,pair<int,int>>>> ans = combinations(n-1,total,edges);
    set<vector<pair<int,pair<int,int>>>> result = AllMST(ans);
    count = 0;
    cout<<"MSTs"<<endl;
    for(auto child : result){
        count++;
        cout<<"MST "<<count<<" : [ ";
        for(auto childs : child){
            cout<<"["<<childs.second.first<<","<<childs.second.second<<","<<childs.first<<"] ";
        }
        cout<<"]"<<endl;
    }

    fclose(stdin);

}
