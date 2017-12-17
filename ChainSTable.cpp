#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "linkedlist.h"
using namespace std;

const int MOD = 1e6 + 7, KASE = 20;

template <class T>
class HashTable {
private:
    LinkedList<T> *ht;

public:
    HashTable() {ht = new LinkedList<T>[MOD];}
    ~HashTable() {delete[] ht;}
    HashTable<T> &insert(const T x);
    HashTable<T> &remove(const T x, T &e);
    bool search(const T x) const;
};

template <class T>
HashTable<T> &HashTable<T>::insert(const T x)
{
    int pos = x % MOD;
    ht[pos].addBack(x);
    return *this;
}

template <class T>
HashTable<T> &HashTable<T>::remove(const T x, T &e)
{
    int pos = x % MOD;
    int k = ht[pos].search(x);
    if (k) ht[pos].remove(k, e);
    return *this;
}

template <class T>
bool HashTable<T>::search(const T x) const
{
    int pos = x % MOD;
    if (ht[pos].search(x))
        return true;
    else
        return false;
}

int main()
{
    HashTable<int> hs;
    srand(time(0));
    int cnt = 0;
    for (int i = 1; i <= KASE; i++) {
        int x = rand();
        hs.insert(x);
        cout << setw(6) << x << " ";
        if (++cnt % 10 == 0) cout << endl;
    }
    int n;
    cout << "Input the number of your query:" << endl; cin >> n;
    while (n--) {
        cout << "Input the number you want to check if it is in the HashTable:" << endl;
        int x;
        cin >> x;
        cout << (hs.search(x) ? "YES\n" : "NO\n") << endl;
    }
    return 0;
}
