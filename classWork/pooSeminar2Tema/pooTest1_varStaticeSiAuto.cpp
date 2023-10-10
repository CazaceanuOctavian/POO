#include <iostream>

using namespace std;

void testStatic() {
    static int testStaticVar=51; 
    testStaticVar++;            
}                                
                                

void testAuto() {               
    auto testAutoVar='a';   
    testAutoVar++;             
}                             

int main() {
    testStatic();
    testStatic();
    testAuto();
    testAuto();
}