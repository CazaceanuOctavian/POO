#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

enum StarePetitie{
    DESCHISA = 1,
    REZOLVATA = 2
};

int ziCurenta = 170;

class IColectareResurse {
    virtual int strangeResurse() = 0;
};

class Petitii : IColectareResurse {
    protected:
        static int termenLegal;
        int data;
        char* numeDepunator;
        StarePetitie stare;
        int nrSemnaturi;
    public:
        Petitii() {
            this->numeDepunator = nullptr;
            this->stare = StarePetitie::DESCHISA;
            this->nrSemnaturi = 0;
        }

        Petitii(char* numeDepunator, StarePetitie stare, int nrSemnaturi, int data) {
            if(numeDepunator!=nullptr) {
                this->numeDepunator = new char[strlen(numeDepunator) + 1];
                strcpy(this->numeDepunator, numeDepunator);
            }
            else
                this->numeDepunator = nullptr;

            this->stare = stare;

            if(nrSemnaturi>0)
                this->nrSemnaturi = nrSemnaturi;
            else
                this->nrSemnaturi = 0;

            if(data>0 && data<366)
                this->data = data;
            else
                this->data = 0;
        }

        Petitii(const Petitii& sursa) {
            if(sursa.numeDepunator!=nullptr) {
                this->numeDepunator = new char[strlen(sursa.numeDepunator) + 1];
                strcpy(this->numeDepunator, sursa.numeDepunator);
            }
            else
                this->numeDepunator = nullptr;

            this->stare = sursa.stare;

            if(sursa.nrSemnaturi>0)
                this->nrSemnaturi = sursa.nrSemnaturi;
            else
                this->nrSemnaturi = 0;

            if(sursa.data>0 && sursa.data<366)
                this->data = sursa.data;
            else
                this->data = 0;
        }

        friend ostream& operator<<(ostream& ost, Petitii& sursa) {
            cout<<"======================================="<<endl;
            if(sursa.numeDepunator!=nullptr)
                cout<<"numele depunatorului: "<<sursa.numeDepunator<<endl;
            else
                cout<<"ERR_NUME_DEPUNATOR"<<endl;
            
            cout<<"stare petitie: "<<sursa.stare<<endl;

            if(sursa.nrSemnaturi>0)
                cout<<"numar de semnaturi: "<<sursa.nrSemnaturi<<endl;
            else
                cout<<"ERR_NUMAR_SEMNATURI"<<endl;

            if(sursa.data>0 && sursa.data<365)
                cout<<"petitia a fost pusa in ziua: "<<sursa.data<<endl;
            else
                cout<<"ERR_ZI_INVALIDA"<<endl;
            cout<<"======================================="<<endl;
            return ost;
        }

        friend ofstream& operator<<(ofstream& ofs, Petitii& sursa) {
            ofs<<"======================================="<<endl;
            if(sursa.numeDepunator!=nullptr)
                ofs<<"numele depunatorului: "<<sursa.numeDepunator<<endl;
            else
                ofs<<"ERR_NUME_DEPUNATOR"<<endl;
            
            ofs<<"stare petitie: "<<sursa.stare<<endl;

            if(sursa.nrSemnaturi>0)
                ofs<<"numar de semnaturi: "<<sursa.nrSemnaturi<<endl;
            else
                ofs<<"ERR_NUMAR_SEMNATURI"<<endl;

            if(sursa.data>0 && sursa.data<365)
                ofs<<"petitia a fost pusa in ziua: "<<sursa.data<<endl;
            else
                ofs<<"ERR_ZI_INVALIDA"<<endl;
            ofs<<"======================================="<<endl;
            return ofs;
        }

        friend ifstream& operator>>(ifstream& in, Petitii& sursa) {
            delete[] sursa.numeDepunator;
            sursa.numeDepunator = nullptr;

            string buffer;
            in>>buffer;
            if(buffer.length()>0){
                sursa.numeDepunator = new char[buffer.size() + 1];
                strcpy(sursa.numeDepunator, buffer.data());
            }
            int stare;
            in>>stare;
            if(stare == 1)
                sursa.stare = StarePetitie::DESCHISA;
            else
                sursa.stare = StarePetitie::REZOLVATA;
            in>>sursa.nrSemnaturi;
            in>>sursa.data;
            return in;
        }

