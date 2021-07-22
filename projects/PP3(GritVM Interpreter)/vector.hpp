#include <iostream>
#include <stdexcept>

template <typename T>
class myVector{
public:
    class IteratorVector{
        public:
            T& operator*();      // reference to the element
            bool operator==(const IteratorVector& p) const; // compare positions
            bool operator!=(const IteratorVector& p) const;
            IteratorVector& operator++();     // move to next position
            IteratorVector& operator--();     // move to previous position
            friend class myVector;      // give myVector access

        private:
        IteratorVector(int i);
        int i; //index            
    };

    myVector();
    int size() const; //returns size 
    bool empty() const; //is vector empty? 
    
    T& operator[](int i); // element at index
    T& at(int i) throw(IndexOutOfBounds); // element at index

    void clear(); //removes all elements
    void insert(it, T); //inserts T @ it
    void erase(it);     //removes element @it

    myVector& operator=(const std::vector<T>& v){
        for(auto& val:v)
    }

    IteratorVector begin() const;
    IteratorVector end() const;
    
private:
    int capacity;
    int n; //# elements
    T* A; //store the elements
};


// constructor from node*
template <typename T>
myVector<T>::IteratorVector::IteratorVector(int index) {
    i = index;
}

// reference to the element
template <typename T>
T& myVector<T>::IteratorVector::operator*() {
    return A[i];
}

// compare positions
template <typename T>
bool myVector<T>::IteratorVector::operator==(const IteratorVector& p) const {
 return i == p.i;
}

template <typename T>
bool myVector<T>::IteratorVector::operator!=(const IteratorVector& p) const{
 return i != p.i;
}

// move to next position
template <typename T>
myVector<T>::IteratorVector& myVector<T>::IteratorVector::operator++(){
    i++;
    return *this;
}

// move to previous position
template <typename T>
myVector<T>::IteratorVector& myVector<T>::IteratorVector::operator--(){
    i--;
    return *this;
}


// constructor
template <typename T>
myVector<T>::myVector() : capacity(0), n(0), A(NULL) { }

// number of elements
template <typename T>
int myVector<T>::size() const{
    return n; }

// is vector empty?
template <typename T>
bool myVector<T>::empty() const{
    return size() == 0; }

// element at index
template <typename T>
T& myVector<T>::operator[](int i){
    return A[i]; }

// element at index (safe)
template <typename T>
T& myVector<T>::at(int i) throw(std::out_of_range) {
 if (i < 0 || i >= n) {
   throw std::out_of_range("illegal index in function at()");
 }
 return A[i];
}

template <typename T>
myVector<T>::IteratorVector myVector<T>::begin() const{
    return IteratorVector(0);
}

template <typename T>
myVector<T>::IteratorVector myVector<T>::end() const{
    return IteratorVector(size());
}


