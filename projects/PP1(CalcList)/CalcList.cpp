/*----------------------------------
Chantal Espinosa
U6874-3089
Calculator script w/ undo function
------------------------------------*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "CalcList.hpp"

/*-------------------------
create the node
------------------------------*/
//Empty node constructor
CalcNode::CalcNode(){}

//node with paramters
CalcNode::CalcNode(double mTotal, char function, double operand){
    this->nTotal = mTotal;
    this->nFunction = function;
    this->nOperand = operand; 
}


/*-------------------------
create the list
------------------------------*/
CalcList::CalcList(){
    header = new CalcNode();
    trailer = new CalcNode();
    header->next = trailer;
    trailer->prev = header;

    header->nTotal = 0;
}
CalcList::~CalcList(){
    while(!empty()) removeFront();
    delete header;
    delete trailer;
}

bool CalcList::empty()const{
    return (header->next == trailer);
}

const CalcNode* CalcList::front() const{
    return header->next;
}

CalcNode* CalcList::back() const{
    return trailer->prev;
}

void CalcList::add(CalcNode* v, CalcNode* e){
    e->next = v->next;
    v->next = e;
    e->prev = v;
    e->next->prev = e;
} 

void CalcList::remove(CalcNode* v){
    CalcNode* u = v->prev;
    CalcNode* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}

void CalcList::addBack(CalcNode* e){
    add(trailer->prev, e);
    step++;
}

void CalcList::removeFront(){
    remove(header->next);
}

void CalcList::removeBack(){
    remove(trailer->prev);
    step--;
}



/*---------------------------
Calculator interface
-----------------------------*/

double CalcList::total() const{
    return mTotal;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand){
   
    switch(func){
        case ADDITION:{
            mTotal += operand; //store as variable, so accessable right away
            CalcNode* node  = new CalcNode (mTotal, '+', operand);
            addBack(node);
            break;
        }

        case SUBTRACTION:{
            mTotal -= operand;
            CalcNode* node  = new CalcNode (mTotal, '-', operand);
            addBack(node);
            break;
        }

        case MULTIPLICATION:{
            mTotal *= operand;
            CalcNode* node  = new CalcNode (mTotal, '*', operand);
            addBack(node);
            break;
        }

        case DIVISION:{
            if(operand == 0)
                throw std::runtime_error("Cannot divide by 0");
            mTotal /= operand;
            CalcNode* node  = new CalcNode (mTotal, '/', operand);
            addBack(node);
            break;
        }
    }
}

void CalcList::removeLastOperation(){
    if(empty())
        throw std::runtime_error("can't undo an operation in an empty list");
    removeBack();
    mTotal = trailer->prev->nTotal;
}
 
std::string CalcList::toString(unsigned short precision) const{
    int i = 1;
    CalcNode* u = trailer->prev;
    std::stringstream pv;
    
    i = step;
    while(u != header){
        pv.precision(precision);
        pv << std::fixed << i << ": " << u->prev->nTotal << u->nFunction  << u->nOperand << "=" <<  u->nTotal << std::endl;
        i--;
        u = u->prev;    
    }
    return pv.str();
}




