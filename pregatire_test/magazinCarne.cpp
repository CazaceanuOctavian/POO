#include <iostream>
#include <string.h>

using namespace std;

enum TipProdus {
    CARNE_PROASPATA = 1,
    CARNE_CONGELATA = 2,
    PRODUS_DIN_CARNE = 3
};

float ziCurenta = 164;

class Produs {
    private:
        TipProdus tip;
        char* denumireProdus;
        int stoc;
        float pretBucata;
        int dataExpirare;
        static int nrProduse;
    public:
        Produs() {
            this->tip = TipProdus::CARNE_PROASPATA;
            this->denumireProdus = nullptr;
            this->stoc = 0;
            this->pretBucata = 0;
            this->dataExpirare = 0;
        }

        Produs(TipProdus tip, char* denumireProdus, int stoc, float pretBucata, int dataExpirare) {
            this->tip = tip;

            if(denumireProdus!=nullptr) {
                this->denumireProdus = new char[strlen(denumireProdus) + 1];
                strcpy(this->denumireProdus, denumireProdus);
            }
            else
                this->denumireProdus = nullptr;
            
            if(stoc>0)
                this->stoc = stoc;
            else
                this->stoc = 0;

            if(pretBucata>0)
                this->pretBucata = pretBucata;
            else
                this->pretBucata = 0;

            if(dataExpirare>0 && dataExpirare<366)
                this->dataExpirare = dataExpirare;
            else
                this->dataExpirare = 0;
            
            Produs::nrProduse++;
        }

        Produs(const Produs& sursa) {
            this->tip = sursa.tip;

            if(sursa.denumireProdus!=nullptr) {
                this->denumireProdus = new char[strlen(sursa.denumireProdus) + 1];
                strcpy(this->denumireProdus, sursa.denumireProdus);
            }
            else
                this->denumireProdus = nullptr;
            
            if(sursa.stoc>0)
                this->stoc = sursa.stoc;
            else
                this->stoc = 0;

            if(sursa.pretBucata>0)
                this->pretBucata = sursa.pretBucata;
            else
                this->pretBucata = 0;

            if(sursa.dataExpirare>0 && sursa.dataExpirare<366)
                this->dataExpirare = sursa.dataExpirare;
            else
                this->dataExpirare = 0;
        }

        Produs& operator=(const Produs& sursa) {
            if(this != &sursa) {
                delete[] this->denumireProdus;
                this->denumireProdus = nullptr;

                this->tip = sursa.tip;

                if(sursa.denumireProdus!=nullptr) {
                    this->denumireProdus = new char[strlen(sursa.denumireProdus) + 1];
                    strcpy(this->denumireProdus, sursa.denumireProdus);
                }
                else
                    this->denumireProdus = nullptr;
                
                if(sursa.stoc>0)
                    this->stoc = sursa.stoc;
                else
                    this->stoc = 0;

                if(sursa.pretBucata>0)
                    this->pretBucata = sursa.pretBucata;
                else
                    this->pretBucata = 0;

                if(sursa.dataExpirare>0 && sursa.dataExpirare<366)
                    this->dataExpirare = sursa.dataExpirare;
                else
                    this->dataExpirare = 0;
            }
            return *this;
        }

        friend ostream& operator<<(ostream& ost, Produs& sursa) {
            ost<<"===================================="<<endl;
            cout<<"tip produs: "<< sursa.tip<<endl;
            if(sursa.denumireProdus!=nullptr)
                cout<<"denumire produs: "<<sursa.denumireProdus<<endl;
            else
                cout<<"ERR_DENUMIRE_PRODUS"<<endl;
            
            if(sursa.stoc>=0)
                cout<<"stoc: "<<sursa.stoc<<endl;
            else
                cout<<"ERR_STOC"<<endl;
            
            if(sursa.pretBucata>0)
                cout<<"pret per bucata: "<<sursa.pretBucata<<endl;
            else
                cout<<"ERR_PRET_PER_BUCATA"<<endl;
            
            if(sursa.dataExpirare>0 && sursa.dataExpirare<366)
                cout<<"data expirare: "<<sursa.dataExpirare<<endl;
            else
                cout<<"ERR_DATA_EXPIRARE"<<endl;
            ost<<"===================================="<<endl;
            return ost;
        }

