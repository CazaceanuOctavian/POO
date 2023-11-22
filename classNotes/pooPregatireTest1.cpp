#include <iostream>
#include <string.h>

using namespace std;

class Sejur {
    private:
        unsigned int id;
        char *destinatie;
        float pretBaza;
        int nrExcursiiOptionale;
        float *pretExcursie;

        int nrPersoaneSejur;
        char** numePersoaneSejur;

    public:
        Sejur() {
            this->id=0;
            this->destinatie=nullptr;
            this->pretBaza=0;
            this->nrExcursiiOptionale=0;
            this->pretExcursie=nullptr;
            this->nrPersoaneSejur=0;
            this->numePersoaneSejur=nullptr;
        }

        //constructor cu un parametru
        Sejur(int id) {
            if(id>0) {
                this->id=id;
            }
            else
                cerr<<"id-ul dat este invalid";
        }

        //constructor cu toti parametrii
        Sejur(int id, char* destinatie, float pretBaza, int nrExcursiiOptionale, float* pretExcursie, int nrPersoaneSejur, char** numePersoaneSejur) {
            cout<<"APEL CONSTRUCTOR CU TOTI PARAMETRII"<<endl;
            if(id>0)
                this->id=id;
            if(destinatie!=nullptr) {
                this->destinatie= new char[strlen(destinatie) + 1]; 
                strcpy(this->destinatie, destinatie);
            }
            this->pretBaza=pretBaza;
            if(nrExcursiiOptionale>0)
                this->nrExcursiiOptionale=nrExcursiiOptionale;
            if(nrExcursiiOptionale>0 && pretExcursie!=nullptr)
                this->pretExcursie = new float[nrExcursiiOptionale];
                for(int i=0; i<this->nrExcursiiOptionale; i++)
                    this->pretExcursie[i] = pretExcursie[i];
            if(nrPersoaneSejur>0)
                this->nrPersoaneSejur=nrPersoaneSejur;
             if(this->nrPersoaneSejur>0 && numePersoaneSejur!=nullptr) {
                this->numePersoaneSejur = new char*[this->nrPersoaneSejur];
                for(int i=0; i<nrPersoaneSejur; i++) {
                    this->numePersoaneSejur[i] = new char[strlen(numePersoaneSejur[i]) + 1];
                    strcpy(this->numePersoaneSejur[i], numePersoaneSejur[i]);
                }
            }
        }

        //constructor de copiere
        Sejur(Sejur &sursa) {
             cout<<"APEL CONSTRUCTOR DE COPIERE"<<endl;
            if(sursa.id>0)
                this->id=sursa.id;
            if(sursa.destinatie!=nullptr) {
                this->destinatie = new char[strlen(sursa.destinatie) + 1];
                strcpy(this->destinatie, sursa.destinatie);
            }
            this->pretBaza=sursa.pretBaza;
            if(sursa.nrExcursiiOptionale>0)
                this->nrExcursiiOptionale=sursa.nrExcursiiOptionale;
            if(sursa.nrExcursiiOptionale>0 && sursa.pretExcursie!=nullptr)
                this->pretExcursie = new float[sursa.nrExcursiiOptionale];
                for(int i=0; i<this->nrExcursiiOptionale; i++)
                    this->pretExcursie[i] = sursa.pretExcursie[i];
            if(sursa.nrPersoaneSejur>0)
                this->nrPersoaneSejur=sursa.nrPersoaneSejur;
            if(this->nrPersoaneSejur>0 && sursa.numePersoaneSejur!=nullptr) {
                this->numePersoaneSejur = new char*[this->nrPersoaneSejur];
                for(int i=0; i<this->nrPersoaneSejur; i++) {
                    this->numePersoaneSejur[i] = new char[strlen(sursa.numePersoaneSejur[i]) + 1];
                    strcpy(this->numePersoaneSejur[i], sursa.numePersoaneSejur[i]);
                }
            }
        }

