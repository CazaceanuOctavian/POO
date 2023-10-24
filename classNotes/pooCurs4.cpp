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
    Pers() {

    }

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
        for(int i=0; i<pers.nrJoburi; i++) {
            ost << pers.pVenit[i] << " ";
        }
        return ost;
    }

    ~Pers() {
        if(pVenit!=nullptr)
            delete[] pVenit;
    }

    //supraincarcare &
    //p1=p2 unde p2 este sursa
    //p1 nonconst
    //pun const ca sa protejez sursa pt ca nu vreau sa o prelucrez
    Pers & operator =(const Pers &sursa) {
        //protectie la autoasignare
        //la autoasignare dezaloc si incerc sa copiez il el insusi o valoare dezalocata
        if(this!=&sursa) {
            this->salariu=sursa.salariu;
            //ma asigur ca daca p1 avea deja valori le dezaloc pt nu avea memory leak
            //daca preiau direct si el avea deja valori ele vor ramane in memorie si nu
            //voi avea acces la ele 
            if(pVenit!=nullptr)
                delete[] pVenit;
            if(nrJoburi>0) {
                pVenit = new double[nrJoburi];
                for(int i=0; i<nrJoburi; i++)
                    pVenit[i] = sursa.pVenit[i];
            }
        else {
            cerr << "ai incercat sa autoasignezi >:(";
        }
        }
    }

    Pers(Pers &sursa) : marca(sursa.marca) {
        salariu = sursa.salariu;
        strcpy(nume, sursa.nume);
        if(nrJoburi>0) {
            pVenit=new double[nrJoburi];
            for(int i=0; i< nrJoburi; i++)
                pVenit[i] = sursa.pVenit[i];
        }
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

    //===========================================//
    //incarc zona de memorie in aux
    //variabilei membru al functiei dezaloc zona de memorie
    //aloc o noua zona de memroie cu una mai mare
    //copiez din zona aux in zona functiei membre
    //dezaloc aux
    //evit memoy leak!!
    void addJob(double v) {
        double* aux = pVenit; nrJoburi++;
        pVenit = new double[nrJoburi];
        for(int i=0; i<nrJoburi-1; i++)
            pVenit[i] = aux[i];
        pVenit[nrJoburi-1] = v;
        if(aux!=nullptr)
            delete[] aux; 
    }

    double salariu() const {
        return salariu;
    }
};
//initializare marca
int Pers::nrPers=0;

int main() {
    Pers p1("nume", 5000);
    //scrie si marca 
    //s-ar putea sa ma minta de ex atunci cand este apelat constructor de copiere
    cout << p1;

    //==========================================//
    //obiectul constrat nu poate fi modificat nici pe parti 
    //oc.salariu=1000 --> err
    //nu pot nici sa invoc metode 
    //cout << oc.getSalariu();
    //ca sa mearga trebuie sa scriu double getSalariu() const {}
    //si atunci merge
    const Pers obiectConstant;
    Pers obicetVariabil;
}