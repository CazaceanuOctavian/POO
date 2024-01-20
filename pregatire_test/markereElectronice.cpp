#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

enum MaterialPenita {
    SILICON=1,
    GRAFIT=2,
    PLASTIC=3
};

class IPretSpecial {
    virtual float calculeazaPretMarker() = 0;
};

class MarkerElectronic : IPretSpecial{
    protected:
        char* modelMarker;
        float pret;
        MaterialPenita material;
        static int nrTotalMarkere;
    public:
        MarkerElectronic() {
            this->modelMarker = nullptr;
            this->pret = 0;
            this->material = MaterialPenita::SILICON;
        }

        MarkerElectronic(char* modelMarker, float pret, MaterialPenita material) {
            cout<<"CONSTRUCTOR ALL FIELDS"<<endl;
            if(modelMarker!=nullptr) {
                this->modelMarker = new char[strlen(modelMarker) + 1];
                strcpy(this->modelMarker, modelMarker);
            }
            else
                this->modelMarker = nullptr;

            if(pret>0)
                this->pret = pret;
            else
                this->pret = 0;
            
            this->material = material;

            MarkerElectronic::nrTotalMarkere++;
        }

        MarkerElectronic(const MarkerElectronic& sursa) {
            cout<<"CPY CONSTRUCTOR"<<endl;
            if(sursa.modelMarker!=nullptr) {
                this->modelMarker = new char[strlen(sursa.modelMarker) + 1];
                strcpy(this->modelMarker, sursa.modelMarker);
            }
            else
                this->modelMarker = nullptr;

            if(sursa.pret>0)
                this->pret = sursa.pret;
            else
                this->pret = 0;
            
            this->material = sursa.material;

            MarkerElectronic::nrTotalMarkere++;
        }

        bool operator==(MarkerElectronic sursa) {
            if(this->material == sursa.material && this->pret == sursa.pret)
                return true;
            return false;
        }

        friend ostream& operator<<(ostream& ost, MarkerElectronic& sursa) {
            cout<<"OPERATOR<<"<<endl;
            cout<<"============================================"<<endl;
            if(sursa.modelMarker!=nullptr)
                cout<<"model marker: "<<sursa.modelMarker<<endl;
            else
                cout<<"ERR_MODEL_MARKER"<<endl;
            
            if(sursa.pret>0)
                cout<<"pret: "<<sursa.pret<<endl;
            else
                cout<<"ERR_PRET_MARKER"<<endl;
            
            cout<<"material penita: "<<sursa.material<<endl;
            cout<<"============================================"<<endl;
            return ost;
        }

        friend istream& operator>>(istream& in, MarkerElectronic& sursa) {
            delete[] sursa.modelMarker;
            sursa.modelMarker = nullptr;

            cout<<"model marker: "<<endl;
            string buffer;
            in>>buffer;
            if(buffer.length() > 0) {
                sursa.modelMarker = new char[buffer.size() + 1];
                strcpy(sursa.modelMarker, buffer.data());
            }
            else
                sursa.modelMarker = nullptr;

            cout<<"pret marker: "<<endl;
            in>>sursa.pret;
            if(sursa.pret<0)
                sursa.pret = 0;

            cout<<"materialul penitei: (1/2/3)"<<endl;
            int material;
            in>>material;
            if(material == 1)
                sursa.material = MaterialPenita::SILICON;
            else if(material == 2)
                sursa.material = MaterialPenita::GRAFIT;
            else
                sursa.material = MaterialPenita::PLASTIC;

            return in;
        }

        void setPret(const float pret) {
            this->pret = pret;
        }

        float getPret() {
            return this->pret;
        }

        void setMaterial(MaterialPenita material) {
            this->material = material;
        }

        MaterialPenita getMaterial() {
            return this->material;
        }

        virtual float calculeazaPretMarker() {
            return this->pret*0.3;
        }

