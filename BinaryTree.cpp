#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include "mQueue.h"
int count_;
using namespace std;

struct node
{
	node* left;
	node* right;
	char data;
	int id;
};

class Tree
{
public:
Tree() {
	root = NULL; height = 0;
};

int getHeight(node *root) const;
int getSize(node *root);
void visit(node *root) {
	cout << root->data << " ";
};

node* makeTreeViaLevelOrder(node *root,char *levelOrder);
void makeTreeViaPreInOrder(node **root, char *preOrder, char *inOrder, int length);

void preOrder(node *root);
void inOrder(node *root);
void postOrder(node *root);
void levelOrder(node *root);
node* getRoot() {
	if (root) return root; else return NULL;
};
private:
node* root;
int height;
void cnt(node *root)
{
	if (root == NULL)
		return;
	count_++;
	cnt(root->left);
	cnt(root->right);
}
};

int Tree::getHeight(node *root) const
{
	if(!root) return 0;
	int hl = getHeight(root->left);
	int hr = getHeight(root->right);
	if (hl > hr) return ++hl;
	else return ++hr;
}

int Tree::getSize(node *root)
{
	count_ = 1;
	if (root == NULL)
		return 0;
	cnt(root->left);
	cnt(root->right);
	return count_;
}
node* Tree::makeTreeViaLevelOrder(node *root,char *levelOrder)
{
	int i = 1;
	int j = 1;
	node** arr[100];
	while (j <= strlen(levelOrder))
	{
		if (i == 1)
		{
			root = new node;
			root->data = levelOrder[j-1];
			arr[i - 1] = &root;
			i++;
			j++;
			continue;
		}
		if (levelOrder[j - 1] == '#')
		{
			if (i % 2 == 0 && arr[i / 2 - 1])
				(*arr[i / 2 - 1])->left = NULL;
			else
				(*arr[i / 2 - 1])->right = NULL;
			arr[i - 1] = new node*;//节点不位空
			node *temp = new node; *arr[i - 1] = temp;
			(*arr[i - 1])->left = NULL; (*arr[i - 1])->right = NULL;
			*arr[i - 1] = NULL;
			i++; j++; continue;
		}
		arr[i - 1] = new node*;//节点不位空
		node *temp = new node;
		temp->data = levelOrder[j - 1];
		if (i % 2 == 0)
			(*arr[i / 2 - 1])->left = temp;
		else (*arr[i / 2 - 1])->right = temp;
		*arr[i - 1] = temp;
		(*arr[i - 1])->left = NULL;
		(*arr[i - 1])->right = NULL;
		i++; j++;
	}
	return root;
}

void Tree::makeTreeViaPreInOrder(node **root,char *preOrder,char *inOrder,int length)
{
	if (length == 0)
	{
		*root = NULL;
		return;
	}
	*root = new node;
	(*root)->data = *preOrder;
	char *rootPlace = strchr(inOrder, (*root)->data);
	cout << "ROOTPLACE IS " << rootPlace;
	if (rootPlace == NULL)
	{
		cout << "INPUT WRONG ORDER SAMPLE" << endl;
		system("pause");
	}

	int leftLength = strlen(inOrder) - strlen(rootPlace);
	int rightLength = length - leftLength - 1;
	makeTreeViaPreInOrder(&(*root)->left, preOrder + 1, inOrder, leftLength);
	makeTreeViaPreInOrder(&(*root)->right, preOrder +leftLength+1, rootPlace+1, rightLength);
}

void Tree::preOrder(node *root)
{
	if (root == NULL)
		return;
	visit(root);
	preOrder(root->left);
	preOrder(root->right);
}

void Tree::inOrder(node *root)
{
	if (root == NULL)
		return;
	inOrder(root->left);
	visit(root);
	inOrder(root->right);
}

void Tree::postOrder(node *root)
{
	if (root == NULL)
		return;
	postOrder(root->left);
	postOrder(root->right);
	visit(root);
}

void Tree::levelOrder(node *root)
{
	Queue<node*> *q = new Queue<node*>(100);
	if(root)
	{
		q->push(root);
		while (!q->isEmpty())
		{
			node *t = q->front();
			visit(t);
			if (t->left) q->push(t->left);
			if (t->right) q->push(t->right);
			q->pop();
		}
	}
}


//template<class T>
int main()
{
	int continue_ = 1;
	Tree *t = new Tree();
	char *pre= "ABDEIJCFG";
	char *in = "DBIEJAFCG";
	char *level = "ABCDEFG";
	cout << "EXAMPLE: Make a binary tree via levelOrder(ABCDEFG) and display :" << endl;
	node *r1 = t->getRoot();
	r1 = t->makeTreeViaLevelOrder(r1,level);
	cout << "1. preOder: ";
	t->preOrder(r1);
	cout << "\n2. inOrder: ";
	t->inOrder(r1);
	cout << "\n3. postOrder: ";
	t->postOrder(r1);
	cout << "\n4. levelOrder: ";
	t->levelOrder(r1);
	int h = t->getHeight(r1);
	cout << "\n5. Height:  " << h << endl;
	int c = t->getSize(r1);
	cout << "6. Size:  " << c << endl;

	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "EXAMPLE: Make a binary tree via pre&inOrder(ABDEIJCFG&DBIEJAFCG) and display :" << endl;
	node *r2 = t->getRoot();
	t->makeTreeViaPreInOrder(&r2, pre, in, strlen(pre));
	cout << "1. postOrder: ";
	t->postOrder(r2);
	cout << endl; cout << endl;

	cout << "MAKE YOUR OWN TREE VIA METHOD BELOW."<<endl;
	while (continue_)
	{
		char *pre2 = new char;
		char *in2 = new char;
		char *level2 = new char;

		cout << "PLEASE INPUT A LEVEL ORDERING STRING TO BUILD A COMPLETE BINARY TREE." << endl;
		cin >> level2;
		node *r11 = t->getRoot();
		r11 = t->makeTreeViaLevelOrder(r11, level2);
		cout << "1. preOder: ";
		t->preOrder(r11);
		cout << "\n2. inOrder: ";
		t->inOrder(r11);
		cout << "\n3. postOrder: ";
		t->postOrder(r11);
		cout << "\n4. levelOrder: ";
		t->levelOrder(r11);
		int h = t->getHeight(r11);
		cout << "\n5. Height:  " << h << endl;
		int c = t->getSize(r11);
		cout << "6. Size:  " << c << endl;

		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "PLEASE INPUT A COMPLETE PRE&IN ORDER BINARY TREE STRING." << endl;
		cin >> pre2; cin >> in2;
		node *r22 = t->getRoot();
		t->makeTreeViaPreInOrder(&r22, pre2, in2, strlen(pre2));
		cout << "\npostOrder: ";
		t->postOrder(r22);
		cout << endl;
		cout << "continue for 1 quit for 0" << endl;
		cin >> continue_;
	}

	system("pause");
	return 0;
}
