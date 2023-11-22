#include <iostream>
//atribute const si statice
//metode de initializare
using namespace std;

//tema: de extins implementarea astfel incat
//sa stiu ocuparea birurilor
//adaugarea unei structuri care sa retina disponibilitatea
class Biblioteca{
    private:
        string denumire;
        const int codUnic;
        int nrEtaje;
        int* birouriStudiu;
        //bool orarZilnic[24];
        float gradIncarcare[24];
        static float gradMinimAglomerare;
    public:
        //tine loc de constructor gol pt ca vreau sa am mereu un cod unic
        //daca aveam un constructor fara parametrii as fi avut mereu acelas cod unic
        //asa ca vreau mereu as apelez Biblioteca cu cel putin un cod;
        Biblioteca(int codUnic) : codUnic(codUnic) {
            this->denumire="N/A";
            this->nrEtaje=0;
            this->birouriStudiu=nullptr;
            for(int i=0; i<24; i++)
                this->gradIncarcare[i]=0;
        }

        Biblioteca(int codUnic, string denumire, int nrEtaje, int* birouriStudiu, float gradIncarcare[24]) : codUnic(codUnic) {
            if(denumire.length()>=5)
                this->denumire=denumire;
            else
                this->denumire=nullptr;
            
            if(nrEtaje > 0 && birouriStudiu != nullptr) {
                this->nrEtaje=nrEtaje;
                this->birouriStudiu = new int[this->nrEtaje];
                for(int i=0; i<this->nrEtaje; i++)
                    this->birouriStudiu[i] = birouriStudiu[i];
            }

            //TEMA: cum adaugam validari pe atribute constante
            for(int i=0; i<24; i++) {
                if(gradIncarcare[i] >=0 && gradIncarcare[i] <= 1)
                    this->gradIncarcare[i] = gradIncarcare[i];
                else    
                    //daca nu este un procent;
                    this->gradIncarcare[i]=1;
            }
        }

        //vreau sa dezaloc ce era inainte
        //am pus &b ca sa eficientizez
        void operator=(Biblioteca &sursa) {
            delete[] this->birouriStudiu;
            this->birouriStudiu = nullptr;

            //atasez codul constructorului de copiere
             if(sursa.denumire.length()>=5)
                this->denumire=sursa.denumire;
            else
                this->denumire=nullptr;
            
            if(sursa.nrEtaje > 0 && sursa.birouriStudiu != nullptr) {
                this->nrEtaje=sursa.nrEtaje;
                this->birouriStudiu = new int[this->nrEtaje];
                for(int i=0; i<this->nrEtaje; i++)
                    this->birouriStudiu[i] = sursa.birouriStudiu[i];
            }

            //TEMA: cum adaugam validari pe atribute constante
            for(int i=0; i<24; i++) {
                if(sursa.gradIncarcare[i] >=0 && sursa.gradIncarcare[i] <= 1)
                    this->gradIncarcare[i] = sursa.gradIncarcare[i];
                else    
                    //daca nu este un procent;
                    this->gradIncarcare[i]=1;
            }
        }

        Biblioteca(const Biblioteca &sursa) : codUnic(sursa.codUnic) {
            if(sursa.denumire.length()>=5)
                this->denumire=sursa.denumire;
            else
                this->denumire=nullptr;
            
            if(sursa.nrEtaje > 0 && sursa.birouriStudiu != nullptr) {
                this->nrEtaje=sursa.nrEtaje;
                this->birouriStudiu = new int[this->nrEtaje];
                for(int i=0; i<this->nrEtaje; i++)
                    this->birouriStudiu[i] = sursa.birouriStudiu[i];
            }

            //TEMA: cum adaugam validari pe atribute constante
            for(int i=0; i<24; i++) {
                if(sursa.gradIncarcare[i] >=0 && sursa.gradIncarcare[i] <= 1)
                    this->gradIncarcare[i] = sursa.gradIncarcare[i];
                else    
                    //daca nu este un procent;
                    this->gradIncarcare[i]=1;
            }
        }

