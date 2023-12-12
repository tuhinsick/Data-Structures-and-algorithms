#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> parent(N), sz(N, 0);

// jotogula edge dibo shobgular weight ber kore dibe
int weight(vector<pair<int, pair<int, int>>> childs)
{
    int wt = 0;
    for (auto child : childs)
    {
        wt += child.first;
    }

    return wt;
}

void help(int i, int k, vector<pair<int, pair<int, int>>> subSet, vector<pair<int, pair<int, int>>> edges, set<vector<pair<int, pair<int, int>>>> &ans)
{
    if (k == 0)
    {
        ans.insert(subSet);
    }

    if (i >= edges.size())
    {
        return;
    }

    subSet.push_back(edges[i]);
    help(i + 1, k - 1, subSet, edges, ans);
    subSet.pop_back();
    help(i + 1, k, subSet, edges, ans);
}

// combinations function call korle ans vector dibe jetar
//  moddhe tarai thakbe jader total edge weight mst er shoman but era
//  cycle form korte pare
set<vector<pair<int, pair<int, int>>>> combinations(int n, int total, vector<pair<int, pair<int, int>>> edges)
{
    vector<pair<int, pair<int, int>>> subSet;
    set<vector<pair<int, pair<int, int>>>> ans;
    set<vector<pair<int, pair<int, int>>>> result;
    help(0, n, subSet, edges, ans);
   // int count = 0;
    for (auto child : ans)
    {
        int wt = weight(child);
        if (wt > total)
            continue;
        result.insert(child);
    }

    return result;
}

void make(int v)
{
    parent[v] = v;
    sz[v] = 1;
}

int find(int v)
{
    if (v == parent[v])
    {
        return v;
    }

    return parent[v] = find(parent[v]);
}

void union_set(int u, int v)
{
    u = find(u);
    v = find(v);
    if (u != v)
    {
        if (sz[u] < sz[v])
        {
            swap(u, v);
        }

        parent[v] = u;
        sz[u] += sz[v];
    }
}

// edge gula theke mst find out korbe and then weight ber kore dibe basically
//  eta holo kruskal algorithm

int MST_weight(int n,vector<pair<int, pair<int, int>>> edges)
{
    for (int i = 0; i < n; i++)
    {
        make(i);
    }

    sort(edges.begin(), edges.end());
    int total = 0;
    for (auto edge : edges)
    {
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if (find(u) != find(v))
        {
            union_set(u, v);
            total += wt;
        }
    }

    return total;
}

// Allmst function call korle khali mst gula pabo

set<vector<pair<int, pair<int, int>>>> AllMST(set<vector<pair<int, pair<int, int>>>> ans)
{
    set<vector<pair<int, pair<int, int>>>> result;
    for (auto child : ans)
    {
        for (auto childs : child)
        {
            int u = childs.second.first;
            int v = childs.second.second;
            make(u);
            make(v);
        }
        bool x = true;
        for (auto childs : child)
        {
            int u = childs.second.first;
            int v = childs.second.second;
            if (find(u) != find(v))
            {
                union_set(u, v);
            }
            else
            {
                x = false;
            }
        }

        if (x)
        {
            result.insert(child);
        }
    }

    return result;
}

int main(){
    //freopen("in.txt","r",stdin);
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
