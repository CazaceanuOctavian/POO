#include <iostream>
#include <string.h>

using namespace std;

class Prajitura {
    private:
        char* denumire;
        int nrCalorii;
        int nrIngrediente;
        float* gramajIngrediente;
        bool esteVegana;

        float pretPrajitura;
        int nrFelii;
    public:
        Prajitura() {
            this->denumire=nullptr;
            this->nrCalorii=0;
            this->nrIngrediente=0;
            this->gramajIngrediente=nullptr;
            this->esteVegana=false;

            this->pretPrajitura=0;
            this->nrFelii=0;
        }

        Prajitura(char* denumire, int nrCalorii, int nrIngrediente, float* gramajIngrediente, bool esteVegana, float pretPrajitura, int nrFelii) {
            cout<<"CONSTRUCTOR CU TOTI PARAMETRII"<<endl;
            if(denumire!=nullptr) {
                this->denumire = new char[strlen(denumire) + 1];
                strcpy(this->denumire, denumire);
            }
            else
                this->denumire=nullptr;
            if(nrCalorii>0)
                this->nrCalorii=nrCalorii;
            else
                this->nrCalorii=0;
            if(nrIngrediente>0)
                this->nrIngrediente=nrIngrediente;
            else
                this->nrIngrediente=0;
            if(this->nrIngrediente>0 && gramajIngrediente!=nullptr) {
                this->gramajIngrediente=new float[this->nrIngrediente];
                for(int i=0; i<this->nrIngrediente; i++)
                    this->gramajIngrediente[i] = gramajIngrediente[i];
            this->esteVegana=esteVegana;
            if(pretPrajitura>0)
                this->pretPrajitura=pretPrajitura;
            else
                this->pretPrajitura=0;
            if(nrFelii>=1)
                this->nrFelii=nrFelii;
            else
                this->nrFelii=1;
            }
        }

        Prajitura(Prajitura& sursa) {
            cout<<"CONSTRUCTOR DE COPIERE"<<endl;
            if(this != &sursa) {
                if(sursa.denumire!=nullptr) {
                this->denumire = new char[strlen(sursa.denumire) + 1];
                strcpy(this->denumire, sursa.denumire);
                }
                else
                    this->denumire=nullptr;
                if(sursa.nrCalorii>0)
                    this->nrCalorii=sursa.nrCalorii;
                else
                    this->nrCalorii=0;
                if(sursa.nrIngrediente>0)
                    this->nrIngrediente=sursa.nrIngrediente;
                else
                    this->nrIngrediente=0;
                if(this->nrIngrediente>0 && sursa.gramajIngrediente!=nullptr) {
                    this->gramajIngrediente=new float[this->nrIngrediente];
                    for(int i=0; i<this->nrIngrediente; i++)
                        this->gramajIngrediente[i] = sursa.gramajIngrediente[i];
                this->esteVegana=sursa.esteVegana;
                if(sursa.pretPrajitura>0)
                    this->pretPrajitura=sursa.pretPrajitura;
                else
                    this->pretPrajitura=0;
                if(sursa.nrFelii>=1)
                    this->nrFelii=sursa.nrFelii;
                else
                    this->nrFelii=1;
                }
            }

        }

        Prajitura& operator=(Prajitura& sursa) {
            cout<<"OPERATOR ="<<endl;
            delete[] this->gramajIngrediente;
            this->gramajIngrediente=nullptr;

            delete[] this->denumire;
            this->denumire=nullptr;

            if(this != &sursa) {
                if(sursa.denumire!=nullptr) {
                   this->denumire = new char[strlen(sursa.denumire) + 1];
                   strcpy(this->denumire, sursa.denumire);
                }
                else
                    this->denumire=nullptr;
                if(sursa.nrCalorii>0)
                    this->nrCalorii=sursa.nrCalorii;
                else
                    this->nrCalorii=0;
                if(sursa.nrIngrediente>0)
                    this->nrIngrediente=sursa.nrIngrediente;
                else
                    this->nrIngrediente=0;
                if(this->nrIngrediente>0 && sursa.gramajIngrediente!=nullptr) {
                    this->gramajIngrediente=new float[this->nrIngrediente];
                    for(int i=0; i<this->nrIngrediente; i++)
                        this->gramajIngrediente[i] = sursa.gramajIngrediente[i];
                this->esteVegana=sursa.esteVegana;
                if(sursa.pretPrajitura>0)
                    this->pretPrajitura=sursa.pretPrajitura;
                else
                    this->pretPrajitura=0;
                if(sursa.nrFelii>=1)
                    this->nrFelii=sursa.nrFelii;
                else
                    this->nrFelii=1;
                }
            }
            return *this;
        }

        friend ostream& operator<<(ostream& ost, Prajitura& sursa) {
            cout<<"=============================="<<endl;
            if(sursa.denumire!=nullptr)
                cout<<"denumire: "<<sursa.denumire<<endl;
            else
                cout<<"denumire nulla";
            cout<<"nrCalorii: "<<sursa.nrCalorii<<endl;
            cout<<"nrIngrediente: "<<sursa.nrIngrediente<<endl;

            if(sursa.nrIngrediente>0 && sursa.gramajIngrediente!=nullptr) {
                cout<<"gramajul ingredientelor este de: ";
                for(int i=0; i<sursa.nrIngrediente; i++) 
                    cout<<sursa.gramajIngrediente[i] << " | ";
                cout<<endl;
            } 
            cout<<"esteVegana: "<<sursa.esteVegana<<endl;
            cout<<"pretPrajitura: "<<sursa.pretPrajitura<<endl;
            cout<<"nrFelii: "<< sursa.nrFelii<<endl;

            cout<<"=============================="<<endl;
            return ost;
        }

