#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    unordered_map<string, int> map;
    unordered_map<int, string> mapint;
    for(int i=0;i<n;i++){
        string tmp;
        cin >> tmp;
        map[tmp] = i+1;
        mapint[i+1] = tmp;
    }
    for (int i=0;i<m;i++){
        string tmp;
        cin >> tmp;
        if (tmp[0] >= '0' && tmp[0] <='9'){
            int tmpint = stoi(tmp);
            cout << mapint[tmpint] << "\n";
        }
        else {
            cout << map[tmp] << "\n";
        }
    }
    return 0;
}