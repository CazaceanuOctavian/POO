#include <iostream>
#include <string.h>

using namespace std;

class Plantatie  {
    private:
        const int id;
        char* adresa;
        int nrPomi;
        int *varsta;
        static int varstaMinimRod;

        char* specieCopac;
        float pretPlantare;
    public:
        Plantatie(const int id) : id(id){
            this->adresa=nullptr;
            this->nrPomi=0;
            this->varsta=nullptr;
            this->specieCopac=nullptr;
            this->pretPlantare=0;
        }

        Plantatie(const int id, char* adresa, int nrPomi, int* varsta, char* specieCopac, float pretPlantare) : id(id) {
            if(adresa!=nullptr) {
                this->adresa = new char[strlen(adresa) + 1];
                strcpy(this->adresa, adresa);
            }
            else
                this->adresa=nullptr;
            if(nrPomi>0)
                this->nrPomi=nrPomi;
            else
                this->nrPomi=0;
            if(this->nrPomi>0 && varsta!=nullptr) {
                this->varsta=new int[this->nrPomi];
                for(int i=0; i<this->nrPomi; i++)
                    this->varsta[i] = varsta[i]; 
            }
            else 
                this->varsta=nullptr;
            if(specieCopac!=nullptr) {
                this->specieCopac= new char[strlen(specieCopac) + 1];
                strcpy(this->specieCopac, specieCopac);
            }
            if(pretPlantare>0)
                this->pretPlantare=pretPlantare;
            else
                this->pretPlantare=0;
        }

        Plantatie(Plantatie& sursa) : id(sursa.id) {
            cout<<"COPY CONSTURCTOR"<<endl;
            if(this != &sursa) {
                if(adresa!=nullptr) {
                    this->adresa = new char[strlen(sursa.adresa) + 1];
                    strcpy(this->adresa, sursa.adresa);
                }
                else
                    this->adresa=nullptr;
                if(sursa.nrPomi>0)
                    this->nrPomi=sursa.nrPomi;
                else
                    this->nrPomi=0;
                if(this->nrPomi>0 && sursa.varsta!=nullptr) {
                    this->varsta=new int[this->nrPomi];
                    for(int i=0; i<this->nrPomi; i++)
                        this->varsta[i] = sursa.varsta[i]; 
                }
                else 
                    this->varsta=nullptr;
                if(sursa.specieCopac!=nullptr) {
                    this->specieCopac= new char[strlen(sursa.specieCopac) + 1];
                    strcpy(this->specieCopac, sursa.specieCopac);
                }
                if(sursa.pretPlantare>0)
                    this->pretPlantare=sursa.pretPlantare;
                else
                    this->pretPlantare=0;
            }
        }

        Plantatie& operator=(Plantatie& sursa) {
            cout<<"OPERATOR ="<<endl;
            delete[] this->varsta;
            this->varsta=nullptr;

            delete[] this->adresa;
            this->adresa=nullptr;

            delete[] this->specieCopac;
            this->specieCopac=nullptr;

            if(adresa!=nullptr) {
                this->adresa = new char[strlen(sursa.adresa) + 1];
                strcpy(this->adresa, sursa.adresa);
            }
            else
                this->adresa=nullptr;
            if(sursa.nrPomi>0)
                this->nrPomi=sursa.nrPomi;
            else
                this->nrPomi=0;
            if(this->nrPomi>0 && sursa.varsta!=nullptr) {
                this->varsta=new int[this->nrPomi];
                for(int i=0; i<this->nrPomi; i++)
                    this->varsta[i] = sursa.varsta[i]; 
            }
            else 
                this->varsta=nullptr;
            if(sursa.specieCopac!=nullptr) {
                this->specieCopac= new char[strlen(sursa.specieCopac) + 1];
                strcpy(this->specieCopac, sursa.specieCopac);
            }
            if(sursa.pretPlantare>0)
                this->pretPlantare=sursa.pretPlantare;
            else
                this->pretPlantare=0;
            return *this;
        }

