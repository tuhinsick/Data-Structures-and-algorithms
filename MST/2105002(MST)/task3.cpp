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


    for(auto edge_container : result){
        for(auto edge : edge_container){
            for(int i=0;i<m;i++){
                if(edge == edges[i]){
                    edge_states[i]++;
                    break;
                }
            }
        }
    }

    vector<int> criticals;
    vector<int> pseudo;
    for(int i=0;i<m;i++){
        if(edge_states[i] == result.size()){
            criticals.push_back(i);
        }

        else if(edge_states[i] > 0){
            pseudo.push_back(i);
        }
    }
    cout<<"Critical edges : [ ";
    for(auto x : criticals){
        cout<<x<<" ";
    }
    cout<<"]"<<endl;
    cout<<"Pseudo edges : [ ";
    for(auto x : pseudo){
        cout<<x<<" ";
    }

    cout<<"]"<<endl;

    fclose(stdin);

}
