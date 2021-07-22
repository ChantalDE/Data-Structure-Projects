#include "dLinkedList.hpp"

#ifndef DEQUE_H
#define DEQUE_H

template <typename T>
class deque{
public:
    deque();
    bool empty() const;
    int size() const;

    const T& front() const;
    const T& back() const;
    void removeFront();
    void removeBack();
    void insertFront(const T&);
    void insertBack(const T&);

private:
    dLList<T> L;
    int n; //number of elements
    bool isOperator(deque);
};

/*-------------------------
Functions
------------------------------*/

template <typename T>
deque<T>::deque() : L(), n(0){}

template <typename T>
bool deque<T>::empty() const{
    return (n==0);
}

template <typename T>
const T& deque<T>::front() const{
    if (empty())
        throw("List is empty");
    return L.front();
}

template <typename T>
const T& deque<T>::back() const{
    if (empty())
        throw("List is empty");
    return L.back();
}

template <typename T>
int deque<T>::size() const{
    return n;
}

template <typename T>
void deque<T>::insertFront(const T& e){
    L.addFront(e);
    n++;
}

// insert new last element
template <typename T>
void deque<T>::insertBack(const T& e) {
    L.addBack(e);
    n++;
}

 // remove first element
template <typename T>
void deque<T>::removeFront(){
     if (empty())
        throw ("removeFront of empty deque");
    L.removeFront();
    n--;
}

// remove last element
template <typename T>
void deque<T>::removeBack(){
     if (empty())
        throw ("removeBack of empty deque");
    L.removeBack();
    n--;
}


#endif