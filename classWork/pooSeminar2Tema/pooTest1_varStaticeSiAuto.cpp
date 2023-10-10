#include <iostream>

using namespace std;

void testStatic() {
    static int testStaticVar='a'; //variabila static isi va retine valoarea 
    testStaticVar++;            //precedenta si la al doilea apel al functiei testStatic
}                               //adica va avea val 4 si apoi 5 
                                //face asta pt ca poate fi initializata doar o singura data cu 3
                                //in rest linia 6 nu face nimic 

void testAuto() {               
    auto testAutoVar='a';       //se reinitializeaza de fiecare data si este alocata dinamic   
    testAutoVar++;              //astfel la iesire din subprogram este distrusa
}                               //se adapteaza la tipul datei pe care il dai 
                                //daca testAutoVar='a' --> char, daca testAutoVar=37211 --> int

int main() {
    testStatic();
    testStatic();
    testAuto();
    testAuto();
}