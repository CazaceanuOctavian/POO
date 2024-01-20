#include <iostream>
#include <string.h>

using namespace std;

enum Materiale {
    SILICON = 1,
    LEMN = 2,
    MARMURA = 3
};

class Imprimari {
    private:
        int nrExemplare;
        float* costExemplar;
        Materiale material;
        static string denumireImprimanta;
    public:
        Imprimari() {
            this->nrExemplare = 0;
            this->costExemplar = nullptr;
            material = Materiale::SILICON;
        }

        Imprimari(int nrExemplare, float* costExemplar, Materiale material) {
            if(nrExemplare > 0)
                this->nrExemplare = nrExemplare;
            else
                this->nrExemplare = 0;
            
            if(this->nrExemplare > 0 && costExemplar != nullptr) {
                this->costExemplar = new float[this->nrExemplare];
                for(int i=0; i<this->nrExemplare; i++)
                    this->costExemplar[i] = costExemplar[i];
            }
            else
                this->costExemplar = nullptr;
            
            this->material = material;
        }

        Imprimari(Imprimari& sursa) {
            if(sursa.nrExemplare > 0)
                this->nrExemplare = sursa.nrExemplare;
            else
                this->nrExemplare = 0;
            
            if(this->nrExemplare > 0 && costExemplar != nullptr) {
                this->costExemplar = new float[this->nrExemplare];
                for(int i=0; i<this->nrExemplare; i++)
                    this->costExemplar[i] = sursa.costExemplar[i];
            }
            else
                this->costExemplar = nullptr;
            
            this->material = sursa.material;
        }

        friend ostream& operator<<(ostream& ost, Imprimari& sursa) {
            cout<<"======================================"<<endl;
            if(sursa.nrExemplare>0)
                cout<<"numar de exemplare: "<<sursa.nrExemplare<<endl;
            else
                cout<<"ERR_NR_EXEMPLARE"<<endl;
            
            if(sursa.nrExemplare>0 && sursa.costExemplar!=nullptr) {
                cout<<"exemplarele au costurile: "<<endl;
                for(int i=0; i<sursa.nrExemplare; i++)
                    cout<<"exemplarul " << i << " are costul " << sursa.costExemplar[i] <<endl;
            }
            else
                cout<<"ERR_COSTURI_EXEMPLARE"<<endl;
            
            cout<<"exemplarele sunt facute din materialul: "<<sursa.material<<endl;
            cout<<"======================================"<<endl;

            return ost;
        }

        Imprimari& operator+=(const Imprimari obiect) {
            if(this->nrExemplare> 0 && obiect.nrExemplare > 0) {
                float* aux = new float[this->nrExemplare + obiect.nrExemplare];
                int k=0;
                for(int i=0; i<this->nrExemplare + obiect.nrExemplare; i++) {
                    if(i<this->nrExemplare)
                        aux[i] = this->costExemplar[i];
                    else {
                        aux[i] = obiect.costExemplar[k];
                        k++;
                    }
                }
                
                delete[] this->costExemplar;
                this->costExemplar = nullptr;

                this->nrExemplare += obiect.nrExemplare;

                this->costExemplar = new float[this->nrExemplare];
                for(int i=0; i<this->nrExemplare; i++)
                    this-> costExemplar[i] = aux[i];

                delete[] aux;
                aux = nullptr;
            }
            return *this;
        }

        void setNrExemplare(int nrExemplare) {
            this->nrExemplare = nrExemplare;
        }

        void setCostExemplare(float* costExemplar) {
            this->costExemplar = costExemplar;
        }

        void setMaterial(Materiale material) {
            this->material = material;
        }

        int getNrExemplare() {
            return this->nrExemplare;
        }

        float* getCostExemplare(){
            return this->costExemplar;
        }

        Materiale getMatrial() {
            return this->material;
        }

        ~Imprimari() {
            delete[] this->costExemplar;
            this->costExemplar = nullptr;
        }
};   

class ImprimariSpecializate {
    private:
        int nrImprimari;
        Imprimari* listaImprimari;
        char* denumireClient;
        float dimensiuneVerticala;
        float dimensiuneOrizontala;
    public:
        ImprimariSpecializate() {
            this->nrImprimari = 0;
            this->listaImprimari = nullptr;
            this->denumireClient = nullptr;
            this->dimensiuneOrizontala = 0;
            this->dimensiuneVerticala = 0;
        }

        ImprimariSpecializate(int nrImprimari, Imprimari* listaImprimari, char* denumireClient, float dimensiuneVerticala, float dimensiuneOrizontala) {
            if(nrImprimari>0)
                this->nrImprimari = nrImprimari;
            else
                this->nrImprimari = 0;

            if(listaImprimari!=nullptr && this->nrImprimari>0) {
                this->listaImprimari = new Imprimari[this->nrImprimari];
                for(int i=0; i<this->nrImprimari; i++)
                    this->listaImprimari[i] = listaImprimari[i];
            }

            if(denumireClient!=nullptr) {
                this->denumireClient = new char[strlen(denumireClient) + 1];
                strcpy(this->denumireClient, denumireClient);
            }

            if(dimensiuneOrizontala > 0 && dimensiuneVerticala > 0) {
                this->dimensiuneOrizontala = dimensiuneOrizontala;
                this->dimensiuneVerticala = dimensiuneVerticala;
            }
            else {
                this->dimensiuneOrizontala = 0;
                this->dimensiuneVerticala = 0;
            }
        }

        friend ostream& operator<<(ostream& ost, ImprimariSpecializate& sursa) {
            cout<<"TIP IMPRIMARI_SPECIALIZATE"<<endl;
            cout<<"---------------------------------------------------------"<<endl;
            if(sursa.nrImprimari>0)
                cout<<"numar de comenzi de tip imprimari: "<<sursa.nrImprimari<<endl;
            else
                cout<<"ERR_NR_IMPRIMARI"<<endl;
            
            if(sursa.nrImprimari>0 && sursa.listaImprimari!=nullptr) {
                cout<<"Avem urmatoarele imprimari: "<<endl;
                for(int i=0; i<sursa.nrImprimari; i++)
                    cout<<sursa.listaImprimari[i]<<endl;
            }
            else
                cout<<"ERR_LISTA_IMPRIMARI"<<endl;
            if(sursa.denumireClient!=nullptr) {
                cout<<"denumirea clientului: "<<sursa.denumireClient<<endl;
            }
            else
                cout<<"ERR_DENUMIRE_CLIENT"<<endl;
            
            cout<<"cu dimensiunile: ";
            cout<<sursa.dimensiuneOrizontala<< " | "<<sursa.dimensiuneVerticala<<endl;
            cout<<"---------------------------------------------------------"<<endl;
            return ost;
        }
};

string Imprimari::denumireImprimanta = "KGB-1953";

int main() {
    Imprimari impEmpty;
    cout<<impEmpty;

    float* costuriExemplare = new float[3];
    costuriExemplare[0] = 15;
    costuriExemplare[1] = 13;
    costuriExemplare[2] = 23;
    Imprimari imp1(3, costuriExemplare, Materiale::MARMURA);
    Imprimari imp2(3, costuriExemplare, Materiale::MARMURA);
    cout<<imp1;

    imp1 += imp2;
    cout<<imp1;

    ImprimariSpecializate specEmpty;
    cout<<specEmpty;

    Imprimari listaImp[] = {imp1, imp2};
    char* numeClinet = new char[strlen("abramovici") + 1];
    strcpy(numeClinet, "abramovici");

    ImprimariSpecializate spec1(2, listaImp, numeClinet, 5, 8);
    cout<<spec1;

}