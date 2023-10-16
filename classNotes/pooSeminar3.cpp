
#include <iostream>
#include <string.h>

using namespace std;

class Student {
    private:
        char* nume;
        int nrNote;
        int note[20];
    protected:
        int varProtected;
    public: 
        int varPublic;
    //constructor gol
    //in constructorul gol incerc sa merg cat mai aproape de 0
    //si de null
    Student() {
        //ar fi mai bine sa folosesc nume=nullptr;
        //char* nume=nullptr;
        nume = new char[strlen("Anonim") + 1];
        strcpy(nume, "Anonim");
        int nrNote=0;
        //nu nevoie sa fac nimic pt note[20]
    }

    void afisare() {
        cout<<"__________________________________________"<<endl;
        cout<< "nume: " << nume << endl;
        cout<< "nrNote: " << note << endl;
        cout << "note: ";
        //nu pot sa dau if(nrNote == NULL)
        //folosesc nrNote == NULL la obiecte alocate dinamic
        if (nrNote > 0) {
            for(int i=0; i< nrNote; i++)
                cout << note[i] << " ";
        }
        else
            cout<<"---";
        cout<<"__________________________________________"<<endl;
    }
    //set-urile sunt bune pentru validare
    //de acum incolo in set-uri se fac validari
    void setNume(const char* nume_){
        if(nume_!=nullptr)
        //deep copy pentru ca nume e alocat dinamic;
        delete[] nume;
        //relativ optional 
        //folositor doar cand nu are loc pe heap si new da eroare
        nume = nullptr;
        nume = new char[strlen(nume_) + 1];
        strcpy(nume, nume_);
    }
    //char * pt ca e sir de caractere
    char* getNume() {
        return nume;
    }
};


//TEMA --> O ALTA CLASA care sa contine alocare statica
//alocare dinamica, vec numerici, vec sir char, boolean
//atribut de tip enumeratie(enum)
//se implementeaza const fara param, met de afisare, metode gettr/settr
//cu sens --> de ex nu are sens sa modific dimensiunea nr de note a 
//unui student. Nu exista setter pt dimensiunea vectorului.
//la fiecare setter valiari cu scop
//getnume de ce nu este corect *incalca principiul incapsularii.
//recap enum 
int main() {
    Student student;
    Student* ps = new Student();
    //la obiecte pointer trb sa pun ->
    //daca pun student. nu voi avea constructorul ca optiune
    //chiar daca e public pentru ca el a fost deja construit
    //nu are sens sa il mai construiesc inca o data
    
    //warning pt ca gigel e const string iar setterul 
    //asteapta string normal --> facem string-ul din setter const
    student.setNume("gigel");
    cout<<student.getNume();
    return 0;
}