        Produs& operator*=(float reducere) {
            if(this->dataExpirare == ziCurenta + 1)
                this->pretBucata*=reducere;
            return *this;
        }

        bool operator==(Produs& comp) {
            if(this->tip == comp.tip && strcmp(this->denumireProdus, comp.denumireProdus)==0 && this->stoc == comp.stoc && this->pretBucata == comp.pretBucata && this->dataExpirare == comp.dataExpirare)
                return true;
            return false;
        }

        void setDenumireProdus(char* denumireProdus) {
            if(denumireProdus!=nullptr) {
                delete[] this->denumireProdus;
                this->denumireProdus = nullptr;

                this->denumireProdus = new char[strlen(denumireProdus) + 1];
                strcpy(this->denumireProdus, denumireProdus);
            }
        }

        char* getDenumireProdus() {
            return this->denumireProdus;
        }

        void setTipProdus(TipProdus tip) {
            this->tip = tip;
        }

        TipProdus getTipProdus() {
            return this->tip;
        }

        void setPretBucata(float pretBucata) {
            if(pretBucata>0)
                this->pretBucata = pretBucata;
        }

        float getPretBucata() {
            return this->pretBucata;
        }

        void setNrBucati(int nrBucati) {
            if(nrBucati>0)
                this->stoc = nrBucati;
        }

        int getNrBucati() {
            return this->stoc;
        }



        ~Produs() {
            delete[] this->denumireProdus;
            this->denumireProdus = nullptr;
        }
};

class gestiuneCarne {
    private:
        float valoareTotala;
        int nrProduse;
        Produs* listaProduse;
    public:
        gestiuneCarne() {
            this->valoareTotala = 0;
            this->nrProduse = 0;
            this->listaProduse = nullptr;
        }

        gestiuneCarne(int nrProduse, Produs* listaProduse) {
            if(nrProduse>0)
                this->nrProduse = nrProduse;
            else
                this->nrProduse = 0;

            this->valoareTotala = 0;

            if(listaProduse!=nullptr && this->nrProduse>0) {
                this->listaProduse = new Produs[this->nrProduse];
                for(int i=0; i<this->nrProduse; i++) {
                    this->listaProduse[i] = listaProduse[i];
                    this->valoareTotala+=this->listaProduse[i].getPretBucata()*this->listaProduse[i].getNrBucati(); 
                }
            }
            else
                this->listaProduse = nullptr;
        }

         gestiuneCarne(const gestiuneCarne& sursa) {
            if(sursa.nrProduse>0)
                this->nrProduse = sursa.nrProduse;
            else
                this->nrProduse = 0;

            this->valoareTotala = 0;

            if(sursa.listaProduse!=nullptr && this->nrProduse>0) {
                this->listaProduse = new Produs[this->nrProduse];
                for(int i=0; i<this->nrProduse; i++) {
                    this->listaProduse[i] = sursa.listaProduse[i];
                    this->valoareTotala+=this->listaProduse[i].getPretBucata()*this->listaProduse[i].getNrBucati(); 
                }
            }
            else
                this->listaProduse = nullptr;
        }

        friend ostream& operator<<(ostream& ost, gestiuneCarne& sursa) {
            cout<<"-----------------------------------------------"<<endl;
            if(sursa.valoareTotala>0)
                cout<<"valoare totala stoc: "<<sursa.valoareTotala<<endl;
            else
                cout<<"ERR_VAL_TOTALA"<<endl;

            if(sursa.nrProduse>0)
                cout<<"numar produse: "<<sursa.nrProduse<<endl;
            else
                cout<<"ERR_NR_PRODUSE"<<endl;

            if(sursa.nrProduse>0 && sursa.listaProduse!=nullptr) {
                cout<<"avem urmatoarele produse: "<<endl;
                for(int i=0; i<sursa.nrProduse; i++)
                    cout<< sursa.listaProduse[i];
            }
            else
                cout<<"ERR_LISTA_PRODUSE"<<endl;
            cout<<"-----------------------------------------------"<<endl;
            return ost;
        }

