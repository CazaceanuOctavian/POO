#include <iostream>
#include <string.h>

using namespace std;

enum TipCombustibil {
    BENZINA = 1,
    MOTORINA = 2
};

struct combustibilAgaugat{
    int nrRezervor;
    TipCombustibil tipCombustibil;
    float cantitateAdaugata;
};


class Rezervor {
    private:
        TipCombustibil combustibil;
        float capacitateTotala;
        int incarcaturaCurenta;
    public:
        Rezervor() {
            this->combustibil=TipCombustibil::BENZINA;
            this->capacitateTotala = 0;
            this->incarcaturaCurenta = 0;
        }

        Rezervor(TipCombustibil combustibil, float capacitateTotala, int incarcaturaCurenta) {
            this->combustibil = combustibil;

            if(capacitateTotala>0)
                this->capacitateTotala = capacitateTotala;
            else
                this->capacitateTotala = 0;

            if(incarcaturaCurenta>=0)
                this->incarcaturaCurenta = incarcaturaCurenta;
            else
                this->incarcaturaCurenta = 0;
        }

        Rezervor(const Rezervor& sursa) {
            this->combustibil = sursa.combustibil;

            if(sursa.capacitateTotala>0)
                this->capacitateTotala = sursa.capacitateTotala;
            else
                this->capacitateTotala = 0;

            if(sursa.incarcaturaCurenta>=0)
                this->incarcaturaCurenta = sursa.incarcaturaCurenta;
            else
                this->incarcaturaCurenta = 0;
        }

        Rezervor& operator==(const Rezervor& sursa) {
            this->combustibil = sursa.combustibil;

            if(sursa.capacitateTotala>0)
                this->capacitateTotala = sursa.capacitateTotala;
            else
                this->capacitateTotala = 0;

            if(sursa.incarcaturaCurenta>=0)
                this->incarcaturaCurenta = sursa.incarcaturaCurenta;
            else
                this->incarcaturaCurenta = 0;
            return *this;
        }

        friend ostream& operator<<(ostream& ost, Rezervor& sursa) {
            cout<<"------------------------------------------"<<endl;
            cout<<"Tip combustibil: "<<sursa.combustibil<<endl;

            if(sursa.capacitateTotala>0)
                cout<<"capacitate totala rezervor: "<<sursa.capacitateTotala<<endl;
            else
                cout<<"ERR_CAPACITATE_TOTALA"<<endl;
            
            if(sursa.incarcaturaCurenta>=0)
                cout<<"incarcatura curenta: "<<sursa.incarcaturaCurenta<<endl;
            else
                cout<<"ERR_INCARCATURA_CURENTA"<<endl;
            cout<<"------------------------------------------"<<endl;
            return ost;
        }

        bool operator!() {
            if(this->incarcaturaCurenta>0)
                return true;
            return false;
        }

        TipCombustibil getTipCombustibil() {
            return this->combustibil;
        }

        float getCapacitateTotala() {
            return this->capacitateTotala;
        }

        float getIncarcaturaCurenta() {
            return this->incarcaturaCurenta;
        }

        void setIncarcaturaCurenta(float incarcaturaCurenta) {
            this->incarcaturaCurenta = incarcaturaCurenta;
        }

};

class Benzinarie {
    private:
        char* denumireBenzinarie;
        float pretBenzina;
        float pretMotorina;
        int nrRezervoare;
        Rezervor* listaRezervoare;
        float baniIncasatiMotorina;
        float baniIncasatiBenzina;
        static int nrBenzinarii;
    public:
        Benzinarie() {
            this->denumireBenzinarie = nullptr;
            this->pretBenzina = 0;
            this->pretMotorina = 0;
            this->nrRezervoare = 0;
            this->listaRezervoare = nullptr;
            this->baniIncasatiBenzina = 0;
            this->baniIncasatiBenzina = 0;
        }

        Benzinarie(char* denumireBenzinarie, float pretBenzina, float pretMotorina, int nrRezervoare, Rezervor* listaRezervoare) {
            if(denumireBenzinarie!=nullptr) {
                this->denumireBenzinarie = new char[strlen(denumireBenzinarie) + 1];
                strcpy(this->denumireBenzinarie, denumireBenzinarie);
            }

            if(pretBenzina > 0)
                this->pretBenzina = pretBenzina;
            else
                this->pretBenzina = 0;
            
            if(pretMotorina > 0)
                this->pretMotorina = pretMotorina;
            else
                this->pretMotorina  = 0;

            if(nrRezervoare > 0)
                this->nrRezervoare = nrRezervoare;
            else
                this->nrRezervoare= 0;
            
            if(this->nrRezervoare>0 && this->listaRezervoare!=nullptr) {
                this->listaRezervoare = new Rezervor[this->nrRezervoare];
                for(int i=0; i<this->nrRezervoare; i++)
                    this->listaRezervoare[i] = listaRezervoare[i];
            }
            else
                this->listaRezervoare = nullptr;

            this->baniIncasatiBenzina = 0;
            this->baniIncasatiMotorina =0;
        }

        Benzinarie(const Benzinarie& sursa) {
            if(sursa.denumireBenzinarie!=nullptr) {
                this->denumireBenzinarie = new char[strlen(sursa.denumireBenzinarie) + 1];
                strcpy(this->denumireBenzinarie, sursa.denumireBenzinarie);
            }

            if(sursa.pretBenzina > 0)
                this->pretBenzina = sursa.pretBenzina;
            else
                this->pretBenzina = 0;
            
            if(sursa.pretMotorina > 0)
                this->pretMotorina = sursa.pretMotorina;
            else
                this->pretMotorina  = 0;

            if(sursa.nrRezervoare > 0)
                this->nrRezervoare = sursa.nrRezervoare;
            else
                this->nrRezervoare= 0;
            
            if(this->nrRezervoare>0 && this->listaRezervoare!=nullptr) {
                this->listaRezervoare = new Rezervor[this->nrRezervoare];
                for(int i=0; i<this->nrRezervoare; i++)
                    this->listaRezervoare[i] = sursa.listaRezervoare[i];
            }
            else
                this->listaRezervoare = nullptr;
        }

