#include<iostream>

using namespace std;

void subset(int list[], int tag[], int k, int m){
    //for(int k=0; k<m; k++) cout << tag[k];
    //cout << "\n";
    if(k == m){
        cout << "{";
        for(int i=0; i<m; i++){
            if(tag[i] == 1) cout << list[i] << ",";
        }
        cout << "}" << endl;
    } else {
        tag[k] = 0;
        subset(list, tag, k+1, m);
        tag[k] = 1;
        subset(list, tag, k+1, m);
    }
}

int main(){
    cout << "enter the length of the list:";
    int len;
    cin >> len;
    int *list = new int[len];
    int *tag = new int[len];
    for(int i=0; i<len; i++) cin >> list[i];
    for(int j=0; j<len; j++) tag[j] = 0;
    subset(list, tag, 0, len);
}
