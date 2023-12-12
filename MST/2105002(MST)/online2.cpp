#include "header.h"

int main(){
    freopen("in.txt","r",stdin);
    int n,m;
    double q;
    cin>>n>>m>>q;

    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<m;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back({wt,{u,v}});
    }

    double total = MST_weight(n,edges,q);
    cout<<total<<endl;
}