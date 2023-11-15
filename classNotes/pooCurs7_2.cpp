#include <iostream>
//OPERATORI DE CAST
using namespace std;

class Student {
    private:
        float medie=10;
    public:
        string nume="Popescu";
    Student(string nume, float medie) : nume(nume), medie(medie) {

    }

    friend ostream& operator<<(ostream& ost, Student& s) {
        ost << s.nume << " are media "<<s.medie;
        return ost;
    }

    //sintaxa operatorului cast
    operator float() {
        return medie;
    }
};

int main() {
    Student s1("unu", 10);
    float m;
    //= cere conversie, adica studentul sa se converteasca la float 
    //cand spun m = s1 se apleaza operatorul cast 
    m = s1;
}