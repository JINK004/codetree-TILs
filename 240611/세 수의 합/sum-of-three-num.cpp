#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    unordered_map<int, int> map;
    int arr[1001];

    for (int i=0;i<n;i++){
        cin >> arr[i];
        if(map.count(arr[i])) map[arr[i]]++;
        else map[arr[i]] = 1;
    }

    int cnt = 0;
    for (int i=0;i<n;i++){
        map[arr[i]]--;
        for(int j=0;j<i;j++){
            if(map.count(k - arr[i] - arr[j]) > 0){
                cnt += map[k - arr[i] - arr[j]];
            }
        }
    }
    cout << cnt;

    return 0;
}