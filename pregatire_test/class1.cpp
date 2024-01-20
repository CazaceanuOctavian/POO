#include <iostream>
#include <string.h>

using namespace std;

class AgendaTelefon {
    private:
        const int id;
        char* consumator;
        int nrApeluri;
        int* durataConvorbirii;
        static int costMinut;

        char* provider;
        bool esteFix;
    public:
        AgendaTelefon(int id) : id(id) {
            cout<<"CONSTRUCTOR FARA PARAM"<<endl;
            this->consumator = nullptr;
            this->nrApeluri = 0;
            this->durataConvorbirii = 0;
            this->provider = nullptr;
            this->esteFix = false;
        }

        AgendaTelefon(int id, char* consumator, int nrApeluri,
                 int* durataConvorbirii, char* provider, bool esteFix) : id(id){
        cout<<"CONSTRUCTOR CU TOTI PARAM"<<endl;

        if(consumator != nullptr) {
            this->consumator = new char[strlen(consumator) + 1];
            strcpy(this->consumator, consumator);
        }

        if(nrApeluri > 0)
            this->nrApeluri = nrApeluri;
        else
            this->nrApeluri = 0;

        if(durataConvorbirii != nullptr && this->nrApeluri>0) {
            this->durataConvorbirii = new int[this->nrApeluri];
            for(int i=0; i<this->nrApeluri; i++)
                this->durataConvorbirii[i] = durataConvorbirii[i];
        }
        if(provider!=nullptr) {
            this->provider = new char[strlen(provider) + 1];
            strcpy(this->provider, provider);
        }
        this->esteFix = esteFix;
        }

        AgendaTelefon(const AgendaTelefon &sursa) : id(sursa.id) {
            cout<<"CONSTRUCTOR COPIERE"<<endl;

            if(sursa.consumator != nullptr) {
                this->consumator = new char[strlen(sursa.consumator) + 1];
                strcpy(this->consumator, sursa.consumator);
            }

            if(sursa.nrApeluri > 0)
                this->nrApeluri = sursa.nrApeluri;
            else
                this->nrApeluri = 0;

            if(sursa.durataConvorbirii != nullptr && this->nrApeluri>0) {
                this->durataConvorbirii = new int[this->nrApeluri];
                for(int i=0; i<this->nrApeluri; i++)
                    this->durataConvorbirii[i] = sursa.durataConvorbirii[i];
            }
            if(sursa.provider!=nullptr) {
                this->provider = new char[strlen(sursa.provider) + 1];
                strcpy(this->provider, sursa.provider);
            }
            this->esteFix = sursa.esteFix;
        }

        AgendaTelefon& operator=(AgendaTelefon& sursa) {
            cout<<"OPERATOR ="<<endl;

            if(this != &sursa) {
                delete[] this->consumator;
                this->consumator = nullptr;

                delete[] this->provider;
                this->provider = nullptr;

                delete[] this->durataConvorbirii;
                this->durataConvorbirii = nullptr;           

                if(sursa.consumator != nullptr) {
                    this->consumator = new char[strlen(sursa.consumator) + 1];
                    strcpy(this->consumator, sursa.consumator);
                }

                if(sursa.nrApeluri > 0)
                    this->nrApeluri = sursa.nrApeluri;
                else
                    this->nrApeluri = 0;

                if(sursa.durataConvorbirii != nullptr && this->nrApeluri>0) {
                    this->durataConvorbirii = new int[this->nrApeluri];
                    for(int i=0; i<this->nrApeluri; i++)
                        this->durataConvorbirii[i] = sursa.durataConvorbirii[i];
                }
                if(sursa.provider!=nullptr) {
                    this->provider = new char[strlen(sursa.provider) + 1];
                    strcpy(this->provider, sursa.provider);
                }
                this->esteFix = sursa.esteFix;
            }
            return *this;
        }

        friend ostream& operator<<(ostream& ost, AgendaTelefon& sursa) {
            cout<<"======================================================"<<endl;
            cout<< "id consumator: "<<sursa.id<<endl;
            if(sursa.consumator!=nullptr)
                cout<<"consumator: "<<sursa.consumator<<endl;
            else
                cout<<"ERR_CONSUMATOR"<<endl;
            if(sursa.nrApeluri > 0)
                cout<<"numar apeluri: "<<sursa.nrApeluri<<endl;
            else
                cout<<"ERR NR_APELURI"<<endl;
            if(sursa.nrApeluri > 0 && sursa.durataConvorbirii!=nullptr) {
                cout<<"apeluri cu durata de: "<<endl;
                for(int i=0; i<sursa.nrApeluri; i++) {
                    cout<<"Apelul "<< i <<" Cu durata " <<sursa.durataConvorbirii[i];
                    cout<<endl;
                }
            }
            else
                cout<<"ERR_DURATA_CONVORBIRII"<<endl;   
            if(sursa.provider!=nullptr)
                cout<<"provider: "<<sursa.provider<<endl;
            else
                cout<<"ERR_PROVIDER"<<endl;
            cout<<"este fix: "<<sursa.esteFix<<endl;
            cout<<"======================================================"<<endl;
            return ost;
        }

