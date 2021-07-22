#ifndef GritVM_H
#define GritVM_H

#include <iostream>
#include <list>
#include <vector>

#include "GritVMBase.hpp"

class GritVM : public GritVMInterface{
public:
    GritVM();
    virtual STATUS load(const std::string filename, const std::vector<long> &initialMemory) override;
    virtual STATUS run() override;
    virtual std::vector<long> getDataMem() override;
    virtual STATUS reset() override;
    void printVM(bool printData, bool printInstruction);

    
private:
    std::vector<long> dataMem;
    std::list<Instruction> instructMem;
    std::list<Instruction>::iterator currentInstruct;   
    STATUS machineStatus = WAITING;
    long accumulator = 0;

    long evaluator(Instruction ins); //returns next place in mem
    std::list<Instruction>::iterator advance;
};

#endif
