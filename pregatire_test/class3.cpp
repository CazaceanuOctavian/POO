#include <iostream>
#include <string.h>

using namespace std;

class Cadou {
    private:
        string denumire;
        float pret;
    public:
        Cadou() {
            this->denumire = "ANON";
            this->pret = 0;
        }

        Cadou(string denumire, float pret) {
            this->denumire = denumire;
            if(pret > 0)
                this->pret = pret;
            else
                this->pret = 0;
        }

        friend ostream& operator<<(ostream& ost, const Cadou& sursa) {
            cout<<"================================================"<<endl;
            cout<<"tip_CADOU"<<endl;
            cout<<"denumire: "<<sursa.denumire<<endl;
            cout<<"pret: "<<sursa.pret<<endl;
            cout<<"================================================"<<endl;
            return ost;
        }

        friend istream& operator>>(istream& in, Cadou& sursa) {
            cout<<"denumire cadou: "<<endl;
            cin>> sursa.denumire;
            cout<<"pret cadou: "<<endl;
            cin>> sursa.pret;
            return in;
        }
};
//cand dai free la memorie si ai pointeri foloseste delete, nu delete[], uitat-te mai jos
//nu fi idiot :D
class WishList {
    private:
        string detinator;
        int nrCadouri;
        Cadou** listaCadouri;
    public:
        WishList() {
            this->detinator = "ANON";
            this->nrCadouri = 0;
            this->listaCadouri = nullptr;
        }

        WishList(string detinator, int nrCadouri, Cadou** listaCadouri) {
            this->detinator = detinator;
            if(nrCadouri>0)
                this->nrCadouri = nrCadouri;
            if(this->nrCadouri > 0 && listaCadouri!=nullptr) {
                this->listaCadouri = new Cadou*[this->nrCadouri];
                for(int i=0; i<this->nrCadouri; i++) {
                    this->listaCadouri[i] = new Cadou(*listaCadouri[i]);
                }
            }
        }

        WishList(const WishList& sursa) {
            this->detinator = sursa.detinator;
            if(sursa.nrCadouri>0)
                this->nrCadouri = sursa.nrCadouri;
            if(this->nrCadouri > 0 && sursa.listaCadouri!=nullptr) {
                this->listaCadouri = new Cadou*[this->nrCadouri];
                for(int i=0; i<this->nrCadouri; i++) {
                    this->listaCadouri[i] = new Cadou(*sursa.listaCadouri[i]);
                }
            }
        }

        WishList& operator=(const WishList& sursa) {
            if(this != &sursa) {
                for(int i=0; i<this->nrCadouri; i++) {
                    delete this->listaCadouri[i];
                    this->listaCadouri[i] = nullptr;
                }

                delete[] this->listaCadouri;
                this->listaCadouri = nullptr;

                this->detinator = sursa.detinator;
                if(sursa.nrCadouri>0)
                    this->nrCadouri = sursa.nrCadouri;
                if(this->nrCadouri > 0 && sursa.listaCadouri!=nullptr) {
                    this->listaCadouri = new Cadou*[this->nrCadouri];
                    for(int i=0; i<this->nrCadouri; i++) {
                        this->listaCadouri[i] = new Cadou(*sursa.listaCadouri[i]);
                    }
                }
            }
            return *this;
        }

        friend ostream& operator<<(ostream& ost, const WishList& sursa) {
            cout<<"------------------------------------------------"<<endl;
            if(sursa.detinator.length() > 0)
                cout<<"detinator: "<<sursa.detinator<<endl;
            else
                cout<<"ANON"<<endl;
            
            if(sursa.nrCadouri > 0)
                cout<<"numar cadouri: "<<sursa.nrCadouri<<endl;
            else
                cout<<"FARA_NR_CADOURI"<<endl;

            if(sursa.nrCadouri > 0 && sursa.listaCadouri!=nullptr) {
                cout<<"Lista de cadouri: "<<endl;
                for(int i=0; i<sursa.nrCadouri; i++)
                    cout<<(*sursa.listaCadouri[i])<<endl;
            }
            else
                cout<<"FARA_LISTA_CADOURI"<<endl;
            cout<<"------------------------------------------------"<<endl;
            return ost;
        }  

        ~WishList() {
            for(int i=0; i<this->nrCadouri; i++){
                delete this->listaCadouri[i];
                this->listaCadouri[i] = nullptr;
            }

            delete[] this->listaCadouri;
        }
};

