#include <iostream>
#include <string.h>

using namespace std;

class Pers {
    //numai metodele clasei eu acees la campul salariu
    //nu pot sa il afisez pe consola daca nu am o functie de acces (get/set)
    //datele sunt incapsulate in tipul Pers.
protected:
    //pot deriva din clasele de baza indiferent care sunt 
    //marca nu este publica dar nu este nici privata
    //cine vrea sa dezvolte clasa persoana poate folosi int marca
    //functiile din clasa si functiile derivate din clasa
    const int marca;
    //================================//
    //se numeste valoarea formala
    //daca in constructor nu initializez marca va lua val default 100
    //altfel chiar daca marca=100 va lua val din constructor
    //int marca=100;
    //================================//
public:  
    //acces liber
    char nume[50];
private:
    //numai functiile din clasa o pot accesa
    double salariu;    
public:
    //constructor gol
    //Pers() {

    //}
    //constructor 
    //daca nu pun const char da eroare pentru ca:
    //ar modifica din apelant o valoare 
    //apelez cu o constanta nume 
    //: sugereaza ca e vorba de o derivare 
    //int x(10) --> utilizeaza constructorul tipului int
    //int x=10 --> initializeaza pe x cu 10
    //se folosesc constructorii altor clase (clasele de baza) pentru a intializa marca 
    //pentru ca marca nu o pot initaliza pt ca e const 
    //prin initializare si nu prin atribuire pot lucra pe const
    Pers(int m, const char* n, double s) : marca(m) {
        strcpy(nume, n);
        salariu = s;
    }
    //=========================//
    //o functie membra din clasa vede automant val din membrii obiectului
    //va da eroare pentru ca nu are nevoie de Pers &p pt ca il stie deja
    //ofstream& operator<<(ostream &ost, Pers &p) {
        //return ost;
    //}
    //========================//
    //friend:
    //declara ca functia este independenta (e straina de clasa)
    //are drepturi pe toate domeniile clasei
    friend ostream& operator<<(ostream &ost, Pers &pers) {
        ost <<"/n"<<pers.marca<<" "<<pers.nume<<" "<<pers.salariu<<" lei";
        return ost;
    }
    //vede datele din functie si le poate folosi fara sa i le dau ca parametrii
    void afiseaza() {
        //cout, cin, cerr... sunt obiecte deja definite in iostream, care nu trebuiesc instantiate
        cout <<"/n"<<marca<<" "<<nume<<" "<<salariu<<" lei";
        //printf("\n%d %s %lf", marca, nume, salariu);
    }

    //destructor a lui pers
    ~Pers() {

    }
};

int main() {
    //clasele trebuiesc construite prin constructori
    //fiecare field in clasa trebuie initializat
    //cand apelez Pers persoana1 se executa un default constructor facilitat de compilator
    //========================//
    //va afisa gibberish
    //Pers persoana1;
    //persoana1.afiseaza();
    //========================//
    Pers persoana1(120, "un nume", 5000);
    persoana1.afiseaza();

    //pot sa dau cout<<persoana1 din cauza la ostream
    cout<<endl<<persoana1;

    //Pers p2(120, "nume", 500) invoca direct constructorul
    //Pers p2 = Pers(120, "nume", 500) da valoarea pui p2 cu o constanta 
}