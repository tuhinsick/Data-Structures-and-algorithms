#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
vector<int> parent(N);
vector<int> size(N,0);

void make_set(int v){
    size[v] = 1;
    parent[v] = v;
}

int find_set(int a){
    if(a = parent[a]){
        return a;
    }

    return parent[a] = find_set(parent[a]);
}

void union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a!=b){
        if(size[a] < size[b]){
            swap(a,b);
        }

        parent[b] = a;
        size[a]+=size[b];
    }
}

int main() {

}