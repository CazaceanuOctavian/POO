#include <iostream>
#include <string.h>

using namespace std;

class Pers {
protected:
    const int marca=1;
public:  
    char nume[50]="...";
    private:
    double salariu=1;    
public:
    Pers(int m, const char* n, double s) : marca(m) {
        strcpy(nume, n);
        salariu = s;
    }

    friend ostream& operator<<(ostream &ost, Pers &pers) {
        ost <<"/n"<<pers.marca<<" "<<pers.nume<<" "<<pers.salariu<<" lei";
        return ost;
    }
    void afiseaza() {
        cout <<"/n"<<marca<<" "<<nume<<" "<<salariu<<" lei";
    }
    //~ vine de la negare pe biti 
    ~Pers() {
        cout << nume << " a fost distrus" << endl;
    }
    //constructor de copiere
    //se floloseste la transfer prin valoare in functii
    Pers(Pers &sursa) : marca(sursa.marca) {
        salariu = sursa.salariu;
        strcpy(nume, sursa.nume);
    }
    //getter
    int getMarca() {
        return marca;
    }
    //setter
    void setNume(const char* pointerNume) {
        if(strlen(pointerNume)<49)
            strcpy(nume, pointerNume);
        else
            cerr<<"\nName 2 big";
    }
};

int main() {
    //==============//
    //referinte -- un pointer care se derefera automat
    //int &py=3 --> atribuire (la runtime)
    //int &py=3 --> initializare (la compilare)
    int y=20, &py=y;
    //echivalent cu y=7
    py=7;
    //p2=p1 tot initializare pt ca p2 nu exista
    Pers p1(200, "da", 30), p2=p1;
    //initializare prin constanta
    Pers p3 =Pers(200, "da", 1);
    p1.afiseaza();

    //forteaza durata de viata a variabilelor din paranteze
    //p10 este vizibil si alocat doar in paratnteze
    //cand iese din paranteze destructorul clasei este apelat
    {
        Pers p10(1020, "zece", 9000);
        Pers vp[]{Pers(100, "ceva", 2.0)};

        //daca il las asa am memory leak pt ca inca exista pers
        //dar se duce pp si nu mai am lant spre acel new pers
        Pers *pp = new Pers(5000, "pp", 3000);
        //evita memory leak 
        delete pp;
        //pot sa il modific pe p3 folosing pe pp
        //pp=&p3;
        Pers *vpp[] = {new Pers (5000, "vpp1", 3000), new Pers(5000, "vpp2", 3000)};
        //vpp ocupa doar 8 biti nu 2 pers;
        //cele 2 linii de mai jos sunt echivalente
        cout<<vpp[1]->nume;
        //devine obiect cand zic *vpp[1]
        (*vpp[1]).nume; 
    }
    
    //compilatorul pune default constructor/destructor/const de copiere
    Pers p1(p3); //echivalnet cu p1=p3;

}