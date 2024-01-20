#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

class IFile {
    virtual void saveToFile(fstream& file) = 0;
    virtual void readFromFile(fstream& file) = 0;
};

class Eveniment : IFile{
    private:
        int nrPers;
        char** numePersoane;
        string locatie;
        float pretBilet;
    public:
        Eveniment() {
            this->nrPers = 0;
            this->numePersoane = nullptr;
            this->locatie = "FARA_LOCATIE";
            this->pretBilet = 0;
        }

        Eveniment(int nrPers, char** numePersoane, string locatie, float pretBilet) {
            if(nrPers > 0)
                this->nrPers = nrPers;
            else
                this->nrPers = 0;

            if(this->nrPers > 0 && numePersoane != nullptr) {
                this->numePersoane = new char*[this->nrPers];
                for(int i=0; i<this->nrPers; i++)
                    this->numePersoane[i] = numePersoane[i];
            }
            else
                this->numePersoane = nullptr;

            if(locatie.length() > 0)
                this->locatie = locatie;
            else
                this->locatie = "FARA_LOCATIE";
            
            if(pretBilet > 0)
                this->pretBilet = pretBilet;
            else
                this->pretBilet = 0;
        }

        friend ostream& operator<<(ostream& ost, Eveniment& sursa) {
            cout<<"============================================"<<endl;
            if(sursa.nrPers > 0)
                cout<<"numar persoane: "<<sursa.nrPers<<endl;
            else
                cout<<"ERR_NR_PERSONAE"<<endl;
            
            if(sursa.nrPers > 0 && sursa.numePersoane!=nullptr) {
                cout<<"persoanele au numele: "<<endl;
                for(int i=0; i<sursa.nrPers; i++)
                    cout<<"persoana " << i << " cu numele: " << sursa.numePersoane[i]<<endl;
            }
            else
                cout<<"ERR_NUME_PERSOANE"<<endl;

            if(sursa.locatie.length()>0)
                cout<<"locatia: "<<sursa.locatie<<endl;
            else
                cout<<"ERR_LOCATIE"<<endl;

            if(sursa.pretBilet>0)
                cout<<"pret bilet: "<<sursa.pretBilet<<endl;
            else
                cout<<"ERR_PRET_BILET"<<endl;
            cout<<"============================================"<<endl;
            return ost;
        }

        friend ofstream& operator<<(ofstream& out, Eveniment& sursa) {
            out<<sursa.nrPers;
            for(int i=0; i<sursa.nrPers; i++)
                out<<sursa.numePersoane[i];
            out<<sursa.locatie;
            out<<sursa.pretBilet;
            return out;
        }

        friend ifstream& operator>>(ifstream& in, Eveniment& sursa) {
            in>>sursa.nrPers;
            sursa.numePersoane = new char*[sursa.nrPers];
            for(int i=0; i<sursa.nrPers; i++) {
                string buffer;
                in>>buffer;
                sursa.numePersoane[i] = new char[buffer.size() + 1];
                strcpy(sursa.numePersoane[i], buffer.data());
            }
            in>>sursa.locatie;
            in>>sursa.pretBilet;
            return in;
        }

        void saveToFile(fstream& file) {
            file.write((char*)&this->nrPers, sizeof(int));
            int lgLoc = this->locatie.length() + 1;
            file.write((char*)&lgLoc, sizeof(int));
            file.write(this->locatie.data(), lgLoc);
            for(int i=0; i<this->nrPers; i++) {
                int lgPers = strlen(this->numePersoane[i]) + 1;
                file.write((char*)&lgPers, sizeof(int));
                file.write(this->numePersoane[i], lgPers);
            }
            file.write((char*)&this->pretBilet, sizeof(float));
        }

        void readFromFile(fstream& file) {
            file.read((char*)&this->nrPers, sizeof(int));
            int lgLoc;
            file.read((char*)&lgLoc, sizeof(int));
            char* buffer = new char[lgLoc];
            file.read(buffer, lgLoc);
            this->locatie = buffer;
            this->numePersoane = new char*[this->nrPers];
            for(int i=0; i<this->nrPers; i++) {
                int lgPers;
                file.read((char*)&lgPers, sizeof(int));
                this->numePersoane[i] = new char[lgPers];
                file.read(this->numePersoane[i], lgPers);

            }
            file.read((char*)&this->pretBilet, sizeof(float));
        }
};

int main() {
    Eveniment evEmpty;
    cout<<evEmpty;

    char** listaPers = new char*[3];
    listaPers[0] = new char[strlen("ana") + 1];
    strcpy(listaPers[0], "ana");
    
    listaPers[1] = new char[strlen("bratislav") + 1];
    strcpy(listaPers[1], "bratislav");
    
    listaPers[2] = new char[strlen("costi") + 1];
    strcpy(listaPers[2], "costi");

    Eveniment ev1(3, listaPers, "neversea", 600);
    cout<<ev1;

    ofstream g("evenimente_dump.txt");
    ifstream f("evenimente.txt");

    Eveniment ev2;
    f>>ev2;
    cout<<ev2;
    g<<ev1;

    //fstream file("colectie.bin", ios::out | ios::binary);
    fstream file("colectie.bin", ios::in | ios::binary);

    Eveniment ev3;
    ev3.readFromFile(file);
    cout<<ev3;
    
    //ev2.saveToFile(file);
}