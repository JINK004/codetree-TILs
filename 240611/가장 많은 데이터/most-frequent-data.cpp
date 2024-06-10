#include <iostream>
#include <unordered_map>
using namespace std;

int main() {

    int n;
    cin >> n;
    int maxi = 0;
    unordered_map<string, int> m;
    for (int i=0;i<n;i++){
        string tmp;
        cin >> tmp;
        if(m.find(tmp) != m.end()){
            m[tmp]++;
        }
        else m[tmp]=1;
        if (m[tmp] > maxi) maxi = m[tmp];
    }
    cout << maxi;
    // 여기에 코드를 작성해주세요.
    return 0;
}