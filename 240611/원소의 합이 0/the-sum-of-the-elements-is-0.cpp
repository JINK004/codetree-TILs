#include<iostream>
#include<unordered_map>
using namespace std;

int main(){
    int n;
    cin >> n;
    unordered_map<int, int> map[4];
    for (int count=0;count<4;count++){
        for (int i=0;i<n;i++){
            int tmp;
            cin >> tmp;
            map[count][tmp]++;
        }
    }
    int cnt = 0;
    for(unordered_map<int, int>::iterator it = map[0].begin(); it != map[0].end(); it++){
        for(unordered_map<int,int>::iterator it2=map[1].begin(); it2!=map[1].end();it2++){
            for(unordered_map<int,int>::iterator it3=map[2].begin(); it3!=map[2].end(); it3++){
                int tmp = it->first + it2->first + it3->first;
                if(map[3].find(-tmp) != map[3].end()){
                    cnt += (it->second * it2->second * it3->second);
                }
            }
        }
    }
    cout << cnt;
    return 0;
}