//
// Created by qidi on 2017/12/6.
//

#ifndef CLIONPROJECTS_MSTACK_H
#define CLIONPROJECTS_MSTACK_H
#include <iostream>
using namespace std;
template <class T>
class Stack{
public:
    Stack(int maxSize = 50){
        this -> maxSize = maxSize;
        stack = new T[maxSize];
    }
    ~Stack(){delete []stack;}
    bool isEmpty(){return top == -1;}
    bool isFull(){return top == maxSize-1;}
    void push (const T& x){
        if(isFull()){cout << "Stack is FULL!" << endl;}
        else {
            top ++;
            stack[top] = x;
        }
    }
    T pop(){
        if(isEmpty()){cout << "Stack is already empty!" << endl;}
        else {
            T rt = stack[top];
//            stack[top] = NULL;
            top --;
            return rt;
        }
    }
private:
    int top = -1;
    int maxSize = 0;
    T* stack;
};
#endif //CLIONPROJECTS_MSTACK_H
