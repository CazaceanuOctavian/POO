#include <iostream>

using namespace std;
//Strings
//constructori cu toti parametrii
//destructori
//constructori de copiere
//this
//TEST GRILA SAPT URM
class Facultate {
    //!daca se zice la test sir de caractere alocat dinamic --> forteaza sa folosim char* 
    //dezavantaj la string --> ocupa multi octeti chiar daca nu are nimic
    string denumire;
    int nrStudenti;
    int nrPersConducere;
    string* persConducere;  //char**

    public:
        Facultate() {
            cout<<"APEL CONSTRUCTOR FARA PARAM"<<endl;
            this->denumire="N/A";
            this->nrStudenti=0;
            this->nrPersConducere=0;
            this->persConducere=nullptr;
        }

        //se fac validari si aici la toate fieldurile
        Facultate(string denumire, int nrStudenti, int nrPersConducere, string* persConducere) {
            cout<<"APEL CONSTRUCTOR CU TOTI PARAM"<<endl;
            //se construieste obiectul de la adresa lui this cu val pe care le dau ca param
            this->denumire=denumire;
            this->nrStudenti=nrStudenti;
            //si denumorea si nrStud trb validat ca mai jos
            if(nrPersConducere>0 && persConducere!=nullptr) {
                this->nrPersConducere=nrPersConducere;
                this->persConducere=new string[this->nrPersConducere];
                for(int i=0; i<this->nrPersConducere; i++)
                    this->persConducere[i]=persConducere[i];
            }
            else {
                //ce e in constructorul gol
                this->nrPersConducere=0;
                this->persConducere=nullptr;
            }
        }
 
        void afisare() {
            cout<<"+++++++++++++++++++++++++++"<<endl;
            cout<<"Denumire: "<<this->denumire<<endl;
            cout<<"Nr studenti: "<<this->nrStudenti<<endl;
            cout<<"Nr pers conducere: "<<this->nrPersConducere<<endl;
            if(this->persConducere!=nullptr) {
                for(int i=0; i<this->nrPersConducere; i++)
                    cout<< this->nrPersConducere <<" ";
            }
            else {
                cout<<"N/A"<<endl;
            }
        }
        //transferam prin referinta nu ca sa optimizam, ci prin necesitate
        //am nevoie nu de o copie, ci de obiectul real pe care il copiez
        //pun const ca sa protejez
        //!!de ce in constructorul de copiere nu sunt total protejat total
        //sizeof!!
        Facultate(const Facultate &f) {
            cout<<"APEL CONSTRUCTOR COPY"<<endl;
            //se construieste obiectul de la adresa lui this cu val pe care le dau ca param
            this->denumire=f.denumire;
            this->nrStudenti=f.nrStudenti;
            //si denumorea si nrStud trb validat ca mai jos
            if(nrPersConducere>0 && persConducere!=nullptr) {
                this->nrPersConducere=f.nrPersConducere;
                this->persConducere=new string[this->nrPersConducere];
                for(int i=0; i<this->nrPersConducere; i++)
                    this->persConducere[i]=f.persConducere[i];
            }
            else {
                //ce e in constructorul gol
                this->nrPersConducere=0;
                this->persConducere=nullptr;
            }
        }
        //daca am alocare dinamic in clasa mea trebuie sa fac destructor
        //care sa imi dezaloce tipurile dinamice (ele sunt alocare in heap)
        //destructorul care vina de la compilator distruge doar stiva
        //se ocupa DOAR de dezalocarea ce tine de heap
        ~Facultate() {
            cout<<"APEL DESTRUCTOR";
            delete[] this->persConducere;
            //o pun pentru pointeri de tip facultate
            //pfacultate = new Facultate()
            //delete facultate
            //daca nu am persConducere = nullptr tot pot sa accesez
            this->persConducere=nullptr;
            
        }
};

int main() {
    //exista adresa obiectului opelator (this) care se trimite in metodele nonstatice
    //apeleaza constructorul gol din clasa;
    string prof[] = {"ana", "maria"};
    Facultate f1("ASE", 100, 2, prof);
    f1.afisare();
    //NU SE APELEAZA NICIUN CONSTRUCOTR;
    Facultate* pFacultate;
    //acum se apeleaza constructorul fara parametrii
    pFacultate = new Facultate();
    //se apeleaza constructor de copiere;
    //versiunea de la compilator a constructorului de copiere face shallow copy
    //a distrus deja zona la care a facut shallow copy si incearca sa dezaloce ceva ce a fost 
    //deja dezalocat
    //de aceea trebuie sa implementam constructor de copiere care sa faca deep copy;
    Facultate f3 = f1;
    f3.afisare();
}
//alta clasa cu alocare dinamica, cu constructor fara param, sau cu alti param
//de ex atributele care nu sunt in constructor le facem in setter
//restul
//2 metode de prelucrare  --> de ex luna cu cea mai mare disponibilitate la  tiruri,
//                        --> pretul cel mai mic la carti