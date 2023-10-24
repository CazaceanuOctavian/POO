//o modalitate mai eleganta de afisare a lui enum
#include <iostream>
#include <string.h>

using namespace std;

class Tir {
    private:
        char* marcaTir;
        int nrColete;
        int* greutateColete;
        bool esteIncarcat;
        int perioadaFunctionareLuna[12];
        enum limiteViteza { 
            localitate = 50,
            drumNational = 70,
            drumEuropean = 80,
            autostrada = 90
        };
    public:
    Tir() {
        marcaTir = new char[strlen("marcaNeinitializata") + 1];
        strcpy(marcaTir, "marcaNeinitializata");
        nrColete=0;
        greutateColete=nullptr;
        esteIncarcat=false;
        for(int i=0; i<12; i++)
            perioadaFunctionareLuna[i]=0;
    }

    friend ostream &operator << (ostream& ost, limiteViteza& limite) {
        ost << "Limite de viteza:\n";
        ost << "Localitate (50 km/h)\n";
        ost << "Drum National (70 km/h)\n";
        ost << "Drum European (80 km/h)\n";
        ost << "Autostrada (90 km/h)\n";
        return ost;   
    }

    void afisateTir() {
        cout<<"+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+"<<endl;
        cout<<"Marca Tir: "<<marcaTir<<endl;
        if(esteIncarcat) {
            cout<<"Tirul este incarcat si are: ";
            cout<<"Colete Incarcate: "<<nrColete<<" avand urmatoarele greutati " <<endl;
            for(int i=0; i<nrColete; i++)
                cout<<"coletul "<<i+1<<": "<<greutateColete[i]<<" kg" << endl;
        }
        else {
            cout<<"!Nu este incarcat!"<<endl;
        }
        cout<< "Perioada de functionare pe parcursul anului este: "<<endl;
        for(int i=0; i<12; i++)
            cout<<"luna "<<i+1<<": "<<perioadaFunctionareLuna[i]<<" ore" << endl;
        limiteViteza limite;
        cout << limite;
        cout<<"+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+"<<endl;
    }

    void setMarca (const char* marcaData) {
        if(marcaData!=nullptr){
            delete[] marcaTir;
            marcaTir=nullptr;
            marcaTir=new char[strlen(marcaData)+1];
            strcpy(marcaTir, marcaData);
        }
    }

    char* getMarca () {
        return marcaTir;
    }

    void setColete(int nrColeteDat, int* greutateColeteDate) {
        if(nrColeteDat>0) {
            esteIncarcat=true;
            nrColete=nrColeteDat;
            delete[] greutateColete;
            greutateColete=nullptr;
            greutateColete = new int(sizeof(int)*nrColeteDat);
            for(int i=0; i<nrColeteDat; i++)
                greutateColete[i]=greutateColeteDate[i];
        }
        else if(nrColeteDat==0){
            esteIncarcat=false;
            nrColete=nrColeteDat;
            delete[] greutateColete;
            greutateColete=nullptr;
        }
        else {
            cerr<<"apel invalid";
        }
    }

    const int* getGreutateColete() {
        return greutateColete;
    }

    int getNrColete() {
        return nrColete;
    }

    bool getStatusIncarcare() {
        return esteIncarcat;
    }
    //primeste 12 de la 
    void setPerioadaFunctionare(int perioadaFunctionareData[]) {
        for(int i=0; i<12; i++)
            perioadaFunctionareLuna[i]=perioadaFunctionareData[i];
    }
    //se pune const ca sa protejez incapsularea
    //daca nu pun const s-ar putea sa schimbe adresa 
    //const se pune la pointeri
    const int* getPerioadaFunctionare() {
        return perioadaFunctionareLuna;
    }

    ~Tir() {

    }
};

int main() {
    Tir tir, tirNeinitializat;
    tir.setMarca("Volvo");
    int coletCurent[] = {1200, 2980, 3555};
    int perioadaFunctionareCurenta[] = {1300, 1632, 1252, 2111, 0, 0, 0, 1623, 1221, 1562, 1173, 1001};
    tir.setColete(3, coletCurent);
    tir.setPerioadaFunctionare(perioadaFunctionareCurenta);
    tir.afisateTir();

    cout<<tir.getMarca()<<endl;
    cout<<tir.getStatusIncarcare()<<endl;
    cout<<tir.getNrColete()<<endl;
    cout<<tir.getGreutateColete()<<endl;
    cout<<tir.getPerioadaFunctionare()<<endl;
    
    tir.setColete(0, NULL);
    tir.afisateTir();

    tirNeinitializat.afisateTir();
    
}
