#include <iostream>
#include "CalcList.hpp"

int main(){

    CalcList calc;   
    //calc.removeLastOperation();                     // Total == 0
    calc.newOperation(ADDITION, 10);      // Total == 10
    calc.newOperation(MULTIPLICATION, 5); // Total == 50
    calc.newOperation(SUBTRACTION, 15);   // Total == 35 
    calc.newOperation(DIVISION, 7);       // Total == 5 
    calc.removeLastOperation();           // Total == 35
    calc.newOperation(SUBTRACTION, 30);   // Total == 5
    calc.newOperation(ADDITION, 5);       // Total == 10 
    calc.removeLastOperation();           // Total == 5 
              
              // Should Return: 
              // 4: 35.00-30.00=5.00 
              // 3: 50.00-15.00=35.00 
              // 2: 10.00*5.00=50.00 
              // 1: 0.00+10.00=10.00 
              
    std::cout << calc.toString(2);
    calc.removeLastOperation();           // Total == 35
              
               // Should Return:
                // 3: 50-15=35
                // 2: 10*5=50
                // 1: 0+10=10
                
    std::cout << calc.toString(0);


return 0;
}