        bool operator!() {
            if(this->stare==StarePetitie::DESCHISA && ziCurenta>this->data+Petitii::termenLegal)
                return true;
            return false;
        }

        Petitii& operator~() {
            if(this->stare==StarePetitie::DESCHISA)
                this->stare=StarePetitie::REZOLVATA;
            else
                this->stare = StarePetitie::DESCHISA;
            return *this;
        }

        void setData(int data) {
            if(data>0 && data<366)
                this->data = data;
            else
                this->data =0;
        }

        int getData() {
            return this->data;
        }

        void setNumeDepunator(char* numeDepunator) {
            if(numeDepunator!=nullptr) {
                delete[] this->numeDepunator;
                this->numeDepunator = nullptr;

                this->numeDepunator = new char[strlen(numeDepunator) + 1];
                strcpy(this->numeDepunator, numeDepunator);
            }
            else
                this->numeDepunator = nullptr;
        }

        char* getNumeDepunator() {
            return this->numeDepunator;
        }

        void setStare(StarePetitie stare) {
            this->stare = stare;
        }

        StarePetitie getStare() {
            return this->stare;
        }

        void setNrSemnaturi(int nrSemnaturi) {
            if(nrSemnaturi>0)
                this->nrSemnaturi = nrSemnaturi;
            else
                this->nrSemnaturi = 0;
        }

        int getNrSemnaturi() {
            return this->nrSemnaturi;
        }

        int strangeResurse() {
            return this->nrSemnaturi;
        }

        ~Petitii() {
            delete[] this->numeDepunator;
            this->numeDepunator = nullptr;
        }
};

class Reclamatii : public Petitii {
    private:
        int nrMartori;
    public:
        Reclamatii() {
            this->nrMartori = nrMartori;
        }

        Reclamatii(Petitii petitii, int nrMartori) : Petitii(petitii) {
            if(nrMartori > 0)
                this->nrMartori = nrMartori;
            else
                this->nrMartori = 0;
        }

        friend ostream& operator<<(ostream& ost, Reclamatii& sursa) {
            ost<<"------------------------------------------"<<endl;
            ost<<"TIP RECLAMATIE"<<endl;
            ost<<(Petitii&)sursa;
            if(sursa.nrMartori>0)
                cout<<"numar de martori: "<<sursa.nrMartori<<endl;
            else
                cout<<"nu au fost martori"<<endl;
            ost<<"------------------------------------------"<<endl;
            return ost;
        }

        int strangeResurse() {
            return this->nrMartori + this->getNrSemnaturi();
        }

        ~Reclamatii() {

        }

};

int Petitii::termenLegal = 30;

int main() {
    Petitii petEmpty;
    cout<<petEmpty;

    char* nume = new char[strlen("bartolovici") + 1];
    strcpy(nume, "bartolovici");

    Petitii pet1(nume, StarePetitie::DESCHISA, 12, 100);
    cout<<pet1;

    Petitii pet2 = pet1;
    cout<<pet2;

    if(!pet1)
        cout<<"e deschisa si a trecut termenul"<<endl;
    else
        cout<<"e rezolvata"<<endl;

    Petitii pet3(nume, StarePetitie::REZOLVATA, 12, 100);

    if(!pet3)
        cout<<"e deschisa si a trecut termenul"<<endl;
    else
        cout<<"e rezolvata"<<endl;

    ~pet3;

    cout<<pet3;

    ~pet1;

    cout<<pet1;

    ofstream g("petitii.txt");
    g << pet1;

    ifstream f("petitii_read.txt");

    Petitii pet4;

    f>>pet4;

    cout<<pet4;

    Reclamatii recEmpty;
    cout<<recEmpty;

    Reclamatii rec1(pet1, 15);
    cout<<rec1;

    int res1 = pet1.strangeResurse();
    cout<<"VIRTUALIZARE PETITII: "<<res1<<endl;
    int res2 = rec1.strangeResurse();
    cout<<"VIRTUALIZARE RECLAMATII: "<<res2<<endl;

}