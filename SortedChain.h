#ifndef SORTED_CHAIN_H
#define SORTED_CHAIN_H
template<class E>
struct SortedChainNode{
    E data;
    SortedChainNode<E>* link;
};
template<class E, class K>
class SortedChain{
    public:
        SortedChain(){first = 0;}
        ~SortedChain(){
            SortedChainNode<E> *p = first, *tp;
            while (p){
                tp = p->link;
                delete p;
                p = tp;
            }
        };
        bool IsEmpty() const{return first == 0;}
        int Length() const;
//        bool search(const K &k, E &e);
        SortedChain<E, K>& Delete(const K &k, E &e);
        SortedChain<E, K>& Insert(const E &e);
        SortedChain<E, K>& DistinctInsert(const E &e);
    bool Search(const K& k, E& e);
        void Output();
    private:
        SortedChainNode<E> *first;

};

template<class E, class K>
bool SortedChain<E, K>::Search(const K& k, E& e){
    SortedChainNode<E> *p = first;
    for (; p && p->data < k; p=p->link);
    if (p && p->data == k){
        e = p->data;
        return true;
    }
    return false;
}

template<class E, class K>
SortedChain<E, K>& SortedChain<E, K>::Delete(const K &k, E &e){
    SortedChainNode<E> *p = first, *tp = 0;
    for (; p && p->data < k; tp = p, p=p->link);
    if (p && p->data == k){
        e = p->data;
        if (tp) tp->link = p->link;
        else first = p->link;
        delete p;
        return *this;
    }
    std::cout << "Bad input" << std::endl;
}

template<class E, class K>
SortedChain<E, K>& SortedChain<E, K>::DistinctInsert(const E &e){
    SortedChainNode<E> *p = first, *tp = 0;
    for (; p && p->data < e; tp = p, p=p->link);
    if (p && p->data == e){
        std::cout << "Already exist" << std::endl;
        return *this;
    }
    SortedChainNode<E> *q = new SortedChainNode<E>;
    q->data = e;
    q->link = p;
    if (tp) tp->link = q;
    else first = q;
    return *this;
}
template<class E, class K>
void SortedChain<E, K>::Output(){
    SortedChainNode<E> *p = first;
    for (; p; p=p->link)
        std::cout << p->data << " ";
    std::cout << std::endl;
}
#endif
