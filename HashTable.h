#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <cstring>
template<class E, class K>
class HashTable{
    public:
        HashTable(int divisor = 961);
        ~HashTable(){delete[] ht; delete[] empty;}
        bool Search(const K &k, E &e) const;
        HashTable<E,K>& Insert(const E &e);
        void Output();
    private:
        int hSearch(const K &k) const;
        int D;
        E *ht;
        bool *empty;
};

template<class E, class K>
void HashTable<E, K>::Output(){
    for (int i=0; i<D; ++i)
        if (!empty[i])
            std::cout << ht[i] << " ";
    std::cout << std::endl;
}

template<class E, class K>
HashTable<E, K>::HashTable(int divisor){
    D = divisor;
//    std::cout << D << "\t" << divisor << std::endl;
    ht = new E[D];
    empty = new bool[D];
    for (int i=0; i<D; ++i) {
        ht[i] = 0;
        empty[i] = true;
    }
}

template<class E, class K>
int HashTable<E, K>::hSearch(const K &k) const{
    int i = k % D;
    int j = i;
    do{
        if (empty[j] || ht[j] == k)
            return j;
        j = (j + 1) % D;
    }while (j != i);
    return j;
}

template<class E, class K>
bool HashTable<E, K>::Search(const K &k, E &e) const{
    int b = hSearch(k);
    if (empty[b] || ht[b] != k)
        return false;
    e = ht[b];
    return true;
}

template<class E, class K>
HashTable<E, K>& HashTable<E, K>::Insert(const E &e){
    K k = e;
    int b = hSearch(k);
    std::cout << "Insert at position : " << b << std::endl;
    if (empty[b]){
        empty[b] = false;
        ht[b] = e;
        return *this;
    }
    if (ht[b] == k)
        std::cout << "Collision occured!!!!" << std::endl;
    else
        std::cout << "No enough memory" << std::endl;
    return *this;

}
#endif
