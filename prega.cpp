#include <iostream>
#include <string.h>

using namespace std;

class DalmatianJavra {
    private:
        static int nrJavre;
        char* numeJavra;
        int peteCuloare;
        //reprezinta suprafata fiecarei pete de culoare de pe javra
        float* suprafataPataCuloare;
    public:
    DalmatianJavra () {
        this->numeJavra=nullptr;
        this->peteCuloare=0;
        this->suprafataPataCuloare=nullptr;
    }

    DalmatianJavra(char* numeJavra, int peteCuloare, float* suprafataPataCuloare) {
        if(numeJavra!=nullptr) {
            this->numeJavra = new char[strlen(numeJavra) + 1];
            strcpy(this->numeJavra, numeJavra);
        }
        else {
            this->numeJavra=nullptr;
        }
        if(peteCuloare>0)
            this->peteCuloare=peteCuloare;
        else
            this->peteCuloare=0;
        if(this->peteCuloare>0 && suprafataPataCuloare!=nullptr) {
            this->suprafataPataCuloare= new float[this->peteCuloare];
            for(int i=0; i<this->peteCuloare; i++)
                this->suprafataPataCuloare[i] = suprafataPataCuloare[i];
        }
    }

    friend ostream& operator<<(ostream& ost, DalmatianJavra& sursa) {
        cout<<"==============================================="<<endl;
        if(sursa.numeJavra!=nullptr)
            cout<<"numeJavra: "<<sursa.numeJavra<<endl;
        else
            cout<<"javra nu are nume"<<endl;
        cout<<"nrPeteCuloare: "<<sursa.peteCuloare<<endl;
        if(sursa.peteCuloare>0 && sursa.suprafataPataCuloare!=nullptr) {
            cout<<"petele de culoare de pe javra au suprafata: ";
            for(int i=0; i<sursa.peteCuloare; i++)
                cout<<sursa.suprafataPataCuloare[i]<<" | ";
            cout<<endl;
        }
        cout<<"==============================================="<<endl;
        return ost;
    }

};

//int DalmatinaJavra::nrJavre = 0;

int main() {
    char* nume = new char[strlen("gigi") + 1];
    strcpy(nume, "gigi");

    float* suprfPete = new float[3];
    suprfPete[0] = 7;
    suprfPete[1] = 5.32;
    suprfPete[2] = 3.141;
    DalmatianJavra dalm(nume, 3, suprfPete);

    cout<< dalm;
}