#include<iostream>

using namespace std;

void perm(int k, int m, int list[]){
    if(k == m){
        for(int i=0; i<m; i++)
            cout << list[i];
        cout << endl;
    } else {
        for(int j=k; j<m; j++){
            swap(list[k], list[j]);
            perm(k+1, m, list);
            swap(list[k], list[j]);
        }
    }
}

void swap(int &a, int &b){
    a = a + b;
    b = a - b;
    a = a - b;
}

int main(){
    cout << "enter the length of the list:";
    int len;
    cin >> len;
    int *list = new int[len];
    for(int i=0; i<len; i++){
        list[i] = i;
        //cout << "list[" << i << "] is " << list[i] << endl;
    }
    perm(0, len, list);
    return 0;
}
