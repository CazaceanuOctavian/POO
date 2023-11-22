#include <iostream>


//daca e virtual pura nu ocupa loc
//daca are cod cum am in comparator ocupa loc in clasa, nu in obiect
//e asemanator cu o interfata de pe java 
class Comparator {
    public:
        //exista si nu exista 
        //nu exista mai mult decat exista 
        virtual bool operator()(double a, double b) = 0;
};

//clasa mai mic este derivata din comparator
class MaiMic : public Comparator {
     public:
        bool operator()(double a, double b) {
            return a<b;
        }
};

class MaiMare : public Comparator {
     public:
        bool operator()(double a, double b) {
            return a>b;
        }
};

//supraincarcare pentru vectori alocati dinamic adica a operatorului "[]" --> supraincarcare de indexare
//pentru operatorul "[]" el va returna valoarea de pe pozitia care este in paranteza
//pentru masive multidimensionale se va face supraincarcare in cascada 
//ex pentru: c[i][j][k]=123; avem 3 supraincarcari, in cascada care da referinta una la alta

//se mai foloseste si pentru extragerea bitului k dintr-o configuratie data
// bbbb cu & bitwise operator
// 0110 
// ----
// 0bb0
//daca vreau sa inserez folosesc bitwise or "|" similar cu e e sus si o sa am b11b

using namespace std;

class Vector
{
private:
	int dim;
	double* pe;
public:
    static double errPoint;

	Vector(int d = 1) : dim(d)
	{
		pe = new double[dim];
		for (int i = 0; i < dim; i++) pe[i] = 0.0;
	}
	Vector(int d, double* v) : dim(d)
	{
		pe = new double[dim];
		for (int i = 0; i < dim; i++) pe[i] = v[i];
	}

	Vector(Vector& src) : dim(src.dim)
	{
		pe = new double[dim];
		for (int i = 0; i < dim; i++) pe[i] = src.pe[i];
	}

	~Vector() { delete[] pe; }

	Vector& operator=(Vector& src)
	{
        //test de autoasignare 
        //this e operatorul din stanga
        //v1 = v2 --> this se refera la v1;
        //din perspectiva sa nu fie alocati in acelasi loc 
        //pot fi egal in continut dar nu in termeni de pointeri la element
		if (pe != src.pe)
		{
			delete[] pe; dim = src.dim;
			pe = new double[dim];
			for (int i = 0; i < dim; i++) pe[i] = src.pe[i];
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, Vector& v)
	{
		for (int i = 0; i < v.dim; i++) os << v.pe[i] << "\t";
		return os;
	}

    //se poate face template si sa mearga pentru mai multe lucruri decat double
    //se foloseste & ca sa pot si seta corect valoarea
    //daca nu as avea double & nu as putea spune v[5]=32;
    //acces si in read si in write
    double& operator[](int index) {
        if(index>=0 && index<dim)
            return pe[index];
        else {
            cerr<<"out of range"<<endl;
            return errPoint;
        }    
    }
    //Comparator& pentru ca virtualizarea se face mereu prin referinta
    void sort(Comparator& ordine) {
        for(int i=0; i<dim-1; i++)
            for(int j=i+1; j<dim; j++) 
                if(!ordine(pe[i], pe[j])) {
                    double aux = pe[i];
                    pe[i] = pe[j];
                    pe[j] = aux;
                }
    }

};

double Vector::errPoint=-1;

//tema: void operator+=(double d) care sa fie echivalentul lui PushBack (adauga un element la sfarsitul vectorului).
int main() {
    double v[]={21, -1.1, 5, 6};
    Vector v1(4, v);
    MaiMic mm;
    MaiMare MM;
    v1.sort(mm);
    v1.sort(MM);
    //fac virtualizare ca sa nu fac pointeri la functie care arata 
    //bool (*pf)(double, double)
}