        Sejur& operator=(const Sejur& sursa) {
            cout<<"APEL OPERATOR ="<<endl;
            if(this != &sursa) {
                delete[] destinatie;
                this->destinatie=nullptr;
                delete[] pretExcursie;
                this->pretExcursie=nullptr;

                for(int i=0; i<nrPersoaneSejur; i++)
                    delete[] this->numePersoaneSejur[i];
                delete[] this->numePersoaneSejur;

                if(sursa.id>0)
                    this->id=sursa.id;
                if(sursa.destinatie!=nullptr) {
                    this->destinatie = new char[strlen(sursa.destinatie) + 1];
                    strcpy(this->destinatie, sursa.destinatie);
                }
                this->pretBaza=sursa.pretBaza;
                if(sursa.nrExcursiiOptionale>0)
                    this->nrExcursiiOptionale=sursa.nrExcursiiOptionale;
                if(sursa.nrExcursiiOptionale>0 && sursa.pretExcursie!=nullptr)
                    this->pretExcursie = new float[sursa.nrExcursiiOptionale];
                    for(int i=0; i<this->nrExcursiiOptionale; i++)
                        this->pretExcursie[i] = sursa.pretExcursie[i];
                if(sursa.nrPersoaneSejur>0)
                    this->nrPersoaneSejur=sursa.nrPersoaneSejur;
                if(this->nrPersoaneSejur>0 && sursa.numePersoaneSejur!=nullptr) {
                    this->numePersoaneSejur = new char*[this->nrPersoaneSejur];
                    for(int i=0; i<this->nrPersoaneSejur; i++) {
                        this->numePersoaneSejur[i] = new char[strlen(sursa.numePersoaneSejur[i]) + 1];
                        strcpy(this->numePersoaneSejur[i], sursa.numePersoaneSejur[i]);
                    }
                }            
            }
            return *this;
        }

        bool operator<=(Sejur sursa) {
            if(sursa.nrExcursiiOptionale>0 && sursa.pretExcursie!=nullptr) {
                int max=-1;
                for(int i=0; i<sursa.nrExcursiiOptionale; i++)
                    if(sursa.pretExcursie[i]>max)
                        max=sursa.pretExcursie[i];
            }
        }

        friend ostream& operator<<(ostream& out, const Sejur& sursa) {
            cout<<"=========================="<<endl;
            cout<<"id: "<<sursa.id << endl;
            if(sursa.destinatie!=nullptr)
                cout<<"destinatie: "<<sursa.destinatie <<endl;
            else
                cout<<"destinatie nealeasa"<<endl;
            cout<<"pretBaza: "<<sursa.pretBaza <<endl;
            cout<<"nrExcursiiOptionale: "<< sursa.nrExcursiiOptionale<< endl;
            if(sursa.nrExcursiiOptionale>0 && sursa.pretExcursie!=nullptr)
                for(int i=0; i<sursa.nrExcursiiOptionale; i++)
                    cout<<sursa.pretExcursie[i] << " | ";
            cout<<endl;
            cout<<"------------------------"<<endl;
            cout<<"nrPersSejur: "<<sursa.nrPersoaneSejur<<endl;
            if(sursa.nrPersoaneSejur>0 && sursa.numePersoaneSejur!=nullptr)
                for(int i=0; i<sursa.nrPersoaneSejur; i++)
                    cout<<sursa.numePersoaneSejur[i] << " | ";

            cout<<endl;
            cout<<"=============================="<<endl;
            return out;
        }

