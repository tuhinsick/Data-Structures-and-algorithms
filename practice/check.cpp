#include<bits/stdc++.h>
using namespace std;

#define iPair pair<int, int>

int main(){
    unordered_map<iPair,vector<iPair>> parent(100);
    parent[{2,3}].push_back({1,2});
    auto it = parent.find({2,3});
    for(auto value : it->second){
        cout<<value.first<<" "<<value.second<<endl;
    }

}