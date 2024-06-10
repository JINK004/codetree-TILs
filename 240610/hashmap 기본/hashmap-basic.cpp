#include<iostream>
#include<unordered_map>
using namespace std;

int main(){

    int n;
    unordered_map<int, int> m;
    cin >> n;
    for (int i=0;i<n;i++){
        string tmp;
        cin >> tmp;
        if(tmp == "add"){
            int k, v;
            cin >> k >> v;
            m[k] = v;
        }

        else if(tmp == "remove"){
            int k;
            cin >> k;
            m.erase(k);
        }

        else if(tmp == "find"){
            int k;
            cin >> k;
            if(m.find(k) != m.end()){
                cout << m[k] << "\n";
            }
            else cout << "None\n";
        }
    }

    return 0;
}