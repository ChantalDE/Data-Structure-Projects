#ifndef CALCLIST_H
#define CALCLIST_H

#include <string>
#include "CalcListInterface.hpp"


class CalcNode{
public:
    CalcNode();
    CalcNode(double, char, double);

private:
    double nTotal; //total
    char nFunction; // (-, +, *, /)
    double nOperand; // (amount 'added')
    CalcNode* prev;
    CalcNode* next;
    friend class CalcList;
};

class CalcList : public CalcListInterface{
public:
    CalcList();
    ~CalcList();

    bool empty() const; //is list empty?
    const CalcNode* front() const; //get front
    CalcNode* back() const; //get trailor

    void addFront(CalcNode* node); //add new node front
    void addBack(CalcNode* node); //add new node in back

    void removeFront(); //remove first operation
    void removeBack(); //remove last operation  
    
    virtual double total() const;
    virtual void newOperation(const FUNCTIONS func, const double operand);
    virtual void removeLastOperation();
    virtual std::string toString(unsigned short precision) const; //list of total operations

private:
    CalcNode* header;  
    CalcNode* trailer;
    double mTotal = 0;
    double step = 0;
    double operand;
    char function;

protected:
    void add(CalcNode* v, CalcNode* node);
    void remove(CalcNode* v);
};

#endif 