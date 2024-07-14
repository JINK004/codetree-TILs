#include <iostream>
#include <unordered_map>
using namespace std;

int cnt = 0;
int n = 0;
unordered_map<int, int> m[4];

void ADD(int lv, int sum) {
    if (lv != 3) {
        for (int i = 0; i < n; i++) {
            ADD(lv+1, sum + m[lv][i]);
        }
    }
    else {
        int num = -sum;
        if (m[3].find(num) != m[3].end()) cnt++;
        return;
    }

    return;
}


int main() {
    int N;
    cin >> N;
    n = N;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        m[3][tmp] = i;
    }
    ADD(0, 0);
    cout << cnt;

    return 0;
}