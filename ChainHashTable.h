#ifndef CHAIN_HASH_TABLE_H
#define CHAIN_HASH_TABLE_H
#include "SortedChain.h"
template<class E, class K>
class ChainHashTable{
    public:
        ChainHashTable(int divisor = 961){
            D = divisor;
            ht = new SortedChain<E, K>[D];
        }
        ~ChainHashTable(){delete[] ht;}
        bool Search(const K &k, E &e) const{
            return ht[k % D].Search(k, e);
        }
        ChainHashTable<E, K>& Insert(const E &e){
            ht[e % D].DistinctInsert(e);
            return *this;
        }
        ChainHashTable<E, K>& Delete(const K &k, E &e){
            ht[k % D].Delete(k, e);
            return *this;
        }
        void Output() const{
            for (int i=0; i<D; ++i){
                std::cout << "the " << i << "th chain element :\n";
                ht[i].Output();
            }
        }
    private:
        int D;
        SortedChain<E, K> *ht;
};
#endif
