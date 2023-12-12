#include "head.h"


int main(){
    freopen("in.txt","r",stdin);
    vector<pair<int,pair<int,int>>> graph;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++) {
        int x,y,w;
        cin>>x>>y>>w;
        graph.push_back({w,{x,y}});
    }
    int total = MST_weight(n,graph);
    set<vector<pair<int,pair<int,int>>>> ans = combinations(n-1,total,graph);
    ans = AllMST(ans);
    int a,b;
    cin>>a>>b;
    for(auto edges : ans){
        for(auto edge : edges){
            int x = edge.second.first;
            int y = edge.second.second;
            if(a == x && b == y) {
                cout<<"true";
                return 0 ;
            }
        }
    }

    cout<<"false";
    
}