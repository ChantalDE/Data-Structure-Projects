#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

template <typename T>
class node{
public:
    node<T>(T);
    node<T>() = default;
    T data;
    node<T>* prev;
    node<T>* next;
};

template <typename T>
class dLList{
public:
    dLList();
    ~dLList();

    bool empty() const; //is list empty?
    const T& front() const; //get front
    const T& back() const; //get trailor

    void addFront(T node); //add new node front
    void addBack(T node); //add new node in back

    void removeFront(); //remove first operation
    void removeBack(); //remove last operation

    int size(); //returns size

private:
    node<T>* header;  
    node<T>* trailer;

protected:
    void add(node<T>* v, node<T>* node);
    void remove(node<T>* v);
};

/*-------------------------
FUNCTIONS
------------------------------*/

/*-------------------------
create the node
------------------------------*/
//Empty node constructor
template <typename T>
node<T>::node(T data){
    this->data = data;
}

/*-------------------------
create the list
------------------------------*/
template <typename T>
dLList<T>::dLList(){
    header = new node<T>();
    trailer = new node<T>();
    header->next = trailer;
    trailer->prev = header;
}

template <typename T>
dLList<T>::~dLList(){
    while(!empty()) removeFront();
    delete header;
    delete trailer;
}

template <typename T>
bool dLList<T>::empty()const{
    return (header->next == trailer);
}

template <typename T>
const T& dLList<T>::front() const{;
    return header->next->data;
}

template <typename T>
const T& dLList<T>::back() const{
    return trailer->prev->data;
}

template <typename T>
void dLList<T>::add(node<T>* v, node<T>* e){
    e->next = v->next;
    v->next = e;
    e->prev = v;
    e->next->prev = e;
} 

template <typename T>
void dLList<T>::remove(node<T>* v){
    node<T>* u = v->prev;
    node<T>* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}

template <typename T>
void dLList<T>::addBack(T e){
    node<T>* v = new node<T>(e);
    add(trailer->prev, v);
}

template <typename T>
void dLList<T>::addFront(T e){
    node<T>* v = new node<T>(e);
    add(header, v);
}


template <typename T>
void dLList<T>::removeFront(){
    remove(header->next);
}

template <typename T>
void dLList<T>::removeBack(){
    remove(trailer->prev);
}

#endif