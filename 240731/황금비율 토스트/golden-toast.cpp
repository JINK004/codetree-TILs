#include <iostream>
#include <list>
using namespace std;

int main() {
    list<char> mlist;

    int n, m;
    cin >> n >> m;
    for (int i=0;i<n;i++){
        char tmp;
        cin >> tmp;
        mlist.push_back(tmp);
    }

    list<char>::iterator it; 
    it = mlist.end();

    for (int i=0;i<m;i++){
        char tmp;
        cin >> tmp;
        if(tmp == 'L'){
            if(it == mlist.begin()) continue;
            it--;
        }
        else if(tmp == 'R'){
            if(it == mlist.end()) continue;
            it++;
        }
        else if(tmp == 'D'){
            if(it == mlist.end()) continue;
            it = mlist.erase(it);
        }
        else if(tmp == 'P'){
            char num;
            cin >> num;
            mlist.insert(it, num);
        }
        else{
            cout << "ERROR\n";
        }
    }

    for (it=mlist.begin(); it!=mlist.end(); it++){
        cout << *it;
    }
    return 0;
}