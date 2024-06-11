#include <iostream>
#include<unordered_map>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    unordered_map<int, int> map;
    int cnt = 0;
    for (int i=0;i<n;i++){
        int tmp;
        cin >> tmp;
        if(map.find(k-tmp) != map.end()) cnt++;
        map[tmp] = i+1;
    }
    cout << cnt;   
    return 0;
}