        friend ostream& operator<<(ostream& out, Plantatie& sursa) {
            cout<<"======================================="<<endl;
            cout<<"id: "<<sursa.id<<endl;
            if(sursa.adresa!=nullptr)
                cout<<"adresa: "<<sursa.adresa<<endl;
            cout<<"numarPomi: "<<sursa.nrPomi<<endl;
            if(sursa.nrPomi>0 && sursa.varsta!=nullptr) {
            cout<<"varsta pomilor este de: ";
                for(int i=0; i<sursa.nrPomi; i++)
                    cout<<sursa.varsta[i] << " | ";
            }
            cout<<endl;
            if(sursa.specieCopac!=nullptr)
                cout<<"specieCopac: "<<sursa.specieCopac<<endl;
            if(sursa.pretPlantare>=0)
                cout<<"pretPlantare: "<<sursa.pretPlantare<<endl;
            cout<<"varsta minim rod: " << Plantatie::varstaMinimRod<<endl;
            cout<<"======================================="<<endl;
            return out;
        }

        //cum se face citirea pentru id
        friend istream& operator>>(istream& in, Plantatie& sursa) {
            delete[] sursa.varsta;
            sursa.varsta=nullptr;

            delete[] sursa.adresa;
            sursa.adresa=nullptr;

            delete[] sursa.specieCopac;
            sursa.specieCopac=nullptr;

            string buffer;
            cout<<"adresa: ";
            in>>buffer;
            sursa.adresa=new char[buffer.size() + 1];
            strcpy(sursa.adresa, buffer.data());
            cout<<"nr pomi: ";
            in>>sursa.nrPomi;

            if(sursa.nrPomi>0) {
                cout<<"pomii au varsta: ";
                sursa.varsta=new int[sursa.nrPomi];
                for(int i=0; i<sursa.nrPomi; i++)
                    in>>sursa.varsta[i];
            }

            cout<<"specie copac: ";
            in>>buffer;
            sursa.specieCopac = new char[buffer.size() + 1];
            strcpy(sursa.specieCopac, buffer.data());

            cout<<"cost plantare: ";
            in>>sursa.pretPlantare;

            return in;
        }

        int operator()() {
            cout<<"CAST OPERATOR";
            int cnt=0;
            for(int i=0; i<this->nrPomi; i++)
                if(this->varsta[i]>=Plantatie::varstaMinimRod)
                    cnt++;
            return cnt;
        }

        Plantatie operator+(int nrPomi) {
            int* nouVarsta = new int[this->nrPomi + nrPomi];
            int medie =0;
            for(int i=0; i<this->nrPomi; i++)
                medie+=this->varsta[i];
            medie/=this->nrPomi;
            for(int i=0; i<this->nrPomi + nrPomi; i++) {
                if(i<this->nrPomi)
                    nouVarsta[i]=this->varsta[i];
                else
                    nouVarsta[i]=medie;
            }
            delete[] this->varsta;
            this->varsta=nullptr;

            this->nrPomi+=nrPomi;
            this->varsta=new int[this->nrPomi];

            for(int i=0; i<this->nrPomi; i++)
                this->varsta[i] = nouVarsta[i];

            delete[] nouVarsta;
            nouVarsta=nullptr;

            Plantatie rez = *this;

            return rez;
        }

        //returneaza adev daca toti pomii din a sunt mai mari ca varsta decat cei din b
        bool operator>(Plantatie &plt) {
            bool rez=true;
            if(this->varsta!=nullptr && plt.varsta!=nullptr) {
                for(int i=0; i<this->nrPomi; i++)
                    for(int j=0; j<plt.nrPomi; j++) 
                        if(this->varsta[i]<=plt.varsta[j])
                            return false;
            return true;
            }
            cerr<<"nu au ambele plantatii vector de varsta";
            return false;
        }

        bool operator==(Plantatie plt) {
            if(this->id==plt.id && strcmp(this->adresa, plt.adresa) == 0 && strcmp(this->specieCopac, plt.specieCopac)==0 && this->pretPlantare == plt.pretPlantare
            && this->nrPomi == plt.nrPomi)
                for(int i=0; i<this->nrPomi; i++)
                    if(this->varsta[i]!=plt.varsta[i])
                        return 0;
            return 1;
        }

        //inmulteste cu un int pretul de plantare
        Plantatie operator*=(int x) {
            this->pretPlantare*=x;
            return *this;
        }

