#include<iostream>
#include<unordered_map>
using namespace std;

int main(){
    int n, M;
    unordered_map <int, int> m;
    cin >> n >> M;
    for (int i=0;i<n;i++){
        int tmp;
        cin >> tmp;
        if(m.find(tmp) != m.end()){
            m[tmp]++;
        }
        else{
            m[tmp] = 1;
        }
    }
    for (int i=0;i<M;i++){
        int tmp;
        cin >> tmp;
        if (m.find(tmp) != m.end()){
            cout << m[tmp] << " ";
        }
        else cout << "0 ";
    }

    return 0;
}