#include <iostream>
#include <string.h>

using namespace std;

class GradinaZoo{
    private:
        string denumire;
        int nrAnimale;
        char** listaAnimale;
        int nrTarife;
        int* tarifeIntrare;
        int tarifeIncasateLuna[12];
    public:
        GradinaZoo() {
            this->denumire="N/A";
            this->nrAnimale=0;
            this->listaAnimale=nullptr;
            this->nrTarife=0;
            this->tarifeIntrare=nullptr;
            /*for(int i=0; i<12; i++)
                tarifeIncasateLuna[i]=0;*/
        }
        GradinaZoo(string denumire, int nrAnimale, char** listaAnimale, int nrTarife, 
                   int* tarifeIntrare, int tarifeIncasateLuna[]) {
            this->denumire=denumire;
            if(nrAnimale>0 && listaAnimale!=nullptr) {
                this->nrAnimale=nrAnimale;
                this->listaAnimale=new char*[this->nrAnimale];
                for(int i=0; i<nrAnimale; i++) {
                    this->listaAnimale[i] = new char[strlen(listaAnimale[i])+1];
                    strcpy(this->listaAnimale[i], listaAnimale[i]);
                }
            }
            else {
                nrAnimale=0;
                listaAnimale=nullptr;
            }
            if(nrTarife!=0 && tarifeIntrare!=nullptr) {
                this->nrTarife=nrTarife;
                this->tarifeIntrare = new int(sizeof(int)*nrTarife);
                for(int i=0; i<nrTarife; i++)
                    this->tarifeIntrare[i] = tarifeIntrare[i];
            }
            else {
                this->nrTarife=0;
                this->tarifeIntrare=nullptr;
            }
            //??
            for(int i=0; i<12; i++)
                this->tarifeIncasateLuna[i] = tarifeIncasateLuna[i];
        }

        GradinaZoo(GradinaZoo &sursa) {
            this->denumire=sursa.denumire;
            if(sursa.nrAnimale>0 && sursa.listaAnimale!=nullptr) {
                this->nrAnimale=nrAnimale;
                this->listaAnimale=new char*[this->nrAnimale];
                for(int i=0; i<sursa.nrAnimale; i++) {
                    this->listaAnimale[i] = new char[strlen(listaAnimale[i])+1];
                    strcpy(this->listaAnimale[i], sursa.listaAnimale[i]);
                }
            }
            else {
                this->nrAnimale=0;
                this->listaAnimale=nullptr;
            }
            if(nrTarife!=0 && tarifeIntrare!=nullptr) {
                this->nrTarife=nrTarife;
                this->tarifeIntrare = new int(sizeof(int)*nrTarife);
                for(int i=0; i<sursa.nrTarife; i++)
                    this->tarifeIntrare[i] = sursa.tarifeIntrare[i];
            }
            else {
                this->nrTarife=0;
                this->tarifeIntrare=nullptr;
            }
            //??
            for(int i=0; i<12; i++)
                this->tarifeIncasateLuna[i] = sursa.tarifeIncasateLuna[i];
        }

        void afisare() {
            cout<<"+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+"<<endl;
            cout << "Denumire: " << this->denumire << endl;
            if(this->nrAnimale>0) {
                cout << "Gradina Zoologica are: " << this->nrAnimale << " animale din speciile" << endl;
                for(int i=0; i<nrAnimale; i++)
                    cout<<this->listaAnimale[i]<<" | ";
                cout<<endl;
            }
            else 
                cout<<"!!Gradina Zoologica nu are animale!!"<<endl;

            if(this->nrTarife>0){
                cout << "Gradina Zoologica are " << this->nrTarife << " tarife in valoare de: " << endl;
                for(int i=0; i<nrTarife; i++)
                    cout<<this->tarifeIntrare[i]<<" | ";
                cout<<endl;
            }
            else
                cout<<"!!Gradina Zoologica nu are tarife!!"<<endl;

            cout<<"Incasarile din tarife pe parcursul anului fiind de: ";
            for(int i=0; i<12; i++) {
                cout<<tarifeIncasateLuna[i]<<" | ";
            }
            cout<<endl;
            cout<<"+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+"<<endl;
        }

        const char** getListaAnimale() {
            return this->listaAnimale;
        }

        const int* getTarifeIntrare() {
            return this->tarifeIntrare;
        }

        int getIncasariMax() {
            int max = this->tarifeIncasateLuna[0];
            for(int i=1; i<12; i++)
                if(tarifeIncasateLuna[i]>max)
                    max=tarifeIncasateLuna[i];
            return max;
        }

        void sorteazaIncasari() {
            bool swapped;
            for (int i = 0; i < 12 - 1 ; i++) {
                swapped = false;
                for (int j = 0; j < 12 - i - 1; j++) {
                    if (this->tarifeIncasateLuna[j] > this->tarifeIncasateLuna[j + 1]) {
                        int aux1 = this->tarifeIncasateLuna[i];
                        int aux2 = this->tarifeIncasateLuna[j];
                        this->tarifeIncasateLuna[i] = aux2;
                        this->tarifeIncasateLuna[j + 1] = aux1;
                        swapped = true;
                    }
                }
                if (swapped == false)
                    break;
            }
        }

        void addTarif(int tarifNou) {
            int* aux = this->tarifeIntrare;
            nrTarife++;
            tarifeIntrare = new int[nrTarife];
            for(int i=0; i<nrTarife-1; i++)
                tarifeIntrare[i]=aux[i];
            tarifeIntrare[nrTarife-1]=tarifNou;
            delete[] aux;
        }

        void deleteTarif(int pozTarif) {
            int* aux = this->tarifeIntrare;
            nrTarife--;
            tarifeIntrare=new int[nrTarife];
            for(int i=0; i<nrTarife; i++) {
                if(i!=pozTarif)
                    tarifeIntrare[i]=aux[i];
            }
            delete[] aux;
        }

        ~GradinaZoo() {
            delete[] this->listaAnimale;
            this->listaAnimale=nullptr;
            delete[] this->tarifeIntrare;
            this->tarifeIntrare=nullptr;
        }
};

int main() {
    char** listaAnimale = new char*[3];
    listaAnimale[0] = new char[6];
    strcpy(listaAnimale[0], "TIGRU");
    listaAnimale[1] = new char[4];
    strcpy(listaAnimale[1], "LEU");
    listaAnimale[2] = new char[7];
    strcpy(listaAnimale[2], "GAZELA");

    int tarife[]={15, 25, 50};
    int tarifeIncasateLuna[] = {1500, 1300, 8900, 5400, 1210, 0, 0, 9880, 1715, 7880, 0, 0};

    GradinaZoo zoo("AFRICA", 3, listaAnimale, 3, tarife, tarifeIncasateLuna);
    zoo.afisare();

    cout<<zoo.getIncasariMax();
    zoo.sorteazaIncasari();
    zoo.afisare();
    
}