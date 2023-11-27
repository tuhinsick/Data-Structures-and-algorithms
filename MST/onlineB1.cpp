#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<int> parent1(N), parent2(N), sz1(N), sz2(N);
void make(int v)
{
    sz1[v] = 1;
    sz2[v] = 1;
    parent1[v] = v;
    parent2[v] = v;
}

int find1(int v)
{
    if (v == parent1[v])
    {
        return v;
    }

    return parent1[v] = find1(parent1[v]);
}

int find2(int v)
{
    if (v == parent2[v])
    {
        return v;
    }

    return parent2[v] = find2(parent2[v]);
}

void union1(int u, int v)
{
    u = find1(u);
    v = find1(v);

    if (u != v)
    {
        if (sz1[u] < sz2[v])
        {
            swap(u, v);
        }

        parent1[v] = u;
        sz1[u] += sz1[v];
    }
}

void union2(int u, int v)
{
    u = find2(u);
    v = find2(v);

    if (u != v)
    {
        if (sz2[u] < sz2[v])
        {
            swap(u, v);
        }

        parent2[v] = u;
        sz2[u] += sz2[v];
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        make(i);
    }

    vector<pair<int, pair<int, int>>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, {u, v}});
    }

    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());
    int cnt = 0, cnt1 = 0, cnt2 = 0;
    for (auto edge : edges)
    {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        //cout << u << " " << v << " " << w << endl;

        if (w == 3)
        {
            if (find1(u) != find1(v))
            {
                cnt++;
                union1(u, v);
                union2(u, v);
            }
        }
        else if (w == 1)
        {
            if (find1(u) != find1(v))
            {
                cnt1++;
                union1(u, v);
            }
        }
        else
        {
            if (find2(u) != find2(v))
            {
                cnt2++;
                union2(u, v);
            }
        }
    }
    cout << cnt << " " << cnt1 << " " << cnt2 << endl;
    if (cnt + cnt1 == n - 1 && cnt + cnt2 == n - 1)
    {
        cout << m - cnt - cnt1 - cnt2 << endl;
    }

    else
    {
        cout << -1 << endl;
    }

    return 0;
}