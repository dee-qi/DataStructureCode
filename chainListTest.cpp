#include<iostream>

using namespace std;

template <class T>
struct chainNode
{
	//成员变量们
	T element;
	chainNode<T> *next;
    chainNode<T> *previous;

	//构造方法们
	chainNode(){}
	explicit chainNode(const T& element) {
		this->element = element;
        this->next = nullptr;
        this->previous = nullptr;
	}
	chainNode(const T& element, chainNode<T>* next, chainNode<T>* previous) {
		this->element = element;
		this->next = next;
        this->previous = previous;
	}
};

template <class T>
class chain {
	public:
        chain(){
            firstNode = nullptr;
            lastNode = nullptr;
            listSize = 0;
        }
		chain(const chain<T>&);
		~chain();

		bool empty() const {return listSize == 0;};
		int size() const {return listSize;};
		T& get(int index) const;
		int indexOf(const T& element) const;
		void deleteNode(int index);
        void insertBeginning(const T &element);
		void insert(int index, const T& element);
		void output(const string msg) const;
        void output_re(const string msg) const;
        void add(const T &element);
        class ChainIter{
        public:
            ChainIter(){}
            ChainIter(chain<T>* chain){
                mChain = chain;
                location = chain->firstNode;
            }

            bool hasNext(){
                return location->next != nullptr;
            }

            void setPositionToEnd(){
                location = mChain->lastNode;
            }

            void setPositionToStart(){
                location = mChain->firstNode;
            }

            chainNode<T>* next(){
                if(location != nullptr) {
                    location = location->next;
                    return location;
                } else {
                    return nullptr;
                }
            }

            chainNode<T>* previous(){
                if(location != nullptr){
                    location = location->previous;
                    return location;
                } else {
                    return nullptr;
                }
            }

            chainNode<T>* getCurrent(){
                return location;
            }

            T getCurrentElement(){
                return location->element;
            }

            void output_reverse(){

            }

        private:
            chain<T>* mChain = nullptr;
            chainNode<T>* location = nullptr;

        };

	protected:
		void checkIndex(int index) const{
            if(index < 0 )
                throw out_of_range("Index is not valid.");;
        };
		chainNode<T>* firstNode;
        chainNode<T>* lastNode;
		int listSize;
};

template <class T>
chain<T>::chain(const chain<T>& theList) {
	this->listSize = theList.listSize;
	if(listSize == 0){
		this->firstNode = NULL;
	} else {
		chainNode<T>* sourceNode = theList.firstNode;
		firstNode = new chainNode<T>(sourceNode->element);
		sourceNode = sourceNode->next;
		chainNode<T>* targetNode = firstNode;
		while(sourceNode != NULL){
			targetNode->next = new chainNode<T>(sourceNode->element);
			targetNode = targetNode->next;
			sourceNode = sourceNode->next;
		}
		targetNode->next = NULL;
	}
}

