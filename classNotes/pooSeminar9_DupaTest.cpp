#include<iostream>
#include<string>
using namespace std;

//TEMA: De implementat o clasa de baza si 2 derivate. De implementat "must-ul" in clase.
//De adaugat o metoda virtuala si de exemplificat virtualizarea in main pe baza unui vector de pointeri la clasa de baza
//TEMA OPTIONALA: De virtualizat conceptul de cout.

enum Grad
{
	ASIST = 1, LECT = 2, CONF = 3, PROF = 4
};

class Angajat
{
private:
	string nume = "Anonim";
protected:
	int vechime = 0;
	int nrLocuriMunca = 0;
	string* locuriMunca = nullptr;
	float salariu = 0;

public:
	Angajat()
	{
		cout << "\nCONSTRUCTOR FARA PARAM ANGAJAT";
	}

	Angajat(string nume, int vechime, int nrLocuriMunca, string* locuriMunca, float salariu)
	{
		cout << "\nCONSTRUCTOR CU PARAM ANGAJAT";
		this->nume = nume;
		this->vechime = vechime;
		this->salariu = salariu;
		if (locuriMunca != nullptr && nrLocuriMunca != 0)
		{
			this->nrLocuriMunca = nrLocuriMunca;
			this->locuriMunca = new string[this->nrLocuriMunca];
			for (int i = 0; i < this->nrLocuriMunca; i++)
				this->locuriMunca[i] = locuriMunca[i];
		}
	}

	Angajat(const Angajat& a)
	{
		cout << "\nCONSTRUCTOR COPIERE ANGAJAT";
		this->nume = a.nume;
		this->vechime = a.vechime;
		this->salariu = a.salariu;
		if (a.locuriMunca != nullptr && a.nrLocuriMunca > 0)
		{
			this->nrLocuriMunca = a.nrLocuriMunca;
			this->locuriMunca = new string[this->nrLocuriMunca];
			for (int i = 0; i < this->nrLocuriMunca; i++)
				this->locuriMunca[i] = a.locuriMunca[i];
		}
	}

	Angajat& operator=(const Angajat& a)
	{
		cout << "\nOPERATOR = ANGAJAT";
		if (this != &a) {
			this->nume = a.nume;
			this->vechime = a.vechime;
			this->salariu = a.salariu;
			delete[] this->locuriMunca;
			this->locuriMunca = nullptr;
			if (a.locuriMunca != nullptr && a.nrLocuriMunca > 0)
			{
				this->nrLocuriMunca = a.nrLocuriMunca;
				this->locuriMunca = new string[this->nrLocuriMunca];
				for (int i = 0; i < this->nrLocuriMunca; i++)
					this->locuriMunca[i] = a.locuriMunca[i];
			}
			else
			{
				this->nrLocuriMunca = 0;
				this->locuriMunca = nullptr;
			}
		}
		return *this;
	}

	~Angajat()
	{
		cout << "\nDESTRUCTOR ANGAJAT";
		delete[] this->locuriMunca;
		this->locuriMunca = nullptr;
	}


	friend ostream& operator<<(ostream& out, const Angajat& a)
	{
		out << "\nNume: " << a.nume;
		out << "\nVechime: " << a.vechime;
		out << "\nSalariu: " << a.salariu;
		if (a.locuriMunca != nullptr)
		{
			out << "\nLocuri munca: ";
			for (int i = 0; i < a.nrLocuriMunca; i++)
				out << a.locuriMunca[i] << ", ";
		}
		return out;
	}

    //daca o clasa are o metoda virtuala toate clasele 
    //primesc o referinta la tabela de functii virtuale
    //!!obiectul e cu 4 orcteti mai mare acum!!
    //spune care e forma metodei pe care vreau sa o aplelez
    //bitii in plus pun un pointer la forma de calcul salariu specifica angajatului si profesorului
    //retine ce fost el candva
    //merge doar la pointeri
	virtual float calculSalariu()
	{
		return this->salariu;
	}
};

//Profesor IS A angajat
//angajatul e clasa de baza si prefoesorul e clasa derivata 
//Profesor vede tot mai putin zona private din Angajat
//patrat din dreptunghi
//principiul Liskov(SOLID PRINCIPAL) 
//CLASA DERIVATA SE OCUPA DE NOILE SALE ATRIBUTE SI 
//SI SA RELATIONEZE CU CLASA DE BAZA
class Profesor : public Angajat {
    Grad gradDidactic = Grad::ASIST;
    int nrOreSuplimentare = 0;
    public:
        Profesor() {
            cout<<"Apel constructor fara param profesor";
        }

