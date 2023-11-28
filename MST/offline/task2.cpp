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

    //kruskal's algorithm
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