        gestiuneCarne& operator+=(Produs produs) {
            bool gasit=false;
            for(int i=0; i<this->nrProduse; i++)
                if(strcmp(produs.getDenumireProdus(), this->listaProduse[i].getDenumireProdus())==0 && produs.getPretBucata()==this->listaProduse[i].getPretBucata() && produs.getTipProdus() == this->listaProduse[i].getTipProdus()) {
                    gasit = true;
                    listaProduse[i].setNrBucati(produs.getNrBucati() + listaProduse[i].getNrBucati());
                }
            if (gasit == false) {
                Produs* aux = new Produs[this->nrProduse + 1];
                for(int i=0; i<this->nrProduse; i++)
                    aux[i] = this->listaProduse[i];
                aux[this->nrProduse] = produs;

                delete[] this->listaProduse;
                this->listaProduse = nullptr;

                this->nrProduse++;
                this->listaProduse = new Produs[this->nrProduse];

                for(int i=0; i<this->nrProduse; i++)
                    this->listaProduse[i] = aux[i];

                delete[] aux;
                aux = nullptr;
                return *this;
            }
            return *this;
        }

        gestiuneCarne& operator()() {
            int cnt=0;
            for(int i=0; i<this->nrProduse; i++)
                if(listaProduse[i].getNrBucati()==0)
                    cnt++;

            if(this->nrProduse-cnt == 0) {
                this->nrProduse = 0;
                this->listaProduse = nullptr;
                return *this;
            }

            Produs* aux = new Produs[this->nrProduse - cnt];
            int k=0;
            for(int i=0; i<this->nrProduse; i++)
                if(listaProduse[i].getNrBucati()!=0) {
                    aux[k] = listaProduse[i];
                    k++;
                }
            
            delete[] this->listaProduse;
            this->listaProduse = nullptr;

            this->nrProduse-=cnt;
            this->listaProduse = new Produs[this->nrProduse];

            for(int i=0; i<this->nrProduse; i++)
                this->listaProduse[i] = aux[i];

            delete[] aux;
            aux = nullptr;
            return *this;
        }

        ~gestiuneCarne() {
            delete[] this->listaProduse;
            this->listaProduse = nullptr;
        }
};

int Produs::nrProduse = 0;

int main() {
    cout<<"hello world";
    Produs prodEmpty;
    cout<< prodEmpty;

    char* denumireCarne = new char[strlen("cotlet") + 1];
    strcpy(denumireCarne, "cotlet");

    Produs p1(TipProdus::CARNE_PROASPATA, denumireCarne, 3, 23, 165);
    cout<<p1;

    Produs p2 = p1;
    cout<<p2;

    if(p1==p2)
        cout<<"produsele sunt identice"<<endl;
    else
        cout<<"produsele sunt diferite"<<endl;

    p1*=0.6;
    cout<<p1;

    if(p1==p2)
        cout<<"produsele sunt identice"<<endl;
    else
        cout<<"produsele sunt diferite"<<endl;

    gestiuneCarne gestEmpty;
    cout<<gestEmpty;

    Produs p3 (TipProdus::CARNE_CONGELATA, denumireCarne, 0, 15, 183);
    Produs p4 (TipProdus::PRODUS_DIN_CARNE, denumireCarne, 1, 23, 210);
    
    char* denumireCarneNoua = new char[strlen("salam") + 1];
    strcpy(denumireCarneNoua, "salam");
    Produs p5(TipProdus::PRODUS_DIN_CARNE, denumireCarneNoua, 5, 11, 199);

    Produs lista[] = {p1, p3, p4};

    gestiuneCarne gest1(3, lista);
    cout<<gest1;

    gestiuneCarne gest2 = gest1;

    gest1+=p4;
    cout<<gest1;

    gest1+=p5;
    cout<<gest1;

    gest1();
    cout<<gest1;

    
}