        friend istream& operator>>(istream& in, Sejur &sursa) {
            delete[] sursa.destinatie;
            sursa.destinatie=nullptr;
            delete[] sursa.pretExcursie;
            sursa.pretExcursie=nullptr;

            for(int i=0; i<sursa.nrPersoaneSejur; i++)
                delete[] sursa.numePersoaneSejur[i];
            delete[] sursa.numePersoaneSejur;
            sursa.numePersoaneSejur=nullptr;

            string buffer;
            cout<<"id: ";
            in>>sursa.id;
            if(sursa.id<0)
                sursa.id=0;
            cout<<"pretBaza: ";
            in>>sursa.pretBaza;
            if(sursa.pretBaza<0)
                sursa.pretBaza=0;
            cout<<"nrExcursiiOptionale: ";
            in>>sursa.nrExcursiiOptionale;
            if(sursa.nrExcursiiOptionale<0)
                sursa.nrExcursiiOptionale=0;
            cout<<"destinatie: ";
            in>>buffer;
            sursa.destinatie= new char[buffer.size() + 1];
            strcpy(sursa.destinatie, buffer.data());
            cout<<"pretul pentru cele "<< sursa.nrExcursiiOptionale << " excursii optionale este: ";
            if(sursa.nrExcursiiOptionale>0) {
                sursa.pretExcursie = new float[sursa.nrExcursiiOptionale];
                for(int i=0; i<sursa.nrExcursiiOptionale; i++)
                    in>>sursa.pretExcursie[i];
                    cout<< " | ";
            }
            cout<<"nrPersoaneSejur: ";
            in>>sursa.nrPersoaneSejur;
            if(sursa.nrPersoaneSejur<0)
                sursa.nrPersoaneSejur=0;

            cout<<"numele celor "<< sursa.nrPersoaneSejur << " persoane de sejur este: ";
            if(sursa.nrPersoaneSejur>0){
                sursa.numePersoaneSejur = new char*[sursa.nrPersoaneSejur];
                for(int i=0; i<sursa.nrPersoaneSejur; i++) {
                    in>>buffer;
                    sursa.numePersoaneSejur[i] = new char[buffer.size() + 1];
                    strcpy(sursa.numePersoaneSejur[i], buffer.data());
                }
            } 
        }

        Sejur operator--() {
            Sejur copie = *this;

            float min=9999;
            int cnt=0;
            for(int i=0; i<this->nrExcursiiOptionale; i++) 
                if(this->pretExcursie[i]<min) {
                    min=this->pretExcursie[i];
                    cnt++;
                }
            this->nrExcursiiOptionale=this->nrExcursiiOptionale-cnt;
            float* aux=new float[nrExcursiiOptionale];
            for(int i=0; i<this->nrExcursiiOptionale; i++)
                if(this->pretExcursie[i]!=min) {
                    aux[i] = this->pretExcursie[i];
                }

            delete[] this->pretExcursie;
            this->pretExcursie=nullptr;

            this->pretExcursie=new float[nrExcursiiOptionale];
            for(int i=0; i<this->nrExcursiiOptionale; i++)
                this->pretExcursie[i] = aux[i];

            return copie;
        }

        //metoda afisare
        void afiseazaSejur() {
            cout<<"=========================="<<endl;
            cout<<"id: "<<id << endl;
            if(this->destinatie!=nullptr)
                cout<<"destinatie: "<<this->destinatie <<endl;
            else
                cout<<"destinatie nealeasa"<<endl;
            cout<<"pretBaza: "<<pretBaza <<endl;
            cout<<"nrExcursiiOptionale: "<< nrExcursiiOptionale<< endl;
            if(this->nrExcursiiOptionale>0 && this->pretExcursie!=nullptr)
                for(int i=0; i<this->nrExcursiiOptionale; i++)
                    cout<<this->pretExcursie[i] << " | ";
            cout<<endl;
            cout<<"------------------------"<<endl;
            cout<<"nrPersSejur: "<<nrPersoaneSejur<<endl;
            if(this->nrPersoaneSejur>0 && this->numePersoaneSejur!=nullptr)
                for(int i=0; i<nrPersoaneSejur; i++)
                    cout<<this->numePersoaneSejur[i] << " | ";

            cout<<endl;
            cout<<"=============================="<<endl;
        }

        //metode get/set
        void setNrPersoaneSejur(int nrPersoaneSejur) {
            if(nrPersoaneSejur>0)
                this->nrPersoaneSejur=nrPersoaneSejur;
            else
                cerr<<"numar invalid de persoane introdus";
        }

        int getNrPersoaneSejur() {
            return this->nrPersoaneSejur;
        }

        void setNumePersoaneSejur(char** numePersoaneSejur) {
            if(this->nrPersoaneSejur>0) {
                this->numePersoaneSejur = new char*[this->nrPersoaneSejur];
                for(int i=0; i<nrPersoaneSejur; i++) {
                    this->numePersoaneSejur[i] = new char[strlen(numePersoaneSejur[i]) + 1];
                    strcpy(this->numePersoaneSejur[i], numePersoaneSejur[i]);
                }
            }
        }

