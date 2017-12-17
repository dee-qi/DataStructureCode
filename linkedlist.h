#include <iostream>
using namespace std;

template <class T> class LinkedList;

template <class T>
class Node {
    friend LinkedList<T>;

private:
    T data;
    Node<T> *left, *right;

public:
    Node() {left = right = NULL;}
    Node(const T &x) {data = x; left = right = NULL;}
    ~Node() {}
    T getData() {return data;}
    Node<T> *getLeft() const {return left;}
    Node<T> *getRight() const {return right;}
};

template<class T>
class LinkedListIterator {
private:
    Node<T> *node;

public:
    LinkedListIterator(Node<T> *one = NULL){node = one;}
    T operator*() const {return node->getData();}
    T *operator->() const {return &node->getData();}
    bool operator==(const LinkedListIterator<T> another) const {return node == another.node;}
    bool operator!=(const LinkedListIterator<T> another) const {return node != another.node;}
    LinkedListIterator<T> &operator++() {
        node = node->getRight();
        return *this;
    }
    LinkedListIterator<T> operator++(int) {
        LinkedListIterator<T> one = *this;
        node = node->getRight();
        return one;
    }
    LinkedListIterator<T> &operator--() {
        node = node->getLeft();
        return *this;
    }
    LinkedListIterator<T> operator--(int) {
        LinkedListIterator<T> one = *this;
        node = node->getLeft();
        return one;
    }
};

template <class T>
class LinkedList {
private:
    Node<T> *head, *tail;

public:
    typedef LinkedListIterator<T> iterator;
    LinkedList() {head = tail = NULL;}
    ~LinkedList();
    bool isEmpty() const {return head == NULL;}
    int length() const;
    void add(const T &x);
    void addBack(const T &x);
    bool find(int k, T &x) const;
    bool findBack(int k, T &x) const;
    int search(const T &x) const;
    int searchBack(const T &x) const;
    Node<T> *getHead() const {return head;}
    Node<T> *getTail() const {return tail;}
    LinkedList<T> &insert(int k, const T &x);
    LinkedList<T> &insertBack(int k, const T &x);
    LinkedList<T> &remove(int k, T &x);
    LinkedList<T> &removeBack(int k, T &x);
    LinkedList<T> &merge(LinkedList<T> a, LinkedList<T> b);
    void output(ostream &out) const;
    iterator begin() {return iterator(head);}
    iterator end() {return iterator(NULL);}
};

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T> *temp = head, *next;
    while (temp != NULL) {
        next = temp->right;
        delete temp;
        temp = next;
    }
    head = tail = NULL;
}

template <class T>
int LinkedList<T>::length() const
{
    int cnt = 0;
    Node<T> *temp = head;
    while (temp !=NULL) {
        cnt++;
        temp = temp->right;
    }
    return cnt;
}

template <class T>
void LinkedList<T>::add(const T &x)
{
    Node<T> *newone = new Node<T>(x);
    if (isEmpty()) tail = newone;
    if (head != NULL) {
        newone->right = head;
        head->left = newone;
    }
    head = newone;
}

template <class T>
void LinkedList<T>::addBack(const T &x)
{
    Node<T> *newone = new Node<T>(x);
    if (isEmpty()) head = newone;
    if (tail != NULL) {
        newone->left = tail;
        tail->right = newone;
    }
    tail = newone;
}

template <class T>
bool LinkedList<T>::find(int k, T &x) const
{
    int cnt = 1;
    Node<T> *temp = head;
    while (temp != NULL && cnt != k) {
        cnt++;
        temp = temp->right;
    }
    if (temp != NULL) {
        x = temp->data;
        return true;
    }
    return false;
}

template <class T>
bool LinkedList<T>::findBack(int k, T &x) const
{
    int cnt = 1;
    Node<T> *temp = tail;
    while (temp != NULL && cnt != k) {
        cnt++;
        temp = temp->left;
    }
    if (temp != NULL) {
        x = temp->data;
        return true;
    }
    return false;
}


template <class T>
int LinkedList<T>::search(const T &x) const
{
    int cnt = 1;
    Node<T> *temp = head;
    while (temp != NULL && temp->data != x) {
        cnt++;
        temp = temp->right;
    }
    if (temp != NULL) return cnt;
    return 0;
}

template <class T>
int LinkedList<T>::searchBack(const T &x) const
{
    int cnt = 1;
    Node<T> *temp = tail;
    while (temp != NULL && temp->data != x) {
        cnt++;
        temp = temp->left;
    }
    if (temp != NULL) return cnt;
    return 0;
}