class WishList2 {
    private: 
        char* detinator;
        int nrCadouri;
        Cadou* listaCadouri;
    public:
        WishList2() {
            this->detinator = nullptr;
            nrCadouri = 0;
            this->listaCadouri = nullptr;
        }

        WishList2(char* detinator, int nrCadouri, Cadou* listaCadouri) {
            if(detinator != nullptr) {
                this->detinator = new char[strlen(detinator) + 1];
                strcpy(this->detinator, detinator);
            }
            else
                this->detinator = nullptr;
            
            if(nrCadouri > 0)
                this->nrCadouri = nrCadouri;
            else
                this->nrCadouri = 0;

            if(this->nrCadouri>0 && listaCadouri!=nullptr) {
                this->listaCadouri = new Cadou[this->nrCadouri];
                for(int i=0; i<this->nrCadouri; i++)
                    this->listaCadouri[i] = listaCadouri[i];
            }
            else
                this->listaCadouri = nullptr;
        }

         WishList2(const WishList2& sursa) {
            if(sursa.detinator != nullptr) {
                this->detinator = new char[strlen(sursa.detinator) + 1];
                strcpy(this->detinator, sursa.detinator);
            }
            else
                this->detinator = nullptr;
            
            if(sursa.nrCadouri > 0)
                this->nrCadouri = sursa.nrCadouri;
            else
                this->nrCadouri = 0;

            if(this->nrCadouri>0 && listaCadouri!=nullptr) {
                this->listaCadouri = new Cadou[this->nrCadouri];
                for(int i=0; i<this->nrCadouri; i++)
                    this->listaCadouri[i] = sursa.listaCadouri[i];
            }
            else
                this->listaCadouri = nullptr;
        }


        friend ostream& operator<<(ostream& ost, const WishList2& sursa) {
            cout<<"------------------------------------------------"<<endl;
            if(sursa.detinator != nullptr)
                cout<<"detinator: "<<sursa.detinator<<endl;
            else
                cout<<"FARA_NUME"<<endl;
            
            if(sursa.nrCadouri > 0)
                cout<<"numar cadouri: "<<sursa.nrCadouri<<endl;
            else
                cout<<"FARA_NR_CADOURI"<<endl;

            if(sursa.nrCadouri > 0 && sursa.listaCadouri!=nullptr) {
                cout<<"Lista de cadouri: "<<endl;
                for(int i=0; i<sursa.nrCadouri; i++)
                    cout<<sursa.listaCadouri[i]<<endl;
            }
            else
                cout<<"FARA_LISTA_CADOURI"<<endl;
            cout<<"------------------------------------------------"<<endl;
            return ost;
        }  

        ~WishList2() {
            delete[] this->listaCadouri;
            this->listaCadouri = nullptr;

            delete[] this->detinator;
            this->detinator = nullptr;
        }
};

int main() {
    Cadou cadouEmpty;
    cout<<cadouEmpty;

    Cadou cad1("robotel", 150);
    Cadou cad2("papusica", 110);

    cout<<cad1<<cad2;

    WishList listEmpty;
    cout<<listEmpty;

    Cadou** listaCadou = new Cadou*[3];
    listaCadou[0] = new Cadou("catelus", 20);
    listaCadou[1] = new Cadou("masinuta", 50);
    listaCadou[2] = new Cadou("rtx3060", 1900);

    Cadou* listaCadou2[] = {&cad1, &cad2};

    WishList list1("ana", 2, listaCadou2);
    cout<<list1;

    cout<<"CPY CONSTR"<<endl;
    WishList list2 = list1;
    cout<<list2;

    cout<<"= OPER"<<endl;
    WishList list3;
    list3 = list1;
    cout<<list3;

    WishList2 list2_empty;
    cout<<list2_empty;

    
    Cadou cad5("album", 399);
    Cadou cad6("catelus", 199);
    Cadou cad7("cactus", 150);
    Cadou cad8("camila", 7899);
    Cadou listaCadouNou[] = {cad5, cad6, cad7, cad8};

    char* nume = new char[strlen("marta") + 1];
    strcpy(nume, "marta");
    WishList2 list2_1(nume, 4, listaCadouNou);
    cout<<list2_1;

    WishList2 listTest = list2_1;
    cout<<listTest;

}