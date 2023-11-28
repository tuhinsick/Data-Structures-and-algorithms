#include<bits/stdc++.h>
using namespace std;

void help(int i,int n, int k, vector<int> subSet, vector<vector<int>> &ans){
    if(k == 0){
        ans.push_back(subSet);
        return;
    }

    if(i>n){
        return;
    }

    subSet.push_back(i);
    help(i+1,n,k-1,subSet,ans);
    subSet.pop_back();
    help(i+1,n,k,subSet,ans);
    
}

void combinations(int n){
    vector<int> subSet;
    vector<vector<int>> ans;
    help(1,n,2,subSet,ans);
    for(auto child : ans){
        for(auto x : child){
            cout<<x<<" ";
        }

        cout<<endl;
    }

}

int main(){
    int n;
    cin>>n;
    combinations(n);

    return 0;
}