template <class T>
chain<T>::~chain() {
	while(firstNode != NULL){
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template <class T>
T& chain<T>::get(int index) const {
	checkIndex(index);

	chainNode<T>* currentNode = firstNode;
	for(int i=0; i<index; i++){
		currentNode = currentNode->next;
	}
	return currentNode->element;
}

template <class T>
int chain<T>::indexOf(const T &element) const {
	chainNode<T>* currentNode = firstNode;
	int index = 0;
	while(currentNode != nullptr && currentNode->element != element){
		currentNode = currentNode->next;
		index++;
	}

	if(currentNode == nullptr)
		return -1;
	else return index;
}

template <class T>
void chain<T>::deleteNode(int index) {
	checkIndex(index);

	chainNode<T>* deleteNode;
	if(index == 0){
		deleteNode = firstNode;
		firstNode = firstNode->next;
	} else if(index == listSize-1){
        deleteNode = lastNode;
        lastNode = lastNode->previous;
    } else {
		chainNode<T>* p = firstNode;
		for(int i=0; i<index-1; i++){
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;
        p->next->previous = p;
	}
	listSize --;
	delete deleteNode;
}
template <class T>
void chain<T>::insertBeginning(const T &element) {
    chainNode<T>* newNode = new chainNode<T>(element, firstNode, nullptr);
    firstNode->previous = newNode;
    firstNode = newNode;
}

template <class T>
void chain<T>::insert(int index, const T &element) {
	checkIndex(index);

	if(index == 0){
		firstNode = new chainNode<T>(element, firstNode, nullptr);
//        cout<< "1:"<<firstNode->next<<endl;
	} else {
		chainNode<T>* p = firstNode;
		for(int i=0; i<index-1; i++){
			p=p->next;
		}
        chainNode<T>* newNode = new chainNode<T>(element, p->next, p);
        p->next->previous = newNode;
		p->next = newNode;
//        cout<< "inserted" << element << endl << p->next->next<<endl;
	}
	listSize ++;
}

template <class T>
void chain<T>::output(const string msg) const {
    cout << msg;
	for(chainNode<int>* p = firstNode;
			p != nullptr;
			p = p->next){
		cout << p->element << ",";
	}
    cout << endl;
}

template <class T>
void chain<T>::output_re(const string msg) const {
    cout << msg;
    for(chainNode<int>* p = lastNode;
        p != nullptr;
        p = p->previous){
        cout << p->element << ",";
    }
    cout << endl;
}

template <class T>
void chain<T>::add(const T &element) {
    chainNode<T>* p = firstNode;
    if(p == nullptr){
        firstNode = new chainNode<T>(element);
        lastNode = firstNode;
    } else {
        while(p->next != nullptr){
            p = p->next;
        }
        p->next = new chainNode<T>(element, nullptr, p);
        lastNode = p->next;
//        cout << "***add element " << element << " ,previous:" << lastNode->previous->element <<endl;
    }
}

int main(){
    //****初始化链表****
    chain<int>* chain1 = new chain<int>();
    int list[10] = {5, 12, 6, 76, 22, 33, 76, 23, 21, 99};
    for(int i=0; i<10; i++){
        chain1->add(list[i]);
    }
    chain1->output("Original list : ");

    //****删除元素12****
    chain1->deleteNode(1);
    chain1->output("After deleting element 12 : ");

    //****在末尾插入元素37****
    chain1->add(37);
    chain1->output("After adding 37 : ");

    //****在表首插入元素8****
    chain1->insertBeginning(8);
    chain1->output("After inserting element 8 in the front : ");

    //****在位置2插入元素9
    chain1->insert(2, 9);
    chain1->output("After inserting element 9 at index 2 : ");

    //****输出index为3的元素（第四个元素）****
    cout << "The element indexing 3 : " << chain1->get(3) << endl;

    //****倒序输出****
    chain1->output_re("OUTPUT REVERSE : ");

    //****在链表中搜索某个元素，并输出它的序号****
    cout << "index of 22 is : " << chain1->indexOf(22) << endl;//存在的情况
    cout << "index of 55 is : " << chain1->indexOf(55) << endl;//不存在的情况，输出-1

    //****创建链表遍历器类，并利用列表遍历器遍历输出链表****
    chain<int>::ChainIter* iter = new chain<int>::ChainIter(chain1);
    cout << "OUTPUT with Iter : ";
    do{
        cout << iter->getCurrentElement() << ",";
    } while (iter->next());
    cout << endl;

    //****利用链表遍历器类逆序输出链表****
    cout << "OUTPUT_REVERSE with Iter : ";
    iter->setPositionToEnd();
    do{
        cout << iter->getCurrentElement() << ",";
    } while (iter->previous());
    cout << endl;

    //****创建两个有序链表，并用列表遍历器合并****
    chain<int>* chain2 = new chain<int>();
    chain<int>* chain3 = new chain<int>();
    int l1[6] = {1,3,5,6,8,12};
    int l2[9] = {2,4,9,10,11,15,22,33,99};
    for(int i=0; i<6; i++){
        chain2->add(l1[i]);
    }
    for(int i=0; i<9; i++){
        chain3->add(l2[i]);
    }
    chain<int>::ChainIter* iter2 = new chain<int>::ChainIter(chain2);
    chain<int>::ChainIter* iter3 = new chain<int>::ChainIter(chain3);
    chain<int>* newChain = new chain<int>();//合并后的新链表
    while(true){
        if(iter2->getCurrentElement() < iter3->getCurrentElement()){
            newChain->add(iter2->getCurrentElement());
            iter2->next();
        } else {
            newChain->add(iter3->getCurrentElement());
            iter3->next();
        }
        if(!iter2->hasNext() || !iter3->hasNext()){
            break;
        }
    }
    do{
        newChain->add(iter3->getCurrentElement());
    } while(iter3->next());
    newChain->output("new chain : ");

    return 0;
}