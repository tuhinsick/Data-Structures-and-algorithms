#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int src, dest, weight;
};

const int N = 1e5 + 10;

vector<int> parent(N), size(N, 0);
void make(int i)
{
    parent[i] = i;
    size[i] = 1;
}

int find(int u)
{
    if (u == parent[u])
    {
        return u;
    }

    return parent[u] = find(parent[u]);
}

void merge(int x, int y)
{
    int xRoot = find(x);
    int yRoot = find(y);

    if (xRoot != yRoot)
    {
        if (size[xRoot] < size[yRoot])
        {
            swap(xRoot, yRoot);
        }

        parent[yRoot] = xRoot;
        size[xRoot] += size[yRoot];
    }
}

int MST_weight(int n, vector<pair<int, pair<int, int>>> edges)
{
    // cout << "in mst" << endl;
    // cout<<edges.size()<<endl;
    for (int i = 0; i < n; i++)
    {
        make(i);
    }

    int total = 0;
    for (auto edge : edges)
    {

        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        //cout << u << " " << v << " " << wt << endl;
        if (find(u) != find(v))
        {
            merge(u, v);
            total += wt;
        }
    }

    return total;
}

int weight(vector<pair<int, pair<int, int>>> edges)
{
    int count = 0;
    for (auto child : edges)
    {
        count += child.first;
    }

    return count;
}

void totalCombinations(int index, int mstEdge, set<vector<pair<int, pair<int, int>>>> &combinations,
                       vector<pair<int, pair<int, int>>> &graph, vector<pair<int, pair<int, int>>> singleMST)
{
    if (mstEdge == 0)
    {
        combinations.insert(singleMST);
        return;
    }
    if (index >= graph.size())
    {
        return;
    }
    singleMST.push_back(graph[index]);
    totalCombinations(index + 1, mstEdge - 1, combinations, graph, singleMST);
    singleMST.pop_back();
    totalCombinations(index + 1, mstEdge, combinations, graph, singleMST);
}

void generateMSTs(const vector<Edge> &edges, int n)
{
    vector<pair<int, pair<int, int>>> graph;
    for (const auto &edge : edges)
    {
        graph.push_back({edge.weight, {edge.src, edge.dest}});
    }

    sort(graph.begin(), graph.end());

    int actual_weight = MST_weight(n, graph);
    //cout << actual_weight << endl;

    set<vector<pair<int, pair<int, int>>>> combinations;
    vector<pair<int, pair<int, int>>> singleMST;
    totalCombinations(0, n - 1, combinations, graph, singleMST);
    set<vector<pair<int, pair<int, int>>>> result;
    set<vector<pair<int, pair<int, int>>>> ans;
    for (auto child : combinations)
    {
        //cout << actual_weight << endl;
        if (weight(child) == actual_weight)
        {
            result.insert(child);
        }
    }

    for(auto edge_container : result){
        for(auto edge : edge_container){
            int u = edge.second.first;
            int v = edge.second.second;
            make(u);
            make(v);
        }

        bool x = true;
        for(auto edge : edge_container){
            int u = edge.second.first;
            int v = edge.second.second;
            if(find(u) == find(v)){
                x = false;
                break;
            }
            else{
                merge(u,v);
            }
        }

        if(x){
            ans.insert(edge_container);
        }
    }
    cout<<"MSTs : "<<endl;
    for(auto edges : ans){
        cout<<"[";
        for(auto edge : edges){
            cout<<"["<<edge.second.first<<","<<edge.second.second<<","<<edge.first<<"]";
        }
        cout<<"]"<<endl;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    generateMSTs(edges, n);

    return 0;
}