        void setModelMarker(char* modelMarker) {
            if(modelMarker!=nullptr) {
                delete[] this->modelMarker;
                this->modelMarker = nullptr;

                this->modelMarker = new char[strlen(modelMarker) + 1];
                strcpy(this->modelMarker, modelMarker);
            }
            else
                cout<<"ERR_INVALID_MODEL"<<endl;
        }

        char* getModelMarker() {
            return this->modelMarker;
        }

        ~MarkerElectronic() {
            cout<<"DELETE CONSTRUCTOR"<<endl;
            delete[] this->modelMarker;
            this->modelMarker = nullptr;
        }
};

class MarkerInteligent : public MarkerElectronic {
    private:
        float sensibilitatePenita;
        int nivelePresiune;
    public:
        MarkerInteligent() : MarkerElectronic() {
            this->sensibilitatePenita = 0;
            this->nivelePresiune = 0;
        }

        MarkerInteligent(MarkerElectronic markerElectronic, float sensibilitatePenita, int nivelePresiune) : MarkerElectronic(markerElectronic) {
            if(sensibilitatePenita>=0)
                this->sensibilitatePenita = sensibilitatePenita;
            else
                this->sensibilitatePenita = 0;

            if(nivelePresiune>=0)
                this->nivelePresiune = nivelePresiune;
            else
                this->nivelePresiune = 0;
        }

        friend ostream& operator<<(ostream& ost, MarkerInteligent& sursa) {
            cout<<"TIP MARKER INTELIGENT"<<endl;
            cout<<"--------------------------------------------------"<<endl;
            ost<<(MarkerElectronic&)sursa;
            if(sursa.sensibilitatePenita>=0)
                cout<<"sensibilitate penita: "<<sursa.sensibilitatePenita<<endl;
            else
                cout<<"ERR_SENSIBILITATE_PENITA"<<endl;
            
            if(sursa.nivelePresiune>=0)
                cout<<"nivele presiune: "<<sursa.nivelePresiune<<endl;
            cout<<"--------------------------------------------------"<<endl;
            return ost;
        }

        float calculeazaPretMarker() {
            return this->getPret()*5;
        }

        ~MarkerInteligent() {

        }
};

class gestiuneMarkere {
    private:
        char* numePersoana;
        int nrMarkere;
        MarkerElectronic** listaMarkere;
    public:
        gestiuneMarkere() {
            this->numePersoana = nullptr;
            this->listaMarkere = nullptr;
        }

        gestiuneMarkere(char* numePersoana, int nrMarkere, MarkerElectronic** listaMarkere) {
            if(numePersoana!=nullptr){
                this->numePersoana = new char[strlen(numePersoana) + 1];
                strcpy(this->numePersoana, numePersoana);
            }
            else
                this->numePersoana = nullptr;

            if(nrMarkere > 0)
                this->nrMarkere = nrMarkere;
            else
                this->nrMarkere = 0;

            if(this->nrMarkere > 0 && listaMarkere!=nullptr) {
                this->listaMarkere = new MarkerElectronic*[this->nrMarkere];
                for(int i=0; i<this->nrMarkere; i++)
                    this->listaMarkere[i] = new MarkerElectronic(*listaMarkere[i]);
            }
            else
                this->listaMarkere = nullptr;
        }

        gestiuneMarkere(const gestiuneMarkere& sursa) {
            if(sursa.numePersoana!=nullptr){
                this->numePersoana = new char[strlen(sursa.numePersoana) + 1];
                strcpy(this->numePersoana, numePersoana);
            }
            else
                this->numePersoana = nullptr;

            if(sursa.nrMarkere > 0)
                this->nrMarkere = sursa.nrMarkere;
            else
                this->nrMarkere = 0;

            if(this->nrMarkere > 0 && sursa.listaMarkere!=nullptr) {
                this->listaMarkere = new MarkerElectronic*[this->nrMarkere];
                for(int i=0; i<this->nrMarkere; i++)
                    this->listaMarkere[i] = new MarkerElectronic(*sursa.listaMarkere[i]);
            }
            else
                this->listaMarkere = nullptr;
        }

