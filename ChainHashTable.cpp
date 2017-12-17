#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "ChainHashTable.h"
using namespace std;
int main(){
    srand(time(0));
    ChainHashTable<int, int> c(961);
    for (int i=0; i<40; ++i){
        int t = rand() % 9999;
        c.Insert(t);
        cout << "insert value  " << t << endl;
    }
    c.Output();
    int n, k;
    while (cin >> n){
        cout << (c.Search(n, k) ? "found " : "not found ") << n << endl;
    }
    return 0;
}