        //adauga nrArbori de arbori care fiecare au varsta 0
        Plantatie operator+=(int nrArbori) {
            int* nouVarsta = new int[this->nrPomi + nrArbori];
            for(int i=0; i<this->nrPomi + nrArbori; i++) {
                if(i<this->nrPomi)
                    nouVarsta[i]=this->varsta[i];
                else
                    nouVarsta[i]=0;
            }
            delete[] this->varsta;
            this->varsta=nullptr;

            this->varsta=new int[this->nrPomi + nrArbori];
            this->nrPomi+=nrArbori;

            for(int i=0; i<this->nrPomi; i++)
                this->varsta[i] = nouVarsta[i];

            delete[] nouVarsta;
            nouVarsta=nullptr;

            return *this;
        }

        //extrage varsta unui copac din plantatie
        int operator[](int pozitie) {
            return this->varsta[pozitie];
        }

        void setAdresa(char* adresa) {
            delete[] this->adresa;
            this->adresa=nullptr;

            this->adresa= new char[strlen(adresa) + 1];
            strcpy(this->adresa, adresa);
        }

        char* getAdresa() {
            return this->adresa;
        }

        void setVarsta(int* varsta, int nrPomi) {
            delete[] this->varsta;
            this->varsta=nullptr;
            if(nrPomi>0)
                this->nrPomi=nrPomi;
            else
                this->nrPomi=0;
            this->varsta=new int[this->nrPomi];
            for(int i=0; i<this->nrPomi; i++)
                this->varsta[i] = varsta[i];
        }

        int* getVarsta() {
            return this->varsta;
        }

        int getVarstaMinima(int varstaMin) {
            int cnt=0;
            for(int i=0; i<this->nrPomi; i++)
                if(this->varsta[i]==varstaMin)
                    cnt++;
            return cnt;
        }

        ~Plantatie() {
            delete[] this->varsta;
            this->varsta=nullptr;

            delete[] this->adresa;
            this->adresa=nullptr;

            delete[] this->specieCopac;
            this->specieCopac=nullptr;
        }
};


bool operator==(const Plantatie& pl1, const Plantatie& pl2) {
    return pl1 == pl2;
}

int Plantatie::varstaMinimRod = 3;

int main() {
    char* adresaPlt=new char[strlen("comisani") + 1];
    strcpy(adresaPlt, "comisani");

    char* specieCopac = new char[strlen("dud") + 1];
    strcpy(specieCopac, "dud");

    int* varstaPlt= new int[3];
    varstaPlt[0] = 5;
    varstaPlt[1] = 3;
    varstaPlt[3] = 10;
    Plantatie plt1(2, adresaPlt, 3, varstaPlt, specieCopac, 70);
    cout<<plt1;

    Plantatie plt2 = plt1;
    cout<<plt2;

    Plantatie plt3(10);
    plt3 = plt1;
    cout<<plt3;

    int* varstaPltCmp = new int[3];
    varstaPltCmp[0]=10;
    varstaPltCmp[1]=7;
    varstaPltCmp[2]=11;
    Plantatie pltCmp(2, adresaPlt, 3, varstaPltCmp, specieCopac, 90);
    bool rezCmp = pltCmp > plt1;
    cout<<"rezultat comparare: "<< rezCmp<<endl;
    cout<<endl;

    int x = plt1();
    cout<<"rezultat cast: "<<x<<endl;

    cout<<endl;
    Plantatie rez = plt1 + 3;
    cout<<"rezultat +: "<<rez;
    cout<<endl;

    if(plt1 == pltCmp)
        cout<<"operator cmp BOOL = TRUE"<<endl;
    else    
        cout<<"operator cmp BOOL = FALSE"<<endl;

    cout<<"operator *=";
    pltCmp*=3;
    cout<<pltCmp;
    cout<<endl;

    cout<<"operator []: ";
    int z=pltCmp[0];
    cout<<z;
    cout<<endl;

    cout<<"operator +=:";
    pltCmp+=3;
    cout<<pltCmp;
    cout<<endl;


    int y=plt1.getVarstaMinima(3);
    cout<<y;

}