#include <iostream>
#include <string.h>

using namespace std;

class Carti {
    private:
        const int id;
        static int nrCarti;
    protected:
        char* titlu;
        int nrPagini;
    public:

        Carti() : id(Carti::nrCarti){
            Carti::nrCarti++;
            this->titlu = nullptr;
            this->nrPagini = 0;
        }

        Carti(int id, char*titlu, int nrPagini) : id(id) {
            if(nrPagini > 0)
                this->nrPagini = nrPagini;
            else
                this->nrPagini = 0;
            
            if(titlu!=nullptr) {
                this->titlu = new char[strlen(titlu) + 1];
                strcpy (this->titlu, titlu);
            }
        }

        Carti(const Carti& sursa) : id(Carti::nrCarti) {
            Carti::nrCarti++;
            if(sursa.nrPagini > 0)
                this->nrPagini = sursa.nrPagini;
            else
                this->nrPagini = 0;
            
            if(sursa.titlu!=nullptr) {
                this->titlu = new char[strlen(sursa.titlu) + 1];
                strcpy (this->titlu, sursa.titlu);
            }
        }

        Carti& operator=(const Carti& sursa) {
            if(this != &sursa) {
                delete[] this->titlu;
                this->titlu = nullptr;

                if(sursa.nrPagini > 0)
                    this->nrPagini = sursa.nrPagini;
                else
                    this->nrPagini = 0;
                
                if(sursa.titlu!=nullptr) {
                    this->titlu = new char[strlen(sursa.titlu) + 1];
                    strcpy (this->titlu, sursa.titlu);
                }
            }
            return *this;
        }

        bool operator==(Carti& sursa) {
            if(strcmp(this->titlu, sursa.titlu)==0)
                return true;
            else
                return false;
        }

        bool operator!=(Carti& sursa) {
            if(strcmp(this->titlu, sursa.titlu)!=0)
                return true;
            else
                return false;
        }

        friend ostream& operator<<(ostream& ost, Carti& sursa) {
            cout<<"-----------------------------------------"<<endl;
            cout<<"id carte: "<<sursa.id<<endl;

            if(sursa.titlu!=nullptr) {
                cout<<"titlu: "<<sursa.titlu<<endl;
            }
            else
                cout<<"ERR_TITLU"<<endl;
            
            if(sursa.nrPagini>0)
                cout<<"numar pagini: "<<sursa.nrPagini<<endl;
            else
                cout<<"ERR_NR_PAGINI"<<endl;
            cout<<"-----------------------------------------"<<endl;
            return ost;
        }

        ~Carti() {
            delete[] this->titlu;
            this->titlu = nullptr;
            Carti::nrCarti--;
        }
};

class Imprumuturi {
    private:
        char* numeImprumutator;
        int nrCartiImprumutate;
        Carti* listaCartiImprumutate;
        static int nr_imprumutatori;
    
    public:
        Imprumuturi() {
            this->numeImprumutator = nullptr;
            this->nrCartiImprumutate = 0;
            this->listaCartiImprumutate = nullptr;
            Imprumuturi::nr_imprumutatori++;
        }

        Imprumuturi(char* numeImprumutator, int nrCartiImprumutate, Carti* listaCartiImprumutate) {
            if(numeImprumutator!=nullptr) {
                this->numeImprumutator = new char[strlen(numeImprumutator) + 1];
                strcpy(this->numeImprumutator, numeImprumutator);
            }
            else
                this->numeImprumutator = nullptr;

            if(nrCartiImprumutate>0)
                this->nrCartiImprumutate = nrCartiImprumutate;
            else
                this->nrCartiImprumutate = 0;

            if(this->nrCartiImprumutate>0 && listaCartiImprumutate!=nullptr) {
                this->listaCartiImprumutate = new Carti[this->nrCartiImprumutate];
                for(int i=0; i<this->nrCartiImprumutate; i++)
                    this->listaCartiImprumutate[i] = listaCartiImprumutate[i];
            }
            else
                this->listaCartiImprumutate = nullptr;
        }

