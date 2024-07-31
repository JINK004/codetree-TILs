#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> mlist;
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        string tmp;
        cin >> tmp;
        if (tmp == "push_back"){
            int num;
            cin >> num;
            mlist.push_back(num);
        }
        else if(tmp == "push_front"){
            int num;
            cin >> num;
            mlist.push_front(num);
        }
        else if(tmp == "pop_front"){
            int num = mlist.front();
            mlist.pop_front();
            cout << num << "\n";
        }
        else if(tmp == "pop_back"){
            int num = mlist.back();
            mlist.pop_back();
            cout << num << "\n";
        }
        else if(tmp == "size"){
            cout << mlist.size() << "\n";
        }
        else if(tmp == "empty"){
            if (mlist.empty()) cout << "1\n";
            else cout << "0\n";
        }
        else if(tmp == "front"){
            cout << mlist.front() << "\n";
        }
        else if(tmp == "back"){
            cout << mlist.back() << "\n";
        }
        else {
            cout << "Error\n";
        }
    }
    return 0;
}