template <class T>
LinkedList<T> &LinkedList<T>::insert(int k, const T &x)
{
    int cnt = 1;
    Node<T> *temp = head, *newone = new Node<T>(x);
    while (temp != NULL && cnt !=k) {
        cnt++;
        temp = temp->right;
    }
    if (temp != NULL && temp->right != NULL) temp->right->left = newone;
    if (!isEmpty() && temp == tail) tail = newone;
    if (temp != NULL) {
        newone->left = temp;
        newone->right = temp->right;
        temp->right = newone;
    }
    else
        addBack(x);
    return *this;
}

template <class T>
LinkedList<T> &LinkedList<T>::insertBack(int k, const T &x)
{
    int cnt = 1;
    Node<T> *temp = tail, *newone = new Node<T>(x);
    while (temp != NULL && cnt !=k) {
        cnt++;
        temp = temp->left;
    }
    if (temp != NULL && temp->left != NULL) temp->left->right = newone;
    if (!isEmpty() && temp == head) head = newone;
    if (temp != NULL) {
        newone->right = temp;
        newone->left = temp->left;
        temp->left = newone;
    }
    else
        add(x);
    return *this;
}

template <class T>
LinkedList<T> &LinkedList<T>::remove(int k, T &x)
{
    int cnt = 1;
    Node<T> *temp = head;
    while (temp != NULL && cnt != k) {
        cnt++;
        temp = temp->right;
    }
    if (temp != NULL) {
        x = temp->data;
        if (temp->left != NULL) temp->left->right = temp->right;
        if (temp->right != NULL) temp->right->left = temp->left;
        if (temp == head) head = head->right;
        if (temp == tail) tail = tail->left;
        delete temp;
    }
    return *this;
}

template <class T>
LinkedList<T> &LinkedList<T>::removeBack(int k, T &x)
{
    int cnt = 1;
    Node<T> *temp = tail;
    while (temp != NULL && cnt != k) {
        cnt++;
        temp = temp->left;
    }
    if (temp != NULL) {
        x = temp->data;
        if (temp->right != NULL) temp->right->left = temp->left;
        if (temp->left != NULL) temp->left->right = temp->right;
        if (temp == head) head = head->right;
        if (temp == tail) tail = tail->left;
        delete temp;
    }
    return *this;
}

template <class T>
LinkedList<T> &LinkedList<T>::merge(LinkedList<T> a, LinkedList<T> b)
{
    LinkedList<int>::iterator it_a = a.begin(), it_b = b.begin();
    while (it_a != a.end()) {
        while (it_b != b.end() && *it_b <= *it_a) {addBack(*it_b); it_b++;}
        addBack(*it_a); it_a++;
    }
    while (it_b != b.end()) {addBack(*it_b); it_b++;}
    return *this;
}

template <class T>
void LinkedList<T>::output(ostream &out) const
{
    Node<T> *temp = head;
    while (temp != NULL) {
        out << temp->data << " ";
        temp = temp->right;
    }
}

template <class T>
ostream &operator<<(ostream &out, const LinkedList<T> &list)
{
    list.output(out);
    return out;
}

//int main()
//{
//    LinkedList<int> *list = new LinkedList<int>();
//    int n, x;
//    cout << "Input the number of elements:" << endl;
//    cin >> n;
//    cout << "Input all of the elements:" << endl;
//    for (int i = 1; i <= n; i++) {
//        cin >> x;
//        list->addBack(x);
//    }
//    for (LinkedList<int>::iterator it = list->begin(); it != list->end(); ++it) cout << *it << " ";
//    cout << endl;
//    cout << "Input the element you want to find:" << endl;
//    cin >> x;
//    cout << "The order of this element: " << list->search(x) << endl;
//    cout << "All of the elements count backwards: " << endl;
//    for (LinkedList<int>::iterator it(list->getTail()); it != list->end(); --it) cout << *it << " ";
//    cout << endl;
//    LinkedList<int> *a = new LinkedList<int>(), *b = new LinkedList<int>();
//    cout << "Input the number of elements of the first LinkedList and all of them in increasing order;" << endl;
//    cin >> n;
//    for (int i = 1; i <= n; i++) {
//        cin >> x;
//        a->addBack(x);
//    }
//    cout << "Input the number of elements of the first LinkedList and all of them in increasing order;" << endl;
//    cin >> n;
//    for (int i = 1; i <= n; i++) {
//        cin >> x;
//        b->addBack(x);
//    }
//    LinkedList<int> c;
//    c.merge(*a, *b);
//    cout << c;
//    return 0;
//}

