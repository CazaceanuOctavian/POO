#include <iostream>

using namespace std;

//static --> nr total de pers dintr-o clasa
//nu are sens sa inumar intr-un obiect persoanele totale dintr-o clasa
//nu este al obiectului, este al clasei
//:: --> op de rezolutie
#include <iostream>
#include <string.h>

using namespace std;

class Pers {
protected:
    static int nrPersProt;
    const int marca=0;
public:  
    char nume[50]="anon";
    static int nrPers;
    int nrJoburi=0;
    double* pVenit = nullptr;
private:
    double salariu=10;    
public:
    Pers(const char* n, double s, int nrJ=0, double *pV) : marca(++nrPers) {
        strcpy(nume, n);
        salariu = s;
        if(nrJ>0)
            nrJoburi=nrJ;
            pVenit = new double[nrJoburi];
            for(int i=0; i<nrJoburi; i++)
                pVenit[i] = pV[i];
    }

    friend ostream& operator<<(ostream &ost, Pers &pers) {
        ost <<pers.marca<<" "<<pers.nume<<" "<<pers.salariu<<" lei" <<endl;
        ost <<"Venituri: ";
        for(int i=0; i<nrJoburi; i++) {
            ost << pers.pVenit[i] << " ";
        }
        return ost;
    }

    ~Pers() {
        if(pVenit!=nullptr)
            delete pVenit;
    }

    Pers(Pers &sursa) : marca(sursa.marca) {
        salariu = sursa.salariu;
        strcpy(nume, sursa.nume);
    }
    //getter
    int getMarca() {
        return marca;
    }

    static int getNrPers() {
        return nrPersProt;
    }

    //setter
    void setNume(const char* pointerNume) {
        if(strlen(pointerNume)<49)
            strcpy(nume, pointerNume);
        else
            cerr<<"\nName 2 big";
    }

    Pers(Pers& src) : marca(src.marca) {
        
    }
};
//initializare marca
int Pers::nrPers=0;

int main() {
    Pers p1("nume", 5000);
    //scrie si marca 
    //s-ar putea sa ma minta de ex atunci cand este apelat constructor de copiere
    cout << p1;
}