        Profesor(string nume, int vechime, int nrLocuriMunca, string* locuriMunca, float salariu,
        Grad gradDidactic, int nrOreSuplimentare) : Angajat(nume, vechime, nrLocuriMunca, locuriMunca, salariu){
            cout<<"Apel constructor cu toti param profesor";
            this->gradDidactic = gradDidactic;
            this->nrLocuriMunca = nrOreSuplimentare;
        }
        //de ex: cand un angajat promoveaza in grad didactic
        //se apeleaza constructor de copiere 
        Profesor(Angajat a, Grad gradDidactic, int nrOreSuplimentare) : Angajat(a) {
            cout<<"Apel constructor cu 2 param";
            this->nrOreSuplimentare=nrOreSuplimentare;
            this->gradDidactic=gradDidactic;
        }

        Profesor(const Profesor& p) : Angajat(p) {
            cout<< "Constructor de copiere";
            this->gradDidactic = p.gradDidactic;
            this->nrOreSuplimentare = p.nrOreSuplimentare;
        }

        Profesor& operator=(const Profesor& p) {
            cout<<"operator = profesor";
            if(this != &p) {
                //upcast
                this->Angajat::operator=(p);
                this->gradDidactic = p.gradDidactic;
                this->nrOreSuplimentare = p.nrOreSuplimentare;
            }
            return *this
        }

        friend ostream& operator<<(ostream& out, const Profesor& p) {
            //angajatul devine profesor si pentru ca am pus (angajat)p
            //simialr cu mai sus, compilatorul stie sa apeleze ostreamul de la angjat
            //se va apela constuctorul si destructorul angajat
            //daca pun prin referinta nu se schimba functionalitatea
            //instream-ul se face prin REFERINTA OBLIGATORIU
            //pentru ca vreau sa vad schimbarile 
            //in>>(Angajat&)p 
            out<<(Angajat)p;
            out<<"Grad Didactic: "<<p.gradDidactic<<endl;
            out<<"Nr ore suplimentare: "<<p.nrOreSuplimentare<<endl;
            return out;
        }

        float calculSalariu() {
            float rez = Angajat::calculSalariu();
            rez += this->nrOreSuplimentare * 100;
            return rez;
        }

        ~Profesor() {
            cout<<"destructor profesor";
            //niciuna din ce aduce profesor nu e alocat dimamic asa ca nu distrug nicmic  
        }
};

//TODO --> gedstiunea centralizatia a salariatilor din ase 
//TEMA O CALSA DE BAZA IS O CLASA DERIVATA cu alocari dinamice 
//statice si const
//ostream
//istream
int main()
{
	string lista[] = { "CNCV","ASE" };
	Angajat a("Costelus", 10, 2, lista, 5000);
	cout << a;
    //se apeleaza mai intai construcotrul fara apr din clasa angajat
    //apoi se apeleaza contructorul fara param din clasa profesor
    Profesor p1;

    Profesor p2("marcel", 10, 2, lista, 5000, Grad::CONF, 15);

    Profesor p3(a, Grad::CONF, 15);

    //Constructor copiere angajat
    //Construcotr copiere profesor
    Profesor p3 = p2;

    p3=p2;

    //se foloseste tehinica de calcul din clasa de baza
    //daca iau antetul functiei si o pun in calsa profesor, 
    //va apela clasa prof
    cout<<"==========CalculSalarii============";
    cout<<"Calcul salariu Angajat: "<< a.calculSalariu();
    cout<<"Calcul salariu Profesor: "<< p2.calculSalariu();
    cout<<"==================================";

    Angajat listaA[10];
    listaA[0] = a;
    listaA[1] = p2; //apel op= din Angajat + upcast implicit si pierd functia de a calcula salariu din profesor
    float salariuTotal=0;
    for(int i=0; i<2; i++) {
        salariuTotal+=listaA[i].calculSalariu();
    }

    Angajat*  listaPointerA[10];
    listaPointerA[0] = &a;
    listaPointerA[1] = &p2; //nu se mai face operator=
    float salariuTotal=0;
    for(int i=0; i<2; i++) {
        salariuTotal+=listaPointerA[i]->calculSalariu();
    }
	return 0;
}