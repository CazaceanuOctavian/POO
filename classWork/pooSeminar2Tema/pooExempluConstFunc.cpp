#include <iostream>

using namespace std;

class MyClass {
private:    
   int myVar=3;
public:
    int calcPatrat(int x) const {
        //eroare pentru ca modifica o variabila membra a clasei
        //myVar++;  
        x++;
        return x*x;
    }
    const int calcPatrat2(int x) {
        myVar++;
        x++;
        return x;
    }
};

int main() {
    MyClass y;
    cout<<y.calcPatrat(3);
    int x = y.calcPatrat2(4);
}