        friend ostream& operator<<(ostream& ost, Imprumuturi& sursa) {
            cout<<"==========================================="<<endl;
            if(sursa.numeImprumutator!=nullptr)
                cout<<"nume imprumutator: " << sursa.numeImprumutator<<endl;
            else
                cout<<"ERR_NUME_IMPRUMUTATOR"<<endl;

            if(sursa.nrCartiImprumutate>0)
                cout<<"numar de carti imprumutate: "<<sursa.nrCartiImprumutate<<endl;
            else
                cout<<"ERR_NR_CARTI_IMPRUMUTATE"<<endl;

            if(sursa.nrCartiImprumutate>0 && sursa.listaCartiImprumutate!=nullptr) {
                cout<<"cu urmatoarele carti imprumutate: "<<endl;   
                for(int i=0; i<sursa.nrCartiImprumutate; i++)
                    cout<<sursa.listaCartiImprumutate[i];
            }
            else
                cout<<"ERR_LISTA_CARTI_IMPRUMUTATE"<<endl;
            cout<<"==========================================="<<endl;
            return ost;
        }

        Imprumuturi& operator+=(Carti carte) {
            Carti* aux = new Carti[this->nrCartiImprumutate + 1];
            for(int i=0; i<this->nrCartiImprumutate; i++)
                aux[i] = this->listaCartiImprumutate[i];
            aux[this->nrCartiImprumutate] = carte;

            delete[] this->listaCartiImprumutate;
            this->listaCartiImprumutate = nullptr;

            this->nrCartiImprumutate++;

            this->listaCartiImprumutate = new Carti[nrCartiImprumutate];
            for(int i=0; i<this->nrCartiImprumutate; i++)
                this->listaCartiImprumutate[i] = aux[i];

            delete[] aux;
            aux = nullptr;

            return *this;
        }

          Imprumuturi& operator-=(Carti carte) {
            bool gasit = false;
            for(int i=0; i<this->nrCartiImprumutate; i++) {
                if(listaCartiImprumutate[i] == carte)
                    gasit = true;
            }

            if(gasit == true) {
                cout<<"A FOST GAISASDASADfagdasfasd"<<endl;
                Carti* aux = new Carti[this->nrCartiImprumutate - 1];
                int k=0;
                for(int i=0; i<this->nrCartiImprumutate; i++) {
                    if(listaCartiImprumutate[i] != carte)
                        aux[k] = listaCartiImprumutate[i];
                        k++;
                }

                delete[] this->listaCartiImprumutate;
                this->listaCartiImprumutate = nullptr;

                this->nrCartiImprumutate--;

                this->listaCartiImprumutate = new Carti[nrCartiImprumutate];
                for(int i=0; i<this->nrCartiImprumutate; i++)
                    this->listaCartiImprumutate[i] = aux[i];

                delete[] aux;
                aux = nullptr;

            }
        return *this;
        }
};

int Imprumuturi::nr_imprumutatori = 0;
int Carti::nrCarti = 0;

int main() {
    Carti carteEmpty;
    cout<<carteEmpty;

    char* titlu = new char[strlen("basme") + 1];
    strcpy(titlu, "basme");

    Carti carte1(1, titlu, 120);
    cout<<carte1;

    Carti carte2 = carte1;
    cout<<carte2;

    Imprumuturi impEmpty;
    cout<<impEmpty;

    Carti carte3(2, titlu, 230);

    Carti listaCarti[] = {carte1, carte3};
    char* nume = new char[strlen("bratislav") + 1];
    strcpy(nume, "bratislav");

    Imprumuturi imp1(nume, 2, listaCarti);
    cout<<imp1;

    imp1 += carte1;
    cout<<imp1;

    imp1 -= carte1;
    cout<<imp1;
    
}