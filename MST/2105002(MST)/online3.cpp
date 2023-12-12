#include "header.h"

int main(){
    freopen("in.txt","r",stdin);
    vector<pair<int,int>> v;
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        int x,y;
        cin>>x>>y;
        v.push_back({x,y});
    }

    vector<pair<int,pair<int,int>>> edges;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i == j){
                continue;
            }
            int wt = abs(v[i].first - v[j].first) + abs(v[j].second - v[i].second);
            //cout<<wt<<endl;
            edges.push_back({wt,{i,j}});
        }
    }

    int total = MST_weight(n,edges);

    cout<<total<<endl;
}