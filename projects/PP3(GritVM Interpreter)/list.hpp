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
    class IteratorList{
        public:
            T& operator*();      // reference to the element
            bool operator==(const IteratorList& p) const; // compare positions
            bool operator!=(const IteratorList& p) const;
            IteratorList& operator++();     // move to next position
            IteratorList& operator--();     // move to previous position
            friend class dLList;      // give dLList access

        private:
             IteratorList(node<T>* u);      // create from node
            node<T>* v;          // pointer to the node            
    };

    dLList();
    IteratorList begin() const;
    IteratorList end() const;

    int size(); //returns size
    bool empty() const; //is list empty?
    void clear();

    const T& back() const; //get trailor
    const T& front() const; //get header

    void emplace_back(T node); //add new node in back    
    void removeBack(); //remove last    

    void advance(IteratorList& currentInstruct, int jumpDistance);
  
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

/*------------------------
    ITERATOR FUNCTIONS
-------------------------*/

// constructor from node*
template <typename T>
dLList<T>::IteratorList::IteratorList(node<T>* u) {
     v = u; }

// reference to the element
template <typename T>
T& dLList<T>::IteratorList::operator*() {
    return v->data; }

// compare positions
template <typename T>
bool dLList<T>::IteratorList::operator==(const IteratorList& p) const {
 return v == p.v;
}

template <typename T>
bool dLList<T>::IteratorList::operator!=(const IteratorList& p) const{
 return v != p.v;
}

// move to next position
template <typename T>
dLList<T>::IteratorList& dLList<T>::IteratorList::operator++() {
 v = v->next;
 return *this;
}

// move to previous position
template <typename T>
dLList<T>::IteratorList& dLList<T>::IteratorList::operator--() {
 v = v->prev; return *this;
}


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
dLList<T>::dLList(){}

template <typename T>
bool dLList<T>::empty()const{
    return (header->next == trailer);
}

template <typename T>
const T& dLList<T>::back() const{
    return trailer->data;
}

template <typename T>
const T& dLList<T>::front() const{
    return header->data;
}

template <typename T>
void dLList<T>::emplace_back(T e){
    if(empty()){
        header = v;
    }
    node<T>* v = new node<T>(e);
    add(trailer, v);
    trailer = v;
}

template <typename T>
void dLList<T>::add(node<T>* v, node<T>* e){
    e->next = v->next;
    v->next = e;
    e->prev = v;
    e->next->prev = e;
} 

template <typename T>
void dLList<T>::clear(){
    while(!empty()) removeBack();
}

template <typename T>
void dLList<T>::removeBack(){
    remove(trailer);
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
dLList<T>::IteratorList dLList<T>::begin() const{
    return IteratorList(header);
}

template <typename T>
dLList<T>::IteratorList dLList<T>::end() const{
    return IteratorList(trailer->next);
}

template <typename T>
void dLList<T>::advance(IteratorList& iter, int d){
    if(d > 0){
        while(d--){
            ++iter;
        }
    }
    else{
        while(d++){
            --iter;
        }
    }
}
#endif