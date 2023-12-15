#include<bits/stdc++.h>
using namespace std;

const int N = 100;
#define INF 1e9+10
int dist[N][N];

int main(){
    //freopen("in.txt","r",stdin); 
    int t;
    cin>>t;
    while(t--){
        for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i == j){
                dist[i][j] = 0;
            }

            else{
                dist[i][j] = INF;
            }
        }
    }
        string str;
        cin>>str;
        int ii = 0;
        for(int i=0;i<str.size();i++){
            if(str[i] == 'Y'){
                dist[ii][i] = 1;
            }
        }

        ii++;
        int len = str.size() - 1;
        for(int i=0;i<len;i++){
            cin>>str; 
            for(int j=0;j<=len;j++){
                if(str[j] == 'Y'){
                dist[ii][j] = 1;
            }
            }
            ii++;
        }

        //cout<<len<<endl;

        for(int k=0;k<=len;k++){ 
            for(int i=0;i<=len;i++){ 
                for(int j=0;j<=len;j++){ 
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

       priority_queue<pair<int,int>> pq; 
       for(int i=0;i<=len;i++){ 
        int count = 0;
        for(int j=0;j<=len;j++){ 
            if(dist[i][j] == 2){ 
                count++; 
            }
        }

        pq.push({count,i});
       }

       int vertex = pq.top().second; 
       int count = pq.top().first;
       pq.pop();
       while(count == pq.top().first){
        if(vertex > pq.top().second){
            vertex = pq.top().second;
            pq.pop();
        }
       } 
       cout<<vertex<<" "<<count<<endl;
    }
}