        friend istream& operator>>(istream& in, Prajitura& sursa) {
            cout<<"OPERATOR >>"<<endl;
            delete[] sursa.gramajIngrediente;
            sursa.gramajIngrediente=nullptr;

            delete[] sursa.denumire;
            sursa.denumire=nullptr;

            string buffer;

            cout<<"Denumire: ";
            in>>buffer;
            sursa.denumire= new char[buffer.size() + 1];
            strcpy(sursa.denumire, buffer.data());

            cout<<"nrCalorii: ";
            in>>sursa.nrCalorii;
            cout<<"nrIngrediente: ";
            in>>sursa.nrIngrediente;

            if(sursa.nrIngrediente>0) {
                cout<<"gramajul ingredientelor: ";
                sursa.gramajIngrediente= new float[sursa.nrIngrediente];
                for(int i=0; i<sursa.nrIngrediente; i++)
                    in>>sursa.gramajIngrediente[i]; 
            }

            cout<<"esteVegana(bool): ";
            in>>sursa.esteVegana;
            cout<<"pretPrajitura: ";
            in>>sursa.pretPrajitura;
            cout<<"nrFeliiPrajitura: ";
            in>>sursa.nrFelii;

            return in;
        }

        Prajitura operator*=(int multiplicatorIngrediente) {
            cout<<"APEL OPERATOR*="<<endl;
            for(int i=0; i<this->nrIngrediente; i++)
                this->gramajIngrediente[i] *= multiplicatorIngrediente;
            return *this;
        }

        Prajitura& operator+(float gramajIngredient) {
            cout<<"APEL OPERATOR+"<<endl;
            if(gramajIngredient<0) {
                cerr<<"gramaj invalid";
                return *this;
            }
            float* vecGramajNou = new float[this->nrIngrediente + 1];
            for(int i=0; i<nrIngrediente + 1; i++)
                if(i<nrIngrediente)
                    vecGramajNou[i] = this->gramajIngrediente[i];
                else
                    vecGramajNou[i] = gramajIngredient;

            delete[] this->gramajIngrediente;
            this->gramajIngrediente = nullptr;

            this->nrIngrediente++;

            this->gramajIngrediente= new float[this->nrIngrediente];
            for(int i=0; i<this->nrIngrediente; i++)
                this->gramajIngrediente[i] = vecGramajNou[i];

            delete[] vecGramajNou;
            vecGramajNou = nullptr;

            return *this; 
        }

        bool operator!=(Prajitura &sursa) {
            if(strcmp(this->denumire, sursa.denumire)!=0 || this->nrCalorii != sursa.nrCalorii || this->esteVegana!=sursa.esteVegana || this->pretPrajitura != sursa.pretPrajitura
            || this->nrFelii!= sursa.nrFelii || this->nrIngrediente != nrIngrediente)
                return 0;
            return 1;
        }

        void setPretPrajitura(int pretPrajitura) {
            if(pretPrajitura>0)
                this->pretPrajitura=pretPrajitura;
            else
                cerr<<"pretul introdus nu este valid";
        }

        float getPretPrajitura() {
            return this->pretPrajitura;
        }

        void setNrFelii() {
            if(nrFelii>=1)
                this->nrFelii=nrFelii;
            else
                cerr<<"nr de felii introdus nu este valid";
        }

        float getGramajTotal() {
            cout<<"APEL GETGRAMAJTOTAL"<<endl;
            int sumGramaj=0;
            for(int i=0; i<this->nrIngrediente; i++)
                sumGramaj+=this->gramajIngrediente[i];
            return sumGramaj;
        }

        ~Prajitura() {
            delete[] this->gramajIngrediente;
            this->gramajIngrediente=nullptr;

            delete[] this->denumire;
            this->denumire=nullptr;
        }

};

int main() {
    char* denumirePrajitura = new char[strlen("Alexandra") + 1];
    strcpy(denumirePrajitura, "Alexandra");

    float* gramajIngrediente = new float[4];
    gramajIngrediente[0] = 15.3;
    gramajIngrediente[1] = 11.5;
    gramajIngrediente[2] = 20;
    gramajIngrediente[3] = 25.3;

    Prajitura p1(denumirePrajitura, 1500, 4, gramajIngrediente, false, 15, 2);
    cout<<p1;

    Prajitura p2 = p1;
    cout<<p2;

    Prajitura p3;
    p3 = p1;
    cout<<p3;
    cout<<endl;

    //Prajitura p4;
    //cin>>p4;
    //cout<<p4;

    cout<<p1.getGramajTotal();
    cout<<endl;

    p1*=3;
    cout<<p1;

    p3 = p1 + 16.7;
    cout<<p3;

    if(p1!=p3)
        cout<<"OPERATOR != TURE";
    else
        cout<<"OPERATOR != FALSE";


    

}