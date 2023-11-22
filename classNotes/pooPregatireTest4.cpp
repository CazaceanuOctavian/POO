#include <iostream>
#include <string.h>

using namespace std;

class ProfilInfluencer {
    private:
        char* numeCont;
        int nrUrmaritori;
        int nrPostari;
        int* aprecieriPostari;
    public:
        ProfilInfluencer () {
            this->numeCont=nullptr;
            this->nrUrmaritori=0;
            this->nrPostari=0;
            this->aprecieriPostari=nullptr;
        }

        ProfilInfluencer (char* numeCont, int nrUrmaritori, int nrPostari, int* aprecieriPostari) {
            if(numeCont!=nullptr) {
                this->numeCont = new char[strlen(numeCont) + 1];
                strcpy(this->numeCont, numeCont);
            }
            else
                this->numeCont = nullptr;
            if(nrUrmaritori>1000)
                this->nrUrmaritori=nrUrmaritori;
            else
                this->nrUrmaritori=1000;
            if(nrPostari>0)
                this->nrPostari=nrPostari;
            else
                this->nrPostari=0;
            if(this->nrPostari>0 && aprecieriPostari!=nullptr) {
                this->aprecieriPostari = new int[this->nrPostari];
                for(int i=0; i<this->nrPostari; i++)
                    this->aprecieriPostari[i] = aprecieriPostari[i];
            }   
        }

        ProfilInfluencer(ProfilInfluencer& sursa) {
            cout<<"APEL COPY CONSTRUCTOR"<<endl;
            if(this != &sursa) {
                if(sursa.numeCont!=nullptr) {
                    this->numeCont = new char[strlen(sursa.numeCont) + 1];
                    strcpy(this->numeCont, sursa.numeCont);
                }
                else
                    this->numeCont = nullptr;
                if(sursa.nrUrmaritori>1000)
                    this->nrUrmaritori=sursa.nrUrmaritori;
                else
                    this->nrUrmaritori=1000;
                if(sursa.nrPostari>0)
                    this->nrPostari=sursa.nrPostari;
                else
                    this->nrPostari=0;
                if(this->nrPostari>0 && sursa.aprecieriPostari!=nullptr) {
                    this->aprecieriPostari = new int[this->nrPostari];
                    for(int i=0; i<this->nrPostari; i++)
                        this->aprecieriPostari[i] = sursa.aprecieriPostari[i];
                }   
            }
        }

        ProfilInfluencer& operator=(ProfilInfluencer& sursa) {
            cout<<"APEL OPERATOR="<<endl;
            delete[] this->numeCont;
            this->numeCont=nullptr;

            delete[] this->aprecieriPostari;
            this->aprecieriPostari=nullptr;

            if(this != &sursa) {
                if(sursa.numeCont!=nullptr) {
                    this->numeCont = new char[strlen(sursa.numeCont) + 1];
                    strcpy(this->numeCont, sursa.numeCont);
                }
                else
                    this->numeCont = nullptr;
                if(sursa.nrUrmaritori>1000)
                    this->nrUrmaritori=sursa.nrUrmaritori;
                else
                    this->nrUrmaritori=1000;
                if(sursa.nrPostari>0)
                    this->nrPostari=sursa.nrPostari;
                else
                    this->nrPostari=0;
                if(this->nrPostari>0 && sursa.aprecieriPostari!=nullptr) {
                    this->aprecieriPostari = new int[this->nrPostari];
                    for(int i=0; i<this->nrPostari; i++)
                        this->aprecieriPostari[i] = sursa.aprecieriPostari[i];
                }   
            }
            return *this;
        }

        friend ostream& operator<<(ostream& ost, ProfilInfluencer& sursa) {
            cout<<"========================================="<<endl;
            if(sursa.numeCont!=nullptr)
                cout<<"numeCont: "<<sursa.numeCont<<endl;
            else
                cout<<"numeCont: Anon";
            if(sursa.nrUrmaritori>1000)
                cout<<"nrUrmaritori: "<<sursa.nrUrmaritori<<endl;
            if(sursa.nrPostari>0)
                cout<<"nrPostari: "<<sursa.nrPostari<<endl;
            if(sursa.nrPostari>0 && sursa.aprecieriPostari!=nullptr) {
                cout<<"Aprecierile la postari sunt: ";
                for(int i=0; i<sursa.nrPostari; i++)
                    cout<<sursa.aprecieriPostari[i]<< " | ";
                cout<<endl;
            }
            cout<<"========================================="<<endl;

            return ost;
        }

