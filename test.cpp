#include <iostream>

void swap(int &a, int &b){
    a = a+b;
    b = a-b;
    a = a-b;
}

int main(){
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    for (int i=0; i<3/2; i++){
        for(int j=0; j<3; j++){
            swap(a[j][i], a[j][3-i-1]);
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            std::cout << a[i][j];
        }
        std::cout << std::endl;
    }
}
