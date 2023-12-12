#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int city, litre, dis;
    node() {}
    node(int city, int litre, int dis)
    {
        this->city = city;
        this->litre = litre;
        this->dis = dis;
    }

    bool operator>(const node &s) const { return dis > s.dis; }
    bool operator<(const node &s) const { return dis < s.dis; }
};

class graph
{
    int vertices;
    // int edges;
    //  int cost;
    map<node, bool> isInShortestPath;
    vector<node> parent;

    map<node, vector<pair<node, int>>> adj; // for u, element of the adj list would be weight, v
    // priority_queue<pair<node, node>, vector<pair<node, node>>, greater<pair<node, node>>> pq; // weight, node
    priority_queue<node, vector<node>, greater<node>> pq;

    // vector<tuple<int, int, int>> result; // weight, node, parent;
    //  corresponding parent can be easily got from parent vector.

public:
    graph(int v) : vertices(v + 1), parent(v + 1)
    {
    }

    void addEdge(node u, node v, int cost)
    {
        adj[u].push_back({v, cost});
        // adj[v].push_back({weight, u});
    }

    void shortestPath(node root) // dijkstra algorithm
    {

        pq.push(root);

        while (!pq.empty())
        {
            // cout << "hello1 " << adj.size() << endl;
            node v = pq.top(); // weight, node
            pq.pop();

            if (isInShortestPath[v] == true) // once a node hase been poped out from the queue, its final distance has been calculated. it need not to be calculated further.
            {
                continue;
            }

            isInShortestPath[v] = 1;

            for (auto p : adj[v]) // v is a pair of ( node, weight)
            {
                int w = p.second;
                node u = p.first;
                if ((v.dis + w) < u.dis)
                {
                    u.dis = v.dis + w;
                    pq.push(u);
                    // cout << distance[v.second] << ' ' << weight << endl;
                    // pq.push({distance[v.second], v.second}); // Fix here
                    // parent[v.second] = node;
                }
            }
        }
    }

    // vector<int> getParent()
    // {
    //     return parent;
    // }

    // vector<int> getShortestDistance()
    // {
    //     return distance;
    // }

    // int getDistance(node n) const
    // {
    //     auto it = adj.find(n);
    //     if (it != adj.end())
    //     {
    //         return it->first.dis;
    //     }
    //     return -1; // If the node is not found

    int getDistance(node n) const
    {
        auto it = adj.find(n);
        if (it != adj.end())
        {
            return it->first.dis;
        }
        return -1; // If the node is not found
    }
    // }
};

int main()
{

    int n, m, c;
    cin >> n >> m >> c;

    int x, y, wt;
    graph g(n + 1);

    int gas[n];
    for (int i = 0; i < n; i++)
    {
        cin >> gas[i];
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < c; j++)
        {
            g.addEdge(node(i, j, INT_MAX), node(i, j + 1, INT_MAX), gas[i]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> wt;
        for (int j = wt; j <= c; j++)
        {
            g.addEdge(node(x, j, INT_MAX), node(y, j - wt, INT_MAX), 0);
        }
    }

    int source, destination;
    cin >> source >> destination;
    g.shortestPath(node(source, gas[source - 1], 0));

    node queryNode(destination, gas[destination - 1], 2);
    int distance = g.getDistance(queryNode);

    if (distance != -1)
    {
        cout << distance << endl;
    }
    else
    {
        cout << "City not found." << endl;

        return 0;
    }
}