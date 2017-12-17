#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

template<class T>
class MaxHeap{
private:
	vector<T> list;
	void insertBack(int index){
		if (index > 1 && list[index - 1] > list[index / 2 - 1]){
			swap(list[index / 2 - 1], list[index - 1]);
			insertBack(index / 2);
		}
	}

	void insertFront(int index){
		if (index * 2 <= list.size()){
			if (index * 2 + 1 <= list.size()){
				if (list[index - 1] < list[index * 2 - 1] && list[index - 1] >= list[index * 2]){
					swap(list[index * 2 - 1], list[index - 1]);
					insertFront(index * 2);
				}
				else if (list[index - 1] > list[index * 2 - 1] && list[index - 1] <= list[index * 2]){
					swap(list[index * 2], list[index - 1]);
					insertFront(index * 2 + 1);
				}
				else if (list[index - 1] <= list[index * 2 - 1] && list[index - 1] <= list[index * 2]){
					if (list[index * 2] > list[index * 2 - 1]){
						swap(list[index * 2], list[index - 1]);
						insertFront(index * 2 + 1);
					}
					else{
						swap(list[index * 2 - 1], list[index - 1]);
						insertFront(index * 2);
					}
				}
			}
			else{
				if (list[index - 1] < list[index * 2 - 1]){
					swap(list[index * 2 - 1], list[index - 1]);
				}
			}
		}
	}
public:
	void insert(const T& a){
		list.push_back(a);
		int size = list.size();
		insertBack(size);
	}

	T pop(){
		T a = list.back();
		T max = list.front();
		list.pop_back();
		if (list.size() > 0){
			list[0] = a;
			int index = 1;
			insertFront(index);
		}
		return max;
	}

	MaxHeap(T* a,int n){
		for (int i = 0; i < n; i++){
			insert(a[i]);
		}
	}

	void out(){
		typename vector<T>::iterator ite;
		for (ite = list.begin(); ite != list.end(); ite++){
			cout << *ite << " ";
		}
		cout << endl;
	}

};

template<class T>
class MinHeap{
private:
	vector<T> list;
	void insertBack(int index){
		if (index > 1 && list[index - 1] < list[index / 2 - 1]){
			swap(list[index / 2 - 1], list[index - 1]);
			insertBack(index / 2);
		}
	}

	void insertFront(int index){
		if (index * 2 <= list.size()){
			if (index * 2 + 1 <= list.size()){
				if (list[index - 1] > list[index * 2 - 1] && list[index - 1] <= list[index * 2]){
					swap(list[index * 2 - 1], list[index - 1]);
					insertFront(index * 2);
				}
				else if (list[index - 1] < list[index * 2 - 1] && list[index - 1] >= list[index * 2]){
					swap(list[index * 2], list[index - 1]);
					insertFront(index * 2 + 1);
				}
				else if (list[index - 1] >= list[index * 2 - 1] && list[index - 1] >= list[index * 2]){
					if (list[index * 2] < list[index * 2 - 1]){
						swap(list[index * 2], list[index - 1]);
						insertFront(index * 2 + 1);
					}
					else{
						swap(list[index * 2 - 1], list[index - 1]);
						insertFront(index * 2);
					}
				}
			}
			else{
				if (list[index - 1] > list[index * 2 - 1]){
					swap(list[index * 2 - 1], list[index - 1]);
				}
			}
		}
	}
public:
	void insert(const T& a){
		list.push_back(a);
		int size = list.size();
		insertBack(size);
	}

	T pop(){
		T a = list.back();
		T min = list.front();
		list.pop_back();
		if (list.size() > 0){
			list[0] = a;
			int index = 1;
			insertFront(index);
		}
		return min;
	}

	int size(){
		return list.size();
	}
};

template<class T>
class HuffmanTree;

template<class T>
class BinarySearchTree;

template<class T>
class BinaryTreeNode{
	friend HuffmanTree<T>;
	friend BinarySearchTree<T>;
private:
	int weight;
	T data;
	BinaryTreeNode<T> *left, *right;
public:
	BinaryTreeNode(int weight, const T& data, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right){
		this->weight = weight;
		this->data = data;
		this->left = left;
		this->right = right;
	}

	bool operator > (const BinaryTreeNode<T>& other){
		if (this->weight > other.weight)
			return true;
		else
			return false;
	}

	bool operator >= (const BinaryTreeNode<T>& other){
		if (this->weight >= other.weight)
			return true;
		else
			return false;
	}

	bool operator < (const BinaryTreeNode<T>& other){
		if (this->weight < other.weight)
			return true;
		else
			return false;
	}

	bool operator <= (const BinaryTreeNode<T>& other){
		if (this->weight <= other.weight)
			return true;
		else
			return false;
	}
};

template<class T>
class HuffmanTree{
private:
	MinHeap<BinaryTreeNode<T>> heap;
	map<T, vector<char>> hash;