        char** getNumePersoaneSejur() {
            return this->numePersoaneSejur;
        }

        int getNrMaximExcursii(float bugetMaximSejur) {
            int excursiiPermise=0;
            if(bugetMaximSejur>this->pretBaza) {
                bugetMaximSejur-=this->pretBaza;
            }
            else
                return 0;
            int *vec = new int[this->nrExcursiiOptionale];
            for(int i=0; i<this->nrExcursiiOptionale; i++)
                vec[i] = this->pretExcursie[i];

            for(int i=0; i<this->nrExcursiiOptionale; i++) {
                int min=9999;
                int aux=0;
                for(int j=0; j<this->nrExcursiiOptionale; j++)
                    if(vec[j]<min) {
                        min = vec[j];
                        aux = i;
                    }
                if(bugetMaximSejur-min>=0) {
                    bugetMaximSejur=bugetMaximSejur-min;
                    vec[aux]=10000;
                    excursiiPermise++;
                }
                else {
                    delete[] vec;
                    vec = nullptr;
                    return excursiiPermise;
                }
            }
            return excursiiPermise;
        }

    explicit operator float() {
        float pretTotal=0;
        for(int i=0; i<this->nrExcursiiOptionale; i++) {
            pretTotal+=this->pretExcursie[i];
        }
        return pretTotal + this->pretBaza;
    }

    //destructor
    ~Sejur() {
        delete[] destinatie;
        this->destinatie=nullptr;
        delete[] pretExcursie;
        this->pretExcursie=nullptr;

        for(int i=0; i<nrPersoaneSejur; i++)
            delete[] this->numePersoaneSejur[i];
        delete[] this->numePersoaneSejur;
        numePersoaneSejur=nullptr;
    }

};

int main() {
    char** listaPersSejur;
    listaPersSejur = new char*[3];
    listaPersSejur[0] = new char[strlen("daniel")+1];
    strcpy(listaPersSejur[0], "daniel");
    listaPersSejur[1] = new char[strlen("ana")+1];
    strcpy(listaPersSejur[1], "ana");

    Sejur x;
    x.setNrPersoaneSejur(2);
    x.setNumePersoaneSejur(listaPersSejur);
    x.afiseazaSejur();

    char** listaNoua = x.getNumePersoaneSejur();
    for(int i=0; i<2; i++)
        cout<< listaNoua[i];
    cout<<endl;

    //apel constructor toti parametrii
    char* destinatieCurenta = new char[strlen("thasos") + 1];
    strcpy(destinatieCurenta, "thasos");
    float* vecPretEx = new float[3];
    vecPretEx[0] = 20;
    vecPretEx[1] = 10;
    vecPretEx[2] = 10;

    Sejur sejurTotiParam(1, destinatieCurenta, 30, 3, vecPretEx, 2, listaPersSejur);
    sejurTotiParam.afiseazaSejur();

    cout<<"apel getNrMaxExcursii: ";
    //apel getNrMaxExcursii;
    cout<<sejurTotiParam.getNrMaximExcursii(50)<<endl;

    Sejur sejurCpyConstructor = sejurTotiParam;
    sejurCpyConstructor.afiseazaSejur();

    Sejur sejurOpEgal;
    sejurOpEgal = sejurTotiParam;
    sejurOpEgal.afiseazaSejur();

    cout<<"supraincarcare operator float: "<<endl;
    float total = (float)sejurTotiParam;
    cout<<total<<endl;

    sejurTotiParam = (float)5;

    cout<<"supraincarcare operator <<"<<endl;
    cout<<sejurTotiParam;

    //cout<<"supraincarcare opearot >>"<<endl;
    //cin>>sejurTotiParam;
    //sejurTotiParam.afiseazaSejur();

    cout<<"supraincarcare operator -- postdecrementare"<<endl;
    --sejurTotiParam;
    cout<<sejurTotiParam;
}