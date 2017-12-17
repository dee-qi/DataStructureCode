//
// Created by qidi on 2017/12/6.
//

#ifndef CLIONPROJECTS_MQUEUE_H
#define CLIONPROJECTS_MQUEUE_H
using namespace std;
#include <iostream>
template <class T>
class Queue{
public:
    Queue(int maxSize){
        this -> maxSize = maxSize;
        que = new T[maxSize];
    }
    ~Queue(){delete []que;}
    bool isEmpty(){
        return top == -1;
    }
    bool isFull(){
        return top == maxSize-1;
    }
    void push(const T& x){
        if(isFull()){cout << "Queue is FULL!" <<endl;}
        else {
            top++;
            que[top] = x;
        }
    }
    T front(){
      if(isEmpty()) return NULL;
      return que[0];
    }
    T pop(){
        if(isEmpty()){cout << "Queue is already empty!" << endl;}
        else {
            T rt = que[0];
            for(int i=0; i<top; i++){
                que[i] = que[i+1];
            }
            top --;
            return rt;
        }
    }
private:
    T* que;
    int maxSize = 0;
    int top = -1;
};
#endif //CLIONPROJECTS_MQUEUE_H
