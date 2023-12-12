#include <bits/stdc++.h>
using namespace std;

const int N = 100;
const int INF = 1e9 + 10;
#define iPair pair<int, int>

vector<pair<int, iPair>> g[N][N];  // first N denotes the vertex no and second N 
// represents the remaining fuel...

int dist[N][N];  // same first N represents the vertex and second N represents 
// the remaining fuel...

void dijkstra(iPair source)
{
    priority_queue<pair<int, iPair>, vector<pair<int, iPair>>, greater<pair<int, iPair>>> pq;
    dist[source.first][source.second] = 0;
    pq.push({0, source});  // the first element is the distance and the second element is the 
    // pair -- first : vertex and second : remaining fuel
    while (!pq.empty())
    {
        auto  v = pq.top();
        pq.pop();
        for (auto vertices : g[v.second.first][v.second.second])
        {
            int wt = vertices.first;
            int u = vertices.second.first;
            int vw = vertices.second.second;
            if (dist[u][vw] > dist[v.second.first][v.second.second] + wt)
            {
                dist[u][vw] = v.first + wt;
                pq.push({dist[u][vw], {u, vw}});
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    for (int i = 1; i < N; i++)
    {
        for(int j = 0; j < N; j++){
            dist[i][j] = INF;
        }
    }

    int n, m, c;
    cin >> n >> m >> c;
    vector<int> weights;
    for (int i = 0; i < n; i++)
    {
        int wt;
        cin >> wt;
        weights.push_back(wt);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= c; j++)
        {
            for (int k = j + 1; k <= c; k++)
            {
                int wt = weights[i - 1] * (k - j);// i= vertex j = current fuel
                g[i][j].push_back({wt, {i, k}});// wt = weight // i = vertex // k = current fuel
                
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        if (wt > c)
        {
            continue;
        }

        for (int j = 0; j <= c; j++)
        {
            for (int k = 0; k <= c; k++)

            {
                if(wt+k > c){
                    continue;  // u theke v te jaoar path + v te pouchar por remaining fuel capacity theke beshi
                    // hole ei case ignore krbo 
                }
                 if (wt + k - j < 0)
                {
                    // negative gulao ignore krbo
                    continue;
                }

                else
                {
                    g[u][j].push_back({(wt + k - j) * weights[u - 1], {v, k}});
                }
            }
        }
    }

    int s, d;
    cin >> s >> d;
    dijkstra({s, 0});
    int min = INF;
    min = dist[d][0];
    if (min == INF)
    {
        cout << "impossible" << endl;
        return 0;
    }

    else{
        cout<<"minimum distance is : "<<min<<endl;
    }
    return 0;
}