        friend ostream& operator<<(ostream& ost, Benzinarie& sursa) {
            cout<<"========================================="<<endl;
            if(sursa.denumireBenzinarie!=nullptr)
                cout<<"denumirea benzinariei: "<<sursa.denumireBenzinarie<<endl;
            else
                cout<<"ERR_DENUMIRE_BENZINARIE"<<endl;
            
            if(sursa.pretBenzina>0)
                cout<<"pret benzina: "<<sursa.pretBenzina<<endl;
            else
                cout<<"ERR_PRET_BENZINA"<<endl;

            if(sursa.pretMotorina>0)
                cout<<"pret motorina: "<<sursa.pretMotorina<<endl;
            else
                cout<<"ERR_PRET_MOTORINA"<<endl;
            
            if(sursa.nrRezervoare>0)
                cout<<"numar rezervoare: "<<sursa.nrRezervoare<<endl;
            else
                cout<<"ERR_NUMAR_REZERVOARE"<<endl;

            if(sursa.nrRezervoare>0 && sursa.listaRezervoare!=nullptr) {
                cout<<"cu urmatoarele rezervoare: "<<endl;
                for(int i=0; i<sursa.nrRezervoare; i++)
                    cout<<sursa.listaRezervoare[i];
            }
            else
                cout<<"ERR_REZERVOARE"<<endl;
            cout<<"========================================="<<endl;
            return ost;
        }

        Benzinarie& operator+=(combustibilAgaugat comb) {
            if(comb.nrRezervor<this->nrRezervoare && comb.tipCombustibil==this->listaRezervoare[comb.nrRezervor].getTipCombustibil()
            && comb.cantitateAdaugata+listaRezervoare[comb.nrRezervor].getIncarcaturaCurenta()<=listaRezervoare[comb.nrRezervor].getCapacitateTotala())
                this->listaRezervoare[comb.nrRezervor].setIncarcaturaCurenta(comb.cantitateAdaugata+listaRezervoare[comb.nrRezervor].getIncarcaturaCurenta());
                return *this;
        }

        Benzinarie& operator-=(combustibilAgaugat comb) {
            if(comb.nrRezervor<this->nrRezervoare && !this->listaRezervoare[comb.nrRezervor] && comb.tipCombustibil==this->listaRezervoare[comb.nrRezervor].getTipCombustibil()
            && listaRezervoare[comb.nrRezervor].getIncarcaturaCurenta() - comb.cantitateAdaugata>0)
                this->listaRezervoare[comb.nrRezervor].setIncarcaturaCurenta(listaRezervoare[comb.nrRezervor].getIncarcaturaCurenta() - comb.cantitateAdaugata);
                if(comb.tipCombustibil==TipCombustibil::BENZINA)
                    this->baniIncasatiBenzina+=comb.cantitateAdaugata*this->pretBenzina;
                else if (comb.tipCombustibil==TipCombustibil::MOTORINA)
                    this->baniIncasatiMotorina+=comb.cantitateAdaugata*this->pretMotorina;
                return *this;
        }

        float getBaniIncasatiBenzina() {
            return this->baniIncasatiBenzina;
        }

        float getBaniIncasatiMotorina() {
            return this->baniIncasatiMotorina;
        }

        TipCombustibil getTipCombustibilCelMaiBineVandut() {
            if(this->baniIncasatiBenzina>this->baniIncasatiMotorina)
                return TipCombustibil::BENZINA;
            else
                return TipCombustibil::MOTORINA;
        }

        ~Benzinarie() {
            delete[] this->denumireBenzinarie;
            this->denumireBenzinarie = nullptr;

            delete[] this->listaRezervoare;
            this->listaRezervoare = nullptr;
        }
};

int Benzinarie::nrBenzinarii = 0;

int main() {
    Rezervor rezEmpty;
    cout<<rezEmpty;

    Rezervor rez1(TipCombustibil::BENZINA, 1060, 560);
    cout<<rez1;

    Rezervor rez2 = rez1;
    cout<<rez2;

    Rezervor rez3;
    rez3 = rez1;

    Benzinarie benEmpty;
    cout<<benEmpty;

    Rezervor rez4(TipCombustibil::MOTORINA, 500, 110);
    Rezervor rez5(TipCombustibil::MOTORINA, 1900, 0);

    Rezervor lista[] = {rez1, rez4, rez5};

    char* denumireBenzinarie = new char[strlen("OMV") + 1];
    strcpy(denumireBenzinarie, "OMV");

    Benzinarie ben1(denumireBenzinarie, 6, 7.5, 3, lista);
    cout<<ben1;

    Benzinarie ben2 = ben1;
    cout<<ben2;

    combustibilAgaugat com;
    com.cantitateAdaugata = 170;
    com.nrRezervor = 0;
    com.tipCombustibil = TipCombustibil::BENZINA;

    ben1+=com;
    cout<<ben1;

    ben1-=com;
    cout<<ben1;

    cout<<"bani incasati din vanzari: "<<endl;
    cout<<"bani incasati benzina "<<ben1.getBaniIncasatiBenzina()<<endl;
    cout<<"bani incasati motorina "<<ben1.getBaniIncasatiMotorina()<<endl;


    



}