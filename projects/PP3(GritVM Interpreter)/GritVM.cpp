#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>

#include "GritVM.hpp"


GritVM::GritVM(){}

STATUS GritVM::load (const std::string filename, const std::vector<long> &initialMemory){
    machineStatus = WAITING;
    dataMem = initialMemory;

    std::ifstream file;
    std::string line;
    file.open(filename);
    
    if(file.is_open()){
        while(getline(file, line)){
            //filter out commends and white space
            if (line[0] == '#' || line.length() == 0 || line[0] == ' '){
            }            
            else{
                Instruction inst = GVMHelper::parseInstruction(line);                
                instructMem.emplace_back(inst);
            }           
        }
        file.close();
    }
    else{
        throw("cannot open file");
        machineStatus = ERRORED;
        return machineStatus;
    }
    machineStatus = READY;
    return machineStatus;
}

//his method starts the evaluation of the instructions. Returns the current machine status. 
STATUS GritVM::run(){
    if(machineStatus != READY){
        return machineStatus;
    }
    machineStatus = RUNNING;
    long jumpDistance = 0;
    for(auto currentInstruct = instructMem.begin(); machineStatus == RUNNING; std::advance(currentInstruct, jumpDistance)){
        std::string output = GVMHelper::instructionToString(currentInstruct->operation);
        std::cout << output << std::endl;
        jumpDistance = evaluator(*currentInstruct);
    }
    return machineStatus;
}

//Sets the accumulator to 0, clears the dataMem and instructMem, sets the machineStatus to WAITING.
STATUS GritVM::reset(){
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    machineStatus = WAITING;
    return machineStatus;
}

long GritVM::evaluator(Instruction ins){
     //std::string output = GVMHelper::instructionToString(ins.operation);
     //std::cout << output << std::endl;
    switch(ins.operation){
    // Accumulator Functions
        case CLEAR: {accumulator = 0; return 1;}

    // Data Memory Management Functions
        case AT: {accumulator = dataMem.at(ins.argument); return 1;}
        case SET: {dataMem.at(ins.argument) = accumulator; return 1;}
        case INSERT: {dataMem.insert(dataMem.begin() + ins.argument, accumulator); return 1;}
        case ERASE: {dataMem.erase(dataMem.begin() + ins.argument); return 1;}

    // Accumulator Maths with a constant
        case ADDCONST: {accumulator+=ins.argument; return 1;}
        case SUBCONST: {accumulator-=ins.argument; return 1;}
        case MULCONST: {accumulator*=ins.argument; return 1;}
        case DIVCONST: {accumulator/=ins.argument; return 1;}

    // Accumulator Maths with a memory location
        case ADDMEM: {accumulator+=dataMem.at(ins.argument); return 1;}
        case SUBMEM: {accumulator-=dataMem.at(ins.argument); return 1;}
        case MULMEM: {accumulator*=dataMem.at(ins.argument); return 1;}
        case DIVMEM: {accumulator/=dataMem.at(ins.argument); return 1;}

    // Instruction Jump Functions
        case JUMPREL: {return ins.argument;}
        case JUMPZERO:{if(accumulator == 0){
                        return ins.argument;
                    }
                    else{
                        return 1;
                    }
                }
                
        case JUMPNZERO:{if (accumulator != 0){
                            return ins.argument;
                        }
                        else{
                            return 1;
                        }
                     }                   

    // Misc Functions
        case NOOP:{ return 1;}
        case HALT:  {machineStatus = HALTED; return 0;}
        case OUTPUT: {std::cout << accumulator; return 1;}
        case CHECKMEM:   {if(dataMem.size() < ins.argument){
                            std::cout << "not enough mem" << std::endl;
                            machineStatus = ERRORED;
                            return 0;
                         }
                         else{
                            return 1;
                         }
                        }                 

    // USE ONLY FOR BAD TRANSLATIONS READS (Ex: Typos in gvm file)
       case UNKNOWN_INSTRUCTION:{ machineStatus = UNKNOWN; return 0;}
       default:{machineStatus = UNKNOWN; return 0;}
    }  
}

void GritVM::printVM(bool printData, bool printInstruction) {
    std::cout << "****** Output Dump ******" << std::endl;
    std::cout << "Status: " << GVMHelper::statusToString(machineStatus) << std::endl;
    std::cout << "Accumulator: " << accumulator << std::endl;
    if (printData) {
        std::cout << "*** Data Memory ***" << std::endl;
        int index = 0;
        std::vector<long>::iterator it = dataMem.begin();
        while(it != dataMem.end()) {
                long item = (*it);
                std::cout << "Location " << index++ << ": " << item << std::endl;
                it++;
        }
    }
    if (printInstruction) {
        std::cout << "*** Instruction Memory ***" << std::endl;
        int index = 0;
        std::list<Instruction>::iterator it = instructMem.begin();
        while(it != instructMem.end()) {
            Instruction item = (*it);
            std::cout << "Instruction " << index++ << ": " << GVMHelper::instructionToString(item.operation) << " " << item.argument << std::endl;
            it++;
        }
    }
}


std::vector<long> GritVM::getDataMem(){
    return dataMem;
}
