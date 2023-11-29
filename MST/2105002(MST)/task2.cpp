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

    vector<int> edge_states(m,0);

    for(auto child : result){
        for(auto childs : child){
            for(int i=0;i<m;i++){
                if(childs == edges[i]){
                    edge_states[i]++;
                    break;
                }
            }
        }
    }

    for(auto edge : edge_states){
        if(edge == 0){
            cout<<"none"<<endl;
        }

        else if(edge == result.size()){
            cout<<"any"<<endl;
        }

        else{
            cout<<"at least one"<<endl;
        }
    }

    fclose(stdin);

}