        void afisare() {
            cout<<"____________________________________"<<endl;
            cout<<"Denumire: " << this->denumire << endl;
            cout<<"Cod Unic: " << this->codUnic << endl;
            cout<<"Nr Etaje: " << this->nrEtaje << endl;
            cout<<"Birouri Studiu: ";
            if(this->birouriStudiu!=nullptr)
                for(int i=0; i<nrEtaje; i++)
                    cout<<this->birouriStudiu[i]<<" | ";
            cout<<endl;

            cout<<"Grad incarcare: ";
            for(int i=0; i<24; i++)
                cout<<gradIncarcare[i] << " | ";
            cout<<endl;
            cout<<"____________________________________"<<endl;
        }

        bool esteOcupata(int ora) {
            if(ora >=0 && ora <23)
                //daca nu am gradMInimAglomerare setat voi avea eroare de linkeditare
                if(this->gradIncarcare[ora] < Biblioteca::gradMinimAglomerare)
                    return true;
            return false;
        }

        //TEMA: utilizarea atributului static pt utilizare de coduri unice
        //      generare de coduri automate
        //      cum pot sa validez unicitatea codurilor unice
        //      (pot sa pun un cod eu sau sa mi-l genereze automat)
        //      verific daca este deja generat 
        //      ex: un licencese plate care pot sa testez daca exista;
        //o pun ca static ca sa pot sa o apelez in main cu Biblioteca::setGradMinimAglomerare(0.5);
        //TEMA: au sens validari pe constructor de copiere? --> NU pentru ca e deja valid 
        static void setGradMinimAglomerare(float gradMinimAglomerare) {
            if(gradMinimAglomerare>=0 && gradMinimAglomerare<=1)
                Biblioteca::gradMinimAglomerare= gradMinimAglomerare;
        }

        ~Biblioteca() {
            delete[] this->birouriStudiu;
            this->birouriStudiu = nullptr;
        }
};

float Biblioteca::gradMinimAglomerare = 0.6;


//obs: functiile difera prin parametrii nu prin nume
//int f1(int a);
//void f1(int b);
//o sa am eroare de ambiguitate
//int f1(int a);
//void f1(float b);
//functioneaza


//REGULIE DE SUPRANCARARE
//SE IDENTIFICA DACA OPERATORUL ESTE BINAR SAU UNAR
//SE INDENTIFICA TIPUL OPERANZILOR (in cazul meu biblioteca si biblioteca)
//DACA PRIMUL OPERAND ESTE DE TIPUL CLASEI ATUNCI SUPRAINCARCAREA SE POATE REALIZA PRINTR-O METODA A CLASEI
//forma explicita b1.operator=(b3);
//DACA PRIMUL OPERAND NU ESTE DE TIPUL CLASEI NU SE POATE IMPLEMENTA PRIN INTERMEDIUL UNEI METODE DIN CLASA
//ex: cout<<b3;
//CE RETURNEAZA OPERATORUL
//CE OBICTE/OPERANZI MODIFICAM
//de exemplu daca am b1 = b3, nu are sens sa se modifice b3

//Obs: constructorul de copiere se apeleaza doar la initializare
//daca ambele obiecte sunt intializare se apeleaza supraincararea
int main() {
    Biblioteca b1(1234);
    int birouriStudiu[] = {10, 20, 30};
    float gradIncarcare[24];
    for(int i=0; i<24; i++)
        gradIncarcare[i] = 1.0/(i+1);
    Biblioteca b2(123, "biblioteca ase", 3, birouriStudiu, gradIncarcare);
    b2.afisare();
    Biblioteca::setGradMinimAglomerare(0.3);
    //se apeleaza constructorul de copiere pt ca testBiblioteca nu exista inca
    Biblioteca testBiblioteca = b1;
}