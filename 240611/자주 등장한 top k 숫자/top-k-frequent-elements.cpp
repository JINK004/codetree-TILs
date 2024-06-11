#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    unordered_map<int, int> map;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        map[tmp]++;
    }

    for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
        v.push_back({ it->second, it->first });
    }
    sort(v.begin(), v.end(), greater<>());
    for (int i = 0; i < k; i++) {
        cout << v[i].second << " ";
    }
    return 0;
}