	vector<char> tmp;
	void preOrder(BinaryTreeNode<T>* cur){
		if (cur != NULL){
			tmp.push_back('0');
			preOrder(cur->left);
			if (cur->data){
				hash[cur->data] = tmp;
			}
			tmp.push_back('1');
			preOrder(cur->right);
			if (cur->data){
				hash[cur->data] = tmp;
			}
			if (tmp.size() > 0)
				tmp.pop_back();
		}
		else{
			if (tmp.size() > 0)
				tmp.pop_back();
		}
	}
public:
	HuffmanTree(map<T, int> m){
		typename map<T, int>::iterator it;
		for (it = m.begin(); it != m.end(); it++){
			heap.insert(*(new BinaryTreeNode<T>(it->second, it->first, NULL, NULL)));
		}
		while (heap.size()>1){
			BinaryTreeNode<T> *n1 = new BinaryTreeNode<T>(0, 0, 0, 0);
			*n1 = heap.pop();
			BinaryTreeNode<T> *n2 = new BinaryTreeNode<T>(0, 0, 0, 0);
			*n2 = heap.pop();
			BinaryTreeNode<T> *n = new BinaryTreeNode<T>(n1->weight + n2->weight, 0, n1, n2);
			heap.insert(*n);
		}
		BinaryTreeNode<T> *node = new BinaryTreeNode<T>(0, 0, 0, 0);
		*node = heap.pop();
		preOrder(node);
		typename map<T, vector<char>>::iterator it1;
		for (it1 = hash.begin(); it1 != hash.end(); it1++){
			cout << "Element: " << it1->first << " Prefix: ";
			vector<char> vec = it1->second;
			vector<char>::iterator ite;
			for (ite = vec.begin(); ite != vec.end(); ite++){
				cout << *ite;
			}
			cout << endl;
		}
	}

	void code(T* a, int n){
		for (int i = 0; i < n; i++){
			vector<char>::iterator ite;
			for (ite = hash[a[i]].begin(); ite != hash[a[i]].end(); ite++){
				cout << *ite;
			}
		}
		cout << endl;
	}
};

template<class T>
class BinarySearchTree{
private:
	BinaryTreeNode<T> *head;

	BinarySearchTree(BinaryTreeNode<T> *h){
		head = h;
	}
public:
	BinarySearchTree(T* a,int n){
		head = new BinaryTreeNode<T>(0, a[0], NULL, NULL);
		for (int i = 1; i < n; i++){
			insert(a[i]);
		}
	}

	void insert(T data){
		if (data < head->data){
			if (head->left){
				BinarySearchTree<T> *lt = new BinarySearchTree<T>(head->left);
				lt->insert(data);
			}
			else{
				BinaryTreeNode<T> *node = new BinaryTreeNode<T>(0, data, NULL, NULL);
				head->left = node;
			}
		}
		else{
			if (head->right){
				BinarySearchTree<T> *rt = new BinarySearchTree<T>(head->right);
				rt->insert(data);
			}
			else{
				BinaryTreeNode<T> *node = new BinaryTreeNode<T>(0, data, NULL, NULL);
				head->right = node;
			}
		}
	}

	bool search(T data){
		if (data < head->data){
			if (head->left){
				BinarySearchTree<T> *lt = new BinarySearchTree<T>(head->left);
				return lt->search(data);
			}
			else{
				return false;
			}
		}
		else if (data == head->data){
			return true;
		}
		else{
			if (head->right){
				BinarySearchTree<T> *rt = new BinarySearchTree<T>(head->right);
				rt->search(data);
			}
			else{
				return false;
			}
		}
	}
};

int main(){
	int n = 10;
	int a[10] = {32, 65, 44, 123, 67, 45, 12, 98, 21, 76};
	cout << "===================================================" << endl;
  	cout << "===INIT THE MAXHEAP " << endl;//初始化最大堆
	MaxHeap<int> heap(a, n);
	heap.out();
	cout << endl;
	cout << "===================================================" << endl;
  	cout << "===After insert number 54" << endl;//插入元素54
	heap.insert(54);
	heap.out();
	cout << endl;
	cout << "===================================================" << endl;
  	cout << "===After deleting the max number " << endl;//删除最大元素
	heap.pop();
	heap.out();
	cout << endl;
	cout << "===================================================" << endl;
  	cout << "===HuffMan Code " << endl;//霍夫曼编码
	map<int, int> m;
	for (int i = 0; i < n; i++){
		char c = a[i];
		if (m.find(c) != m.end()){
			m[c] += 1;
		}
		else{
			m[c] = 1;
		}
	}
	HuffmanTree<int> t(m);
	t.code(a, n);
	cout << endl;
	cout << "===================================================" << endl;
  	cout << "===Binary Search Tree " << endl;//二叉搜索树搜索
	BinarySearchTree<int> tree(a, n);
	cout << endl;
	int tmp = 0;
	cout << "===Input element to search, \"8888\" to exit." << endl;
	while(tmp != 8888){
		cin >> tmp;
		if (tree.search(tmp)){
			cout << "THe number " << tmp << "exists!" << endl;
		}
		else{
			cout << "There is no such number in this heap." << endl;
		}
	}
	cout << endl;
	cout << "===================================================" << endl;
  	cout << "===Heap Sort " << endl;//堆排序
	for (int i = 0; i < n; i++){
		cout << heap.pop() << " ";
	}
	cout << endl;
}