        friend istream& operator>>(istream& in, AgendaTelefon& sursa) {
            delete[] sursa.consumator;
            sursa.consumator = nullptr;

            delete[] sursa.provider;
            sursa.provider = nullptr;

            delete[] sursa.durataConvorbirii;
            sursa.durataConvorbirii = nullptr;

            string buffer;

            cout<<"consumatorul: "<<endl;
            in>>buffer;
            if(!buffer.empty()) {
                sursa.consumator = new char(buffer.size() + 1);
                strcpy(sursa.consumator, buffer.data());
            }
            else
                sursa.consumator = nullptr;

            cout<<"numar apeluri: "<<endl;
            in>>sursa.nrApeluri;
            if(sursa.nrApeluri <= 0)
                sursa.nrApeluri = 0;

            if(sursa.nrApeluri > 0) {
                cout<<"apeluri cu durata de: "<<endl;
                sursa.durataConvorbirii = new int[sursa.nrApeluri];
                for(int i=0; i<sursa.nrApeluri; i++) {
                    in>>sursa.durataConvorbirii[i];
                    if(sursa.durataConvorbirii[i] < 0)
                        sursa.durataConvorbirii[i] = 0;
                }
            }
            else
                sursa.durataConvorbirii = nullptr;
            
            cout<<"provider: "<<endl;
            in>>buffer;
            if(!buffer.empty()) {
                sursa.provider = new char[buffer.size() + 1];
                strcpy(sursa.provider, buffer.data());
            }
            else
                sursa.provider = nullptr;
            
            cout<<"este fix(1/0)";
            in>>sursa.esteFix;

            return in;
        }

        AgendaTelefon& operator+=(int nrMinuteAdaugate) {
            int* aux = new int [this->nrApeluri + 1];

            for(int i=0; i<this->nrApeluri; i++)
                aux[i] = this->durataConvorbirii[i];
            aux[this->nrApeluri] = nrMinuteAdaugate;

            delete[] this->durataConvorbirii;
            this->durataConvorbirii = nullptr;

            this->nrApeluri++;
            this->durataConvorbirii = new int[this->nrApeluri];

            for(int i=0; i<this->nrApeluri; i++)
                this->durataConvorbirii[i] = aux[i];

            delete[] aux;
            aux = nullptr;

            return *this;
        }

        AgendaTelefon& operator--() {
            int* aux = new int [this->nrApeluri-1];

            for(int i=1; i<this->nrApeluri; i++)
                aux[i-1] = this->durataConvorbirii[i];

            delete[] this->durataConvorbirii;
            this->durataConvorbirii = nullptr;

            this->nrApeluri--;
            this->durataConvorbirii = new int[this->nrApeluri];

            for(int i=0; i<this->nrApeluri; i++)
                this->durataConvorbirii[i] = aux[i];

            delete[] aux;
            aux = nullptr;

            return *this;
        }

        AgendaTelefon& operator--(int) {
            int* aux = new int [this->nrApeluri-1];

            for(int i=0; i<this->nrApeluri - 1; i++)
                aux[i] = this->durataConvorbirii[i];

            delete[] this->durataConvorbirii;
            this->durataConvorbirii = nullptr;

            this->nrApeluri--;
            this->durataConvorbirii = new int[this->nrApeluri];

            for(int i=0; i<this->nrApeluri; i++)
                this->durataConvorbirii[i] = aux[i];

            delete[] aux;
            aux = nullptr;

            return *this;
        }

        int operator[](int index) {
            if(index < this->nrApeluri)
                return durataConvorbirii[index];
            else
                return -1;
        }

        bool operator[](const char* provider) {
            if(strcmp(this->provider, provider)==0)
                return 1;
            else
                return 0;
        }

        bool operator!() {
            return !this->consumator;
        }

        explicit operator int() {
            if(this->nrApeluri > 0 && this->durataConvorbirii!=nullptr) {
                float sum = 0;
                for(int i=0; i<this->nrApeluri; i++)
                    sum+=this->durataConvorbirii[i];
                return sum;
            }
            else
                return 0;
        }

        explicit operator bool() {
            if(this->provider!=nullptr && this->consumator!=nullptr)
                return 1;
            else
                return 0;
        }

        ~AgendaTelefon() {
            delete[] this->consumator;
            this->consumator = nullptr;

            delete[] this->provider;
            this->provider = nullptr;

            delete[] this->durataConvorbirii;
            this->durataConvorbirii = nullptr;
        }
};

int AgendaTelefon::costMinut = 2;

int main() {
    AgendaTelefon telEmpty(1);
    cout<<telEmpty;


    char* cons = new char[strlen("anastasia") + 1];
    strcpy(cons, "anastasia");
    int* durConv = new int[4];
    for(int i=0; i<4; i++)
        durConv[i] = i * 3;
     char* prov = new char[strlen("digi") + 1];
    strcpy(prov, "digi");
    
    AgendaTelefon tel1(1, cons, 4, durConv, prov, false);
    cout<<tel1;

    AgendaTelefon tel2 = tel1;
    cout<<tel2;

    tel1+=17;
    cout<<tel1;

    int nrMin = tel1[4];
    cout<<"nr extras din obiect este: "<<nrMin<<endl;

    bool esteDigi = tel1["vodafon"];
    cout<<"verificarea daca providerul este cel introdus este: "<<esteDigi<<endl;

    tel1--;
    cout<<tel1;

    --tel1;
    cout<<tel1;

    int minuteTotale = (int)tel1;
    cout<<"minute total vorbite: "<<minuteTotale <<endl;

    bool areCeTrebuie = (bool)telEmpty;
    cout<<"are ce trebuie: "<<areCeTrebuie<<endl;

    if(!tel1) {
        cout<<"nu are consumator"<<endl;
    }
    else
        cout<<"are consumator"<<endl;

}