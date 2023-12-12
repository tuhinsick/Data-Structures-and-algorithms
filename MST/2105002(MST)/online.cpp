#include "header.h"


int main(){

    freopen("in.txt","r",stdin);
    int n,m;
    cin>>n>>m;

    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<m;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back({wt,{u,v}});
    }

    int total = MST_weight(n,edges);
    set<vector<pair<int,pair<int,int>>>> ans = combinations(n-1,total,edges);
    set<vector<pair<int,pair<int,int>>>> result = AllMST(ans);
    
    int product = 1;
    for(auto edge_container : result) {
        int cnt = 1;
        for(auto edges : edge_container){
            cnt *= edges.first;
        }

        if(cnt>product){
            product = cnt;
        }
    }

    cout<<product<<endl;
}