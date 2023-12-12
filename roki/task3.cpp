#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parent;

// Initialize the disjoint-set data structure
void disjoint(int size) {
    parent.resize(size + 1);
    for (int i = 0; i <= size; i++)
        parent[i] = i;
}

// Finding the representative of the disjoint-set containing 'u'
int find(int u) {
    if (parent[u] == u)
        return u;
    return parent[u] = find(parent[u]);
}

// Merge two disjoint-sets represented by 'u' and 'v'
void merge(int u, int v) {
    int ua = find(u);
    int ub = find(v);
    parent[ua] = ub;
}

// Function to find the minimum spanning tree (MST) weight
int help1(vector<vector<int>>& edges, int j, int n) {
    disjoint(n);
    vector<pair<int, pair<int, int>>> v;

    for (int i = 0; i < edges.size(); i++) {
        if (i == j)
            continue;
        v.push_back({edges[i][2], {edges[i][0], edges[i][1]}});
    }

    sort(v.begin(), v.end());

    int mst_weight = 0;
    int edgesCount = 0;

    for (int i = 0; i < v.size(); i++) {
        auto x = v[i];
        int u = find(x.second.first);
        int v = find(x.second.second);

        if (u != v) {
            edgesCount++;
            mst_weight += x.first;
            merge(u, v);
        }
    }

    if (edgesCount != n - 1)
        return INT_MAX;

    return mst_weight;
}

// Function to find MST weight after including one additional edge
int help2(vector<vector<int>>& edges, int j, int n) {
    disjoint(n);
    int mst_weight = edges[j][2];
    merge(edges[j][1], edges[j][0]);

    vector<pair<int, pair<int, int>>> v;
    for (int i = 0; i < edges.size(); i++) {
        if (i == j)
            continue;
        v.push_back({edges[i][2], {edges[i][0], edges[i][1]}});
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++) {
        auto x = v[i];
        int u = find(x.second.first);
        int v = find(x.second.second);

        if (u != v) {
            mst_weight += x.first;
            merge(u, v);
        }
    }
    return mst_weight;
}

// Function to determine critical and pseudo-critical edges
pair<vector<int>, vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
    disjoint(n);
    int mst_weight = help1(edges, -1, n);

    vector<int> criticalEdges;
    vector<int> pseudoCriticalEdges;

    for (int i = 0; i < edges.size(); i++) {
        int new_weight1 = help1(edges, i, n);
        int new_weight2 = help2(edges, i, n);

        if (new_weight1 > mst_weight) {
            criticalEdges.push_back(i);
        } else if (new_weight2 == mst_weight) {
            pseudoCriticalEdges.push_back(i);
        }
    }

    return {criticalEdges, pseudoCriticalEdges};
}

int main() {
    int vertices, edgesCount;
    cin >> vertices >> edgesCount;

    vector<vector<int>> edges(edgesCount);
    for (int i = 0; i < edgesCount; ++i) {
        int a, b, weight;
        cin >> a >> b >> weight;
        edges[i] = {a, b, weight};
    }

    pair<vector<int>, vector<int>> result = findCriticalAndPseudoCriticalEdges(vertices, edges);

    cout << "Critical edges : [";
    for (int i = 0; i < result.first.size(); ++i) {
        cout << result.first[i];
        if (i < result.first.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;

    cout << "Pseudo critical edges : [";
    for (int i = 0; i < result.second.size(); ++i) {
        cout << result.second[i];
        if (i < result.second.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;

    return 0;
}
