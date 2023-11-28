#include "header.h"

int main(){

    freopen("in.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        make(i);
    }
    vector<pair<int,pair<int,int>>> stored_edges;
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<m;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back({wt,{u,v}});
    }
    stored_edges = edges;

    sort(edges.begin(), edges.end());

    int total = 0;
    for(auto edge : edges){
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if(find(u) != find(v)){
            union_set(u,v);
            total += wt;
        }
    }
    
    //combinations function call korle ans vector dibe jetar 
    // moddhe tarai thakbe jader total edge weight mst er shoman but era
    // cycle form korte pare
    set<vector<pair<int,pair<int,int>>>> ans = combinations(n-1,total,edges);
    // Allmst function call korle khali mst gula pabo
    set<vector<pair<int,pair<int,int>>>> result = AllMST(ans);
    vector<int> edge_states(m,0);

    for(auto child : result){
        for(auto childs : child){
            for(int i=0;i<m;i++){
                if(childs == stored_edges[i]){
                    edge_states[i]++;
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