        friend istream& operator>>(istream& in, ProfilInfluencer& sursa) {
            delete[] sursa.numeCont;
            sursa.numeCont=nullptr;

            delete[] sursa.aprecieriPostari;
            sursa.aprecieriPostari=nullptr;

            string buffer;

            cout<<"numeCont: ";
            in>>buffer;
            sursa.numeCont=new char[buffer.size() + 1];
            strcpy(sursa.numeCont, buffer.data());

            cout<<"nrUrmaritori: ";
            in>>sursa.nrUrmaritori;

            cout<<"nrPostari: ";
            in>>sursa.nrPostari;

            if(sursa.nrPostari>0) {
                cout<<"aprecierile la postari sunt: ";
                sursa.aprecieriPostari= new int[sursa.nrPostari];
                for(int i=0; i<sursa.nrPostari; i++)
                    in>>sursa.aprecieriPostari[i];
            }
            return in;
        }

        bool operator<(const ProfilInfluencer& sursa) {
            if(this->nrUrmaritori<sursa.nrUrmaritori)
                return 1;
            return 0;
        }

        int operator[](int index) {
            if(index < this->nrPostari)
                return this->aprecieriPostari[index];
            else {
                cout<<"index out of bounds";
                return 0;
            }
        }

        explicit operator int() {
            int nrTotalAprecieri=0;
            for(int i=0; i<this->nrPostari; i++)
                nrTotalAprecieri+=this->aprecieriPostari[i];
            return nrTotalAprecieri;
        }
    
        void setNumeCont(char* numeCont) {
            delete[] this->numeCont;
            this->numeCont = nullptr;

            if(numeCont!=nullptr) {
                this->numeCont = new char[strlen(numeCont) + 1];
                strcpy(this->numeCont, numeCont);
            }
        }

        char* getNumeCont() {
            return this->numeCont;
        }

        void setNrUrmaritori(int nrUrmaritori) {
            if(nrUrmaritori>1000)
                this->nrUrmaritori=nrUrmaritori;
            else
                this->nrUrmaritori=1000;
        }

        int getNrUrmaritori() {
            return this->nrUrmaritori;
        }

        void adaugaPostare(int nrAprecieri) {
            int* nouAprecieriPostari = new int[this->nrPostari + 1];
            for(int i=0; i<this->nrPostari; i++)
                nouAprecieriPostari[i] = this->aprecieriPostari[i];
            nouAprecieriPostari[this->nrPostari] = nrAprecieri;

            delete[] this->aprecieriPostari;
            this->aprecieriPostari = nullptr;

            this->nrPostari++;
            this->aprecieriPostari = new int[this->nrPostari];
            for(int i=0; i<this->nrPostari; i++)
                this->aprecieriPostari[i] = nouAprecieriPostari[i];
            
            delete[] nouAprecieriPostari;
            nouAprecieriPostari=nullptr;
        }

        ~ProfilInfluencer() {
            delete[] this->numeCont;
            this->numeCont=nullptr;

            delete[] this->aprecieriPostari;
            this->aprecieriPostari=nullptr;
        }
};

int main() {
    char* numeCont = new char[strlen("tavikq") + 1];
    strcpy(numeCont, "Tavikq");

    int* aprecieriPostari = new int[4];
    aprecieriPostari[0] = 57;
    aprecieriPostari[1] = 101;
    aprecieriPostari[2] = 155;
    aprecieriPostari[3] = 351;

    ProfilInfluencer inf1(numeCont, 1500, 4, aprecieriPostari);
    cout<<inf1;

    ProfilInfluencer inf2 = inf1;
    cout<<inf2;

    ProfilInfluencer inf3;
    inf3 = inf1;
    cout<<inf3;

    //ProfilInfluencer inf4;
    //cin>>inf4;
    //cout<<inf4;

    inf1.adaugaPostare(1311);
    cout<<inf1;

    ProfilInfluencer inf5(numeCont, 2000, 4, aprecieriPostari);
    if(inf5<inf1)
        cout<<"OPERATOR < TRUE"<<endl;
    else    
        cout<<"OPERATOR < FALSE"<<endl;

    cout<<"explicit operator int: ";
    int nrTotal = (int)inf1;
    cout<<nrTotal<<endl;

    cout<<"supranincarcare operator []: ";
    int aprecieriPostare = inf1[3];
    cout<<aprecieriPostare<<endl;

}