        friend ostream& operator<<(ostream& ost, gestiuneMarkere& sursa) {
            cout<<"================================================"<<endl;
            cout<<"TIP GESTIUNE_MARKERE"<<endl;
            if(sursa.numePersoana!=nullptr) {
                cout<<"numele persoanei ce detine markere este: "<<sursa.numePersoana<<endl;
            }
            else
                cout<<"ERR_NUME_PERSOANA"<<endl;

            if(sursa.nrMarkere > 0)
                cout<<"persoana are "<<sursa.nrMarkere << " markere";
            else
                cout<<"ERR_NR_MARKERE"<<endl;

            if(sursa.nrMarkere>0 && sursa.listaMarkere!=nullptr) {
                cout<<"persoana are urmatoarele markere: "<<endl;
                for(int i=0; i<sursa.nrMarkere; i++)
                    cout<<(*sursa.listaMarkere[i]);
            }
            else
                cout<<"ERR_LISTA_MARKERE"<<endl;
            cout<<"================================================"<<endl;
            return ost;
        }

        ~gestiuneMarkere() {
            delete[] this->numePersoana;
            this->numePersoana = nullptr;

            delete[] this->listaMarkere;
            this->listaMarkere = nullptr;
        }
};

int MarkerElectronic::nrTotalMarkere = 0;

int main() {
    MarkerElectronic mkElectEmpty;
    cout<<mkElectEmpty;

    char* model = new char[strlen("wacom kgb_1552") + 1];
    strcpy(model, "wacom kbg_1552");
    MarkerElectronic mk1(model, 150, MaterialPenita::GRAFIT);
    cout<<mk1;

    MarkerElectronic mk2 = mk1;
    cout<<mk2;

    MarkerElectronic mk4(model, 200, MaterialPenita::SILICON);

    if(mk1 == mk4)
        cout<<"markerele sunt similare"<<endl;
    else
        cout<<"markere nu sunt similare"<<endl;

    cout<<"+!+!+!+!+!++!+!+!++!+!+!+!+!++!+!+!++!+!+!++!+!+"<<endl;
    MarkerInteligent mkIntEmpty;
    cout<< mkIntEmpty;

    MarkerInteligent mkInt1(mk1, 150, 300);
    cout<<mkInt1;

    cout<<"valoare marker electornic: ";
    float x = mk1.calculeazaPretMarker();
    cout<<x<<endl;

    cout<<"valoare marker inteligent: ";
    float y = mkInt1.calculeazaPretMarker();
    cout<<y<<endl;

    gestiuneMarkere gestEmpty;
    cout<<gestEmpty;

    char* numeDetinator = new char[strlen("bratislav") + 1];
    strcpy (numeDetinator, "bratislav");

    MarkerElectronic mkL1(model, 100, MaterialPenita::GRAFIT);
    MarkerElectronic mkL2(model, 75, MaterialPenita::PLASTIC);
    MarkerElectronic mkL3(model, 310, MaterialPenita::SILICON);

    MarkerElectronic* lista[] = {&mkL1, &mkL2, &mkL3};
    gestiuneMarkere gest(numeDetinator, 3, lista);

    cout<<gest;

    gestiuneMarkere gest2 = gest;
    
    cout<<gest2;

    //MarkerElectronic mk3;
    //cin>>mk3;
    //cout<<mk3;

    //instantiere clasa stl pentru markerElectronic

    vector<MarkerElectronic> markerVector;
    markerVector.push_back(MarkerElectronic(model, 100, MaterialPenita::GRAFIT));
    markerVector.push_back(MarkerElectronic(model, 75, MaterialPenita::PLASTIC));
    markerVector.push_back(MarkerElectronic(model, 310, MaterialPenita::SILICON));
}