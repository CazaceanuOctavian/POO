//legenda in care expunem cum functuoneaza
//un string pe care il parsez si bazat pe comanda actionez corespunzator
//ex:
//CMD pizza 3, buger 2 --> cand execut comanda mi se realizeaza ceva
//AFIS MENIU mic dejun

//==========================
//trivia
//vector cu elemente distincte --> fiecare prdous are un vector de string-uri
//implementez operatorul ca sa faca p["soia"] --> returnarea pozitie pe care este soia

//========================
//cum putem sa citim atribute constante intr-un istream
//cum ducem istream la forma cea mai aproape de >>
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
using namespace std;

class ExceptieExistentaDenumire {
	string mesaj;
public:
	ExceptieExistentaDenumire(string mesaj) :mesaj(mesaj) {}
	string getMesaj() { return this->mesaj; }
};

class Produs
{
	char* denumire = nullptr;
	int nrZile = 0;
	float* preturi = nullptr;
	int stoc = 0;

public:
	Produs(const char* denumire, int stoc)
	{
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		if (stoc > 0)
			this->stoc = stoc;
	}

	Produs(const Produs& p)
	{
		if (p.denumire != nullptr) {
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
		}
		this->stoc = p.stoc;
		this->nrZile = p.nrZile;
		this->preturi = new float[this->nrZile];
		for (int i = 0; i < this->nrZile; i++)
			this->preturi[i] = p.preturi[i];
	}

	Produs& operator=(const Produs& p)
	{
		if (this != &p) {
			delete[] this->denumire;
			this->denumire = nullptr;
			delete[] this->preturi;
			this->preturi = nullptr;
			if (p.denumire != nullptr) {
				this->denumire = new char[strlen(p.denumire) + 1];
				strcpy(this->denumire, p.denumire);
			}
			this->stoc = p.stoc;
			this->nrZile = p.nrZile;
			this->preturi = new float[this->nrZile];
			for (int i = 0; i < this->nrZile; i++)
				this->preturi[i] = p.preturi[i];
		}
		return *this;
	}

	bool operator>(Produs p) {
		if (this->preturi != nullptr && p.preturi != nullptr) {
			if (this->preturi[this->nrZile - 1] > p.preturi[p.nrZile - 1])
				return true;
			return false;
		}
		else {
			throw exception("nu ambele obj au preturi");
		}
	}

	void adaugaPret(float pretNou)
	{
		if (pretNou > 0 && (this->nrZile == 0 || (pretNou != this->preturi[this->nrZile - 1]))) {
			Produs p = *this;
			delete[] this->preturi;
			this->nrZile++;
			this->preturi = new float[this->nrZile];
			for (int i = 0; i < p.nrZile; i++)
				this->preturi[i] = p.preturi[i];
			this->preturi[this->nrZile - 1] = pretNou;
		}
	}

	void afisare()
	{
		cout << "\n--------------------";
		if (this->denumire != nullptr) {
			cout << "\nDenumire: " << this->denumire;
		}
		else {
			cout << "\nDenumire: -";
		}
		cout << "\nStoc: " << this->stoc;
		cout << "\nNr zile: " << this->nrZile;
		cout << "\nIstoric preturi: ";
		if (this->nrZile > 0) {
			for (int i = 0; i < this->nrZile; i++)
				cout << this->preturi[i] << " ";
		}
		else {
			cout << "-";
		}
		cout << "\n--------------------";
	}

	~Produs()
	{
		delete[] this->denumire;
		this->denumire = nullptr;
		delete[] this->preturi;
		this->preturi = nullptr;
	}

	bool operator==(string denumire) {
		return this->denumire == denumire;
	}

	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\n------<<-------";
		if (p.denumire != nullptr) {
			out << "\nDenumire: " << p.denumire;
		}
		else {
			out << "\nDenumire: -";
		}
		out << "\nStoc: " << p.stoc;
		out << "\nNr zile: " << p.nrZile;
		out << "\nIstoric preturi: ";
		if (p.nrZile > 0) {
			for (int i = 0; i < p.nrZile; i++)
				out << p.preturi[i] << " ";
		}
		else {
			out << "-";
		}
		out << "\n--------------------";
		return out;
	}
	//==================================
	//returunul prin referinta se face pe obicete care persista
	//daca returnez Produs& returnez un obiect de pe stiva care se distruege
	//pot sa folosesc & cand vorbesc de pe elemente care nu sunt pe stiva 
	//adica cand returnez this-ul 
	Produs operator+(int stocSuplimentar) {
		if(stocSuplimentar>0) {
			Produs rez = *this; //dereferentiem left value
			rez.stoc += stocSuplimentar;
			return rez;
		}
	}

	//actualizeaza this-ul
	//putem pune acum & 
	//nu este obligatoriu, este strict pentru optimizare
	Produs& operator+=(int stocSuplimentar) {
		if(stocSuplimentar > 0)
			this->stoc += stocSuplimentar;
			return *this;
	}

	//forma de preincrementare a lui ++;
	Produs& operator++() {
		this->stoc++;
		//returneaza obiectul de dupa incrementare
		return *this;
	}

	//am int value doar ca sa fac diferenta intre cele doua forme
	//forma de postincremetare
	Produs operator++(int value) {
		//starea obiectului de dinainte de incrementare
		Produs copie = *this;
		this->stoc++;
		//returneaza obiectul de dinainte de incremetare
		return copie;
	}

	//este un fel de getter, pot sa fac return prin referinta & dar 
	//nu are sens pentru un getter sa pot sa modific
	float operator[](int pozitie) {
		//sparg in doua if-uri pentru ca unul tine de input si altul tine de obiect
		//de ex pot sa arunc doua exceptii astfel unua pentru input si alta pentru obiect
		if(pozitie>=0 && pozitie < this->nrZile) {
			if(this->preturi != nullptr) {
				return this->preturi[pozitie];
			}
		}
	}

	//am return true si return false --> este o constanta si nu o variabila
	//asa ca nu o returnez prin referinta
	bool operator()(int stocMinim) {
		if(stocMinim > 0)
			return this->stoc>=stocMinim;
	}

	bool operator!() {
		return !this->stoc;
	}

	explicit operator int() {
		return this->stoc;
	}

	friend istream& operator>>(istream& in, Produs& p) {
		delete[] p.denumire;
		p.denumire = nullptr;
		delete[] p.preturi;
		//trebuie sa aloc zona de memorie pentru denumire
		//daca am un sir de caractere mai mare ca bufferul o sa am probleme
		char buffer[100];
		in >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer)
	}

	//acceasi inmplementare doar ca cu string
	friend istream& operator>>(istream& in, Produs& p) {
		delete[] p.denumire;
		p.denumire = nullptr;
		delete[] p.preturi;
		string buffer;
		in>>buffer;
		p.denumire = new char[buffer.size()+1]
		//pot sa folosesc metoda data care sa returneze char* din string
		strcpy(p.denumire, buffer.data());

		//trebuie sa facem validari 
		//daca introduce un stoc gresit facem noi un stoc default 
		//nu aruncam exceptii pentru ca obiectul este semicitit
		//daca aruncam exceptii se fac mai devreme
		cout<<"Introduceti un stoc: ";
		in >> p.stoc;

		if(p.stoc<0)
			p.stoc=0;

		cout<<"Introduceti nr zile analiza preturi: ";

		//VALIDARI PE DIMENSIUNE VECTOR SI VECTOR
		in>> p.nrZile;
		if(p.nrZile<=0) {
			p.nrZile =0;
			p.preturi=nullptr;
		}
		//puteam sa fac validari mult mai deep aici
		else {
			p.preturi = new float[p.nrZile];
			for(int i=0; i< p.nrZile; i++) {
				cout<<"pret["<<i<<"]=";
				in>>p.preturi[i];
			}
		}

	}

};

bool operator==(string denumire, Produs p) {
	return p == denumire;
}

//la lucrare mai intai facem ceea ce se cere si apoi 
//infrumusetam (de ex fac sa arunce exceptii)
int main()
{
	Produs p1("Pix", 100);
	p1.adaugaPret(12);
	p1.adaugaPret(12);
	p1.adaugaPret(10);

	Produs p2("Stilou", 10);
	p2.adaugaPret(760);
	p2.adaugaPret(900);

	p1.afisare();
	p2.afisare();

	Produs p3(nullptr, 0);
	p3.afisare();

	//p3 = p2 = p1;//apel in cascada (deci nu void)
	//p3.afisare();

	p2 = p2;//auto asignare
	p2.afisare();

	//sens marim stocul cu cat primim value
	//se apeleaza overload-ul de +
	p3 = p2 + 10;

	//sens marim stocul ca cat primim value
	//trebuie sa returneze obict de tip produs
	p3+=10;

	//++ are impact doar cand il combinam cu alti operatori 
	//p1 primeste stocul initial al lui p3 si apoi se mareste
	p1=p3++;
	cout<<p1;

	//p1 primeste stocul deja marit a lui p3;
	p1=++p3;
	++p3;

	float pret = p3[0];

	//pretul mediu de pe pozitiile 1-4
		//float pretMediu = p3(1, 4);
		/*//daca am cel putin 12 elem in stoc pentru produs
		bool existaStoc = p3(12);
		Produs v[10];
		//daca pe p3 il gasesc in vector
		bool gasit2 = p3(v, n);
		//p3 face medie dintre toate
		//in cazul de fata p3() nu e constructor
		float pretMediu = p3();
		//E tot operator de functie 
		Produs p4 = p3(1, 4); */

	//OPERATORUL ! (EX !X), NU MODIFICA VALOAREA LUI X
	//Y = !X comparatie fata de 0 --> y=0 
	//operatorul ! returneaza un bool, el nu face modificari

	//ii dam sensul nu are stoc --> e gol
	if(!p3)
		cout<<"nu are stoc";

	//vreau sa preiau din p3 doar denumirea
	//produsul face cast la string-ul din p3 si face cast implicit
	String denumire = p3;
	//vreau sa preiau din p3 doar stocul
	int stoc = (int)p3;

	//operatorul - acum actioneaza pe int
	//pentru ca l-am facut explicit acum - da eroare 
	int test = p3 - 10;

	//cast toString care sa fie mai bun ca friend ost <<


	return 0;
}