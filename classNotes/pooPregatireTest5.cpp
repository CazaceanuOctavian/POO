#include <iostream>
#include <string.h>

using namespace std;

class Sejur {
    private:
        const int id;
        char* destinatie;
        float pretBaza;
        int nrExcursiiOptionale;
        float* pretExcursie;

        static int nrExcursiiEfectuate;
        bool esteInStrainatate;
    public:
        Sejur() : id(id) {
            this->destinatie=nullptr;
            this->pretBaza=0;
            this->nrExcursiiEfectuate=0;
            this->pretExcursie=nullptr;
            this->esteInStrainatate=false;
        }

        Sejur(int id, char* destinatie, float pretBaza, int nrExcursiiOptionale, float* pretExcursie, bool esteInStrainatate) : id(id) {
            if(destinatie!=nullptr) {
                this->destinatie = new char[strlen(destinatie) + 1];
                strcpy(this->destinatie, destinatie);
            }
            else
                this->destinatie=nullptr;
            if(pretBaza>0)
                this->pretBaza=pretBaza;
            else
                this->pretBaza=0;
            if(nrExcursiiOptionale>0)
                this->nrExcursiiOptionale=nrExcursiiOptionale;
            else
                this->nrExcursiiOptionale=0;
            if(this->nrExcursiiOptionale>0 && pretExcursie!=nullptr) {
                this->pretExcursie = new float[this->nrExcursiiOptionale];
                for(int i=0; i<this->nrExcursiiOptionale; i++)
                    this->pretExcursie[i] = pretExcursie[i];
            }
            this->esteInStrainatate=esteInStrainatate;
        }

        Sejur(Sejur& sursa) : id(sursa.id){
            cout<<"COPY CONSTURCTOR"<<endl;
            if(this != &sursa) {
                if(sursa.destinatie!=nullptr) {
                    this->destinatie = new char[strlen(sursa.destinatie) + 1];
                    strcpy(this->destinatie, sursa.destinatie);
                }
                else
                    this->destinatie=nullptr;
                if(sursa.pretBaza>0)
                    this->pretBaza=sursa.pretBaza;
                else
                    this->pretBaza=0;
                if(sursa.nrExcursiiOptionale>0)
                    this->nrExcursiiOptionale=sursa.nrExcursiiOptionale;
                else
                    this->nrExcursiiOptionale=0;
                if(this->nrExcursiiOptionale>0 && sursa.pretExcursie!=nullptr) {
                    this->pretExcursie = new float[this->nrExcursiiOptionale];
                    for(int i=0; i<this->nrExcursiiOptionale; i++)
                        this->pretExcursie[i] = sursa.pretExcursie[i];
                }
                this->esteInStrainatate=sursa.esteInStrainatate;
            }
        }

        Sejur& operator=(Sejur& sursa) : id(sursa.id) {
            delete[] this->destinatie;
            this->destinatie = nullptr;

            delete[] this->pretExcursie;
            this->pretExcursie= nullptr;

            if(this != &sursa) {
                if(sursa.destinatie!=nullptr) {
                    this->destinatie = new char[strlen(sursa.destinatie) + 1];
                    strcpy(this->destinatie, sursa.destinatie);
                }
                else
                    this->destinatie=nullptr;
                if(sursa.pretBaza>0)
                    this->pretBaza=sursa.pretBaza;
                else
                    this->pretBaza=0;
                if(sursa.nrExcursiiOptionale>0)
                    this->nrExcursiiOptionale=sursa.nrExcursiiOptionale;
                else
                    this->nrExcursiiOptionale=0;
                if(this->nrExcursiiOptionale>0 && sursa.pretExcursie!=nullptr) {
                    this->pretExcursie = new float[this->nrExcursiiOptionale];
                    for(int i=0; i<this->nrExcursiiOptionale; i++)
                        this->pretExcursie[i] = sursa.pretExcursie[i];
                }
                this->esteInStrainatate=sursa.esteInStrainatate;
            }

            return *this;
        }

        friend ostream& operator<<(ostream& ost, Sejur& sursa) {
            cout<<"===================================="<<endl;
            cout<<"id: "<<sursa.id<<endl;
            if(sursa.destinatie!=nullptr){
                cout<<"destinatie: "<<sursa.destinatie<<endl;
            }
            else
                cout<<"destination unknown";
            if(sursa.pretBaza>0)
                cout<<"pretBaza: "<<sursa.pretBaza<<endl;
            if(sursa.nrExcursiiOptionale>0)
                cout<<"nrExcursiiOptionale: "<<sursa.nrExcursiiOptionale<<endl;
            if(sursa.nrExcursiiOptionale>0 && sursa.pretExcursie!=nullptr){
                cout<<"excursile optionale au preturile: ";
                for(int i=0; i<sursa.nrExcursiiOptionale; i++)
                    cout<<sursa.pretExcursie[i] << " | ";
                cout<<endl;
            }
            cout<<"esteInStrainatate: "<<sursa.esteInStrainatate<<endl;
            cout<<"===================================="<<endl;
            return ost;
        }

        void setNrExcursiiEfectuate(int nrExcursii) {
            if(nrExcursii>0)
                Sejur::nrExcursiiEfectuate=nrExcursii;
        }

        int getNrExcursiiEfectuate() {
            return Sejur::nrExcursiiEfectuate;
        }

        void setEsteInStrainatate(bool esteInStrainatate) {
            this->esteInStrainatate=esteInStrainatate;
        }

        bool getEsteInStrainatate() {
            return this->esteInStrainatate;
        }

        ~Sejur() {
            delete[] this->destinatie;
            this->destinatie = nullptr;

            delete[] this->pretExcursie;
            this->pretExcursie= nullptr;
        }

};

int Sejur::nrExcursiiEfectuate=0;

int main() {
    char* destinatie = new char[strlen("comisani") + 1];
    strcpy(destinatie, "comisani");

    float* pretExcursiiOptionale = new float[3];
    pretExcursiiOptionale[0] = 110;
    pretExcursiiOptionale[1] = 250;
    pretExcursiiOptionale[2] = 50;

    Sejur s1(1, destinatie, 300, 3, pretExcursiiOptionale, false);
    cout<<s1;

    Sejur s2 = s1;
    cout<<s2;

    Sejur s3;
    s3 = s1;
    cout<<s3;
    

    
}