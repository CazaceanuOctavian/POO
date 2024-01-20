#include <iostream>
#include <string.h>

using namespace std;

enum Grad {
    ASIST = 1,
    LECT = 2,
    CONF = 3,
    PROF = 4
};

class Angajat {

    private:
        char* nume;
    protected:
        int vechime;
        int nrLocuriMunca; 
        string* locuriMunca;
        float salariu = 0; 
    public:
        Angajat() {
            this->nume = nullptr;
            this->vechime = 0;
            this->nrLocuriMunca = 0;
            this->locuriMunca = nullptr;
            this->salariu = 0;
        }  

        Angajat(char* nume, int vechime, int nrLocuriMunca, 
                string* locuriMunca, float salariu) {
            cout<<"CONSTRUCTOR_TOTI_PARAM_ANG"<<endl;
            if(nume!=nullptr) {
                this->nume = new char[strlen(nume) + 1];
                strcpy(this->nume, nume);
            }
            else
                this->nume = nullptr;
            if(vechime>0)
                this->vechime = vechime;
            else
                this->vechime = 0;

            if(nrLocuriMunca > 0)
                this->nrLocuriMunca = nrLocuriMunca;
            else
                this->nrLocuriMunca = 0;

            if(this->nrLocuriMunca > 0 && locuriMunca!=nullptr) {
                this->locuriMunca = new string[this->nrLocuriMunca];
                for(int i=0; i<this->nrLocuriMunca; i++)
                    this->locuriMunca[i] = locuriMunca[i];
            }
            if(salariu > 0)
                this->salariu = salariu;
            else
                this->salariu = 0;
        }

        Angajat(const Angajat& sursa) {
            cout<<"CPY CONSTRUCOR"<<endl;
            if(sursa.nume!=nullptr) {
                this->nume = new char[strlen(sursa.nume) + 1];
                strcpy(this->nume, sursa.nume);
            }
            else
                this->nume = nullptr;
            if(sursa.vechime>0)
                this->vechime = sursa.vechime;
            else
                this->vechime = 0;

            if(sursa.nrLocuriMunca > 0)
                this->nrLocuriMunca = sursa.nrLocuriMunca;
            else
                this->nrLocuriMunca = 0;

            if(this->nrLocuriMunca > 0 && sursa.locuriMunca!=nullptr) {
                this->locuriMunca = new string[this->nrLocuriMunca];
                for(int i=0; i<this->nrLocuriMunca; i++)
                    this->locuriMunca[i] = sursa.locuriMunca[i];
            }
            if(sursa.salariu > 0)
                this->salariu = sursa.salariu;
            else
                this->salariu = 0;
        }

        Angajat& operator=(const Angajat& sursa) {
            cout<<"OPERATOR ="<<endl;
            if(this != &sursa) {
                delete[] this->locuriMunca;
                this->locuriMunca = nullptr;

                delete[] this->nume;
                this->nume = nullptr;

                if(sursa.nume!=nullptr) {
                this->nume = new char[strlen(sursa.nume) + 1];
                strcpy(this->nume, sursa.nume);
                }
                else
                    this->nume = nullptr;
                if(sursa.vechime>0)
                    this->vechime = sursa.vechime;
                else
                    this->vechime = 0;

                if(sursa.nrLocuriMunca > 0)
                    this->nrLocuriMunca = sursa.nrLocuriMunca;
                else
                    this->nrLocuriMunca = 0;

                if(this->nrLocuriMunca > 0 && sursa.locuriMunca!=nullptr) {
                    this->locuriMunca = new string[this->nrLocuriMunca];
                    for(int i=0; i<this->nrLocuriMunca; i++)
                        this->locuriMunca[i] = sursa.locuriMunca[i];
                }
                if(sursa.salariu > 0)
                    this->salariu = sursa.salariu;
                else
                    this->salariu = 0;                
                }
            return *this;
        }

        friend ostream& operator<<(ostream& ost, Angajat& sursa) {
            ost<<"========================================="<<endl;
            if(sursa.nume!=nullptr)
                ost<<"numele: "<<sursa.nume<<endl;
            else
                ost<<"ERR_NUME"<<endl;
            
            if(sursa.vechime>0)
                ost<<"vechime: "<<sursa.vechime<<endl;
            else
                ost<<"ERR_VECHIME"<<endl;

            if(sursa.nrLocuriMunca > 0)
                ost<<"numar locuri munca: "<<sursa.nrLocuriMunca<<endl;
            else
                ost<<"ERR_NR_LOC_MUNCA"<<endl;
            
            if(sursa.nrLocuriMunca > 0 && sursa.locuriMunca!=nullptr) {
                cout<<"locurile de munca sunt: "<<endl;
                for(int i=0; i<sursa.nrLocuriMunca; i++)
                    ost<<"locul de munca " << i << " cu denumirea: " << sursa.locuriMunca[i] <<endl;
            }
            else
                cout<<"ERR_LOCURI_MUNCA"<<endl;

            if(sursa.salariu > 0)
                ost<<"salariul: " << sursa.salariu<<endl;
            else
                ost<<"ERR_SALARIUL"<<endl;

            ost<<"========================================="<<endl;
            return ost;
        }

        float calculSalariu() {
            return this->salariu;
        }

        ~Angajat() {
            delete[] this->locuriMunca;
            this->locuriMunca = nullptr;

            delete[] this->nume;
            this->nume = nullptr;
        }
};

class Profesor : public Angajat {
    private:
        Grad gradDidactic;
        int nrOreSuplimentare;
    public:
        Profesor() {
            gradDidactic = Grad::ASIST;
            nrOreSuplimentare = 0;
        }

        Profesor(char* nume, int vechime, int nrLocuriMunca, 
                string* locuriMunca, float salariu,
                Grad gradDidactic, int nrOreSuplimentare) : Angajat(nume, vechime, nrLocuriMunca, locuriMunca, salariu) {
            cout<<"CONSTRUCTOR_TOTI_PARAM_PROF"<<endl;
            this->gradDidactic = gradDidactic;
            this->nrOreSuplimentare = nrOreSuplimentare;
        }

        Profesor(Angajat ang, Grad gradDidactic, int nrOreSuplimentare) : Angajat(ang) {
            this->gradDidactic = gradDidactic;
            this->nrOreSuplimentare = nrOreSuplimentare;
        }

        Profesor(const Profesor& prf) : Angajat(prf) {
            cout<<"CPY_CONSTURCTOR_PROFESOR";
            this->gradDidactic = prf.gradDidactic;
            this->nrOreSuplimentare = prf.nrOreSuplimentare;
        }

        friend ostream& operator<<(ostream& out, const Profesor& sursa) {
            out<<(Angajat&)sursa;
            out<<"grad didactic: "<<sursa.gradDidactic<<endl;
            out<<"ore suplimentare: "<<sursa.nrOreSuplimentare<<endl;
            return out;
        }

        Profesor operator=(const Profesor& sursa) {
            if(this != &sursa) {
                this->Angajat::operator=(sursa);
                this->gradDidactic = sursa.gradDidactic;
                this->nrOreSuplimentare = sursa.nrOreSuplimentare;
            }
            return *this;
        }
};

int main() {
    Angajat angEmpty;
    cout<<angEmpty;

    char* nume = new char[strlen("ana") + 1];
    strcpy(nume, "ana");
    string* locuriMunca = new string[3];
    locuriMunca[0] = "manager";
    locuriMunca[1] = "profesor";
    locuriMunca[2] = "decan";
    Angajat a1(nume, 5, 3, locuriMunca, 5000);
    cout<<a1;

    Angajat a2 = a1;
    cout<<a2;

    Angajat a3(nume, 5, 3, locuriMunca, 10000);

    a3 = a1;
    cout<<a3;

    Profesor prf1(nume, 5, 3, locuriMunca, 5000, Grad::CONF, 3);
    //sau
    Profesor prf2(a1, Grad::CONF, 3);

    cout<<prf1<<endl;
    cout<<prf2<<endl;

    Profesor prf3;
    cout<<prf3;

    Profesor prf4(nume, 5, 3, locuriMunca, 5000, Grad::ASIST, 5);

    prf3 = prf4;
    cout<<prf3;
}