#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "HashTable.h"
using namespace std;
int main(){
  cout << "线性开型寻址展示："<<endl;
  cout << "D is 10，put 1,11,111,2" << endl;
  HashTable<int, int> cc(10);
  cc.Insert(1);
  cc.Insert(11);
  cc.Insert(111);
  cc.Insert(2);
  cc.Output();
  cout << "____________________________________________________________" << endl;
  cout << "Now create another table and insert 40 numbers." << endl;
  cout << "____________________________________________________________" << endl;
  HashTable<int, int> d(961);
  srand(time(0));
  int n, k;
  for (int i=0; i<40; ++i){
      int t = rand() % 1077;
      d.Insert(t);
      cout << "insert " << t << endl;
  }
  d.Output();
  cout << "NOW INPUT A NUMBER TO QUERY:" << endl;
  while (cin >> n)
      cout << (d.Search(n, k) ? "value found " : " value not found ") << n << endl;
  return 0;
}
