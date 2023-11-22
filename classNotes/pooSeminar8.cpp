#include<iostream>
#include<fstream>
using namespace std;
//abordam relatia has a


class Cadou {
private:
	string denumire = "Anonim";
	float pret = 0;

public:
    //daca nu am constructorul gol, nu pot sa declar de ex un vector de tip cadou static
	Cadou()
	{
	}

	Cadou(string denumire, float pret)
	{
		this->denumire = denumire;
		this->pret = pret;
	}

	Cadou(const Cadou& c)
	{
		this->denumire = c.denumire;
		this->pret = c.pret;
	}

	Cadou& operator=(const Cadou& c)
	{
		this->denumire = c.denumire;
		this->pret = c.pret;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Cadou& c)
	{
		out << "\nDenumire: " << c.denumire << ", pret: " << c.pret;
		return out;
	}
	friend istream& operator>>(istream& in, Cadou& c)
	{
		cout << "Introduceti denumire: ";
		in >> c.denumire;
		cout << "Introduceti pret: ";
		in >> c.pret;
		return in;
	}
};

//wishlist has a 
class WishList1 {
    string detinator;
    Cadou listaCadouri[100];
    int nrCadouri;
};

//vector static de pointere catre cadouri
//optimizarea se face pe transferul obiectelor 
class WishList2 {
    string detinator;
    Cadou* listaCadouri[100];
    int nrCadouri;
};

//vector alocat dinamic de cadouri pentru ca am si int
class WishList3 {
    string detinator;
    Cadou* listaCadouri;
    int nrCadouri;
};

//detine referinta unui singur obiect --> nu e o lista
class WishList4 {
    string detinator;
    Cadou* cadouSpecial;
};

//matrice alocata dinamic de cadou*
//daca aveam *** --> adresa unei martici de cadouri
//separat avem un vector de ex: 2 3 1 --> pe baza lui alocam 
//fiecare dimensiune a cadounui din matrice
//matricea cadourilor se numeste zig zag pentru ca variaza size-ul 
//fiecarui element

class WishList5 {
    string detinator;
    int nrPrieteni;
    int* nrCadouriPrieteni;
    Cadou** listaCadouri;
};

//numarul de linii e 24, restul sunt variabile 
//cand am o alocare de dimensiune fixa ea se refera la primul lucru
//din matrice adica 24
//aloc dinamic coloanele 
//o matrice semidinamica care stocheaza pointeri la cadou
class WishList6 {
    string detinator;
    int nrCadouriZi[24];
    Cadou** cadouSpecial[24];
};

//vector dinamic de 
class WishList {
    string detinator="Anon";
    Cadou** listaCadouri=nullptr;
    int nrCadouri=0;
    
    public:
        WishList() {

        }
    
    //pot sa primesc ca parametrii si alte tipuri (in loc de string char de ex)
    WishList(string detinator, Cadou** listaCadouri, int nrCadouri) {
        this->detinator=detinator;
        if(nrCadouri > 0 && listaCadouri != nullptr) {
            this->nrCadouri = nrCadouri;
            //this o sa pointeze spre o zona de memorie
            //fac shallow copy! NU e bine
            //this->listaCadouri = listaCadouri;
            this->listaCadouri = new Cadou*[this->nrCadouri];
            for(int i=0; i<this->nrCadouri; i++)
                //shallow copy care ar merge
                //this->listaCadouri[i] = listaCadouri[i];
                //dereferentiez 
                //se apeleaza constructorul de copiere si se face deep copy
                this->listaCadouri[i] = new Cadou(*listaCadouri[i]);
        }
    }

    WishList(const WishList& w) {
        this->detinator=w.detinator;
        if(w.nrCadouri > 0 && w.listaCadouri != nullptr) {
            this->nrCadouri = w.nrCadouri;
            //this o sa pointeze spre o zona de memorie
            //fac shallow copy! NU e bine
            //this->listaCadouri = listaCadouri;
            this->listaCadouri = new Cadou*[this->nrCadouri];
            for(int i=0; i<this->nrCadouri; i++)
                //shallow copy care ar merge
                //this->listaCadouri[i] = listaCadouri[i];
                //dereferentiez 
                //se apeleaza constructorul de copiere si se face deep copy
                this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
        }
    }

    WishList& operator=(const WishList& w) {
        //layer 1 
        if(this!= &w) {
            for(int i=0; i<this->nrCadouri; i++) {
                delete this->listaCadouri[i];
                this->listaCadouri[i]=nullptr;
            }
            //layer 2
            delete[] this->listaCadouri;
            this->listaCadouri = nullptr;

            //======
            this->detinator=detinator;
            if(nrCadouri > 0 && listaCadouri != nullptr) {
                this->nrCadouri = nrCadouri;
                //this o sa pointeze spre o zona de memorie
                //fac shallow copy! NU e bine
                //this->listaCadouri = listaCadouri;
                this->listaCadouri = new Cadou*[this->nrCadouri];
                for(int i=0; i<this->nrCadouri; i++)
                    //shallow copy care ar merge
                    //this->listaCadouri[i] = listaCadouri[i];
                    //dereferentiez 
                    //se apeleaza constructorul de copiere si se face deep copy
                    this->listaCadouri[i] = new Cadou(*listaCadouri[i]);
            }
        }
        //fac else pt ca nu mai avem safety net
        else {
            this->nrCadouri=0;

        }
    }

    friend ostream& operator<<(ostream& out, const WishList& w) {
        out<<"Detinator" << w.detinator;
        //... etc

        for(int i=0; i<w.nrCadouri; i++)
            //daca nu il dereferentiez va returna pur si simplu adrese
            out<< *w.listaCadouri[i];
        return out;
    }

    //distrugerea se face de jos in sus, altfel am memory leaks
    //delete cu [] cand am alocat cu []
    ~WishList() {
        //layer 1 
        for(int i=0; i<this->nrCadouri; i++) {
            delete this->listaCadouri[i];
            this->listaCadouri[i]=nullptr;
        }
        //layer 2
        delete[] this->listaCadouri;
        this->listaCadouri = nullptr;
    }
};

int main()
{
	Cadou c1("stilou", 100);
    Cadou c2("Carte", 250);
    Cadou c3("Papusa", 200);
    //nu se apeleaza nimic pentru ca lucrez cu adrese;
    //sunt in shallow copy
    Cadou* lista[] = {&c1, &c2, &c3};
    WishList w("DMZ", lista, 3);
    cout<< w;

    WishList w2 = w;
    cout<<w2;

    WishList w3;
    w3 = w2;
    cout<<w3;

    //cast la float pentru clasa cadou si operator de indexare 
    float pretMinim=w[0];

    //cast de la wishList la cadou in calsa WishList 
    Cadou cadouPretMinim = w;
}