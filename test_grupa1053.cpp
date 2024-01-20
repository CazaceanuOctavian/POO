#include <iostream>
#include <string.h>

using namespace std;

class AgendaTelefon {
    private:
        const int id;
        char* consumator;
        int nrApeluri;
        int* durataConvorbirii;
        static int costMinut;
        //----------------------

        char* provider;
        bool esteFix;
    public:
        AgendaTelefon(int id) : id(id) {
            this->consumator=nullptr;
            this->nrApeluri=0;
            this->durataConvorbirii=nullptr;
            this->provider=nullptr;
            this->esteFix=false;
        }

        //constructor cu toti param --> nu este necesar pentru cerinta dar ajuta la debugging si este template pentru restul constructorilor
        AgendaTelefon(int id, char* consumator, int nrApeluri, int* durataConvorbirii, char* provider, bool esteFix) : id(id) {
            if(consumator!=nullptr) {
                this->consumator=new char[strlen(consumator) + 1];
                strcpy(this->consumator, consumator);
            }
            else {
                this->consumator=nullptr;
            }
            if(nrApeluri>0)
                this->nrApeluri=nrApeluri;
            else
                this->nrApeluri=0;
            if(this->nrApeluri>0 && durataConvorbirii!=nullptr) {
                this->durataConvorbirii= new int[this->nrApeluri];
                for(int i=0; i<this->nrApeluri; i++)
                    this->durataConvorbirii[i] = durataConvorbirii[i];
            }
            if(provider!=nullptr) {
                this->provider = new char[strlen(provider) + 1];
                strcpy(this->provider, provider);
            }
            else {
                this->provider=nullptr;
            }
            this->esteFix=esteFix;
        }

        AgendaTelefon (AgendaTelefon& sursa) : id(sursa.id){
            cout<<"COPY CONSTRUCTOR"<<endl;
            if(sursa.consumator!=nullptr) {
                this->consumator=new char[strlen(sursa.consumator) + 1];
                strcpy(this->consumator, sursa.consumator);
            }
            else {
                this->consumator=nullptr;
            }
            if(sursa.nrApeluri>0)
                this->nrApeluri=sursa.nrApeluri;
            else
                this->nrApeluri=0;
            if(this->nrApeluri>0 && sursa.durataConvorbirii!=nullptr) {
                this->durataConvorbirii= new int[this->nrApeluri];
                for(int i=0; i<this->nrApeluri; i++)
                    this->durataConvorbirii[i] = sursa.durataConvorbirii[i];
            }
            if(sursa.provider!=nullptr) {
                this->provider = new char[strlen(sursa.provider) + 1];
                strcpy(this->provider, sursa.provider);
            }
            else {
                this->provider=nullptr;
            }
            this->esteFix=sursa.esteFix;
        }

        AgendaTelefon& operator=(AgendaTelefon& sursa) {
            if(this != &sursa) {
                cout<<"OPERATOR ="<<endl;
                delete[] this->durataConvorbirii;
                this->durataConvorbirii=nullptr;

                delete[] this->provider;
                this->provider=nullptr;

                delete[] this->consumator;
                this->consumator=nullptr;

                if(sursa.consumator!=nullptr) {
                    this->consumator=new char[strlen(sursa.consumator) + 1];
                    strcpy(this->consumator, sursa.consumator);
                }
                else {
                    this->consumator=nullptr;
                }
                if(sursa.nrApeluri>0)
                    this->nrApeluri=sursa.nrApeluri;
                else
                    this->nrApeluri=0;
                if(this->nrApeluri>0 && sursa.durataConvorbirii!=nullptr) {
                    this->durataConvorbirii= new int[this->nrApeluri];
                    for(int i=0; i<this->nrApeluri; i++)
                        this->durataConvorbirii[i] = sursa.durataConvorbirii[i];
                }
                if(sursa.provider!=nullptr) {
                    this->provider = new char[strlen(sursa.provider) + 1];
                    strcpy(this->provider, sursa.provider);
                }
                else {
                    this->provider=nullptr;
                }
                this->esteFix=sursa.esteFix;
                }
                return *this;
        }
        //postIncrementare;
        AgendaTelefon operator++(int) {
            AgendaTelefon copie = *this;
            for(int i=0; i<this->nrApeluri; i++)
                this->durataConvorbirii[i]++;

            return copie;
        }

        AgendaTelefon& operator+(int minuteNoi) {
            int* durataConvorbiriiNou = new int[this->nrApeluri+1];
            for(int i=0; i<this->nrApeluri + 1; i++)
                durataConvorbiriiNou[i] = this->durataConvorbirii[i];
            durataConvorbiriiNou[this->nrApeluri] = minuteNoi;

            delete[] this->durataConvorbirii;
            this->durataConvorbirii=nullptr;

            this->nrApeluri++;
            this->durataConvorbirii= new int[this->nrApeluri];
            for(int i=0; i<this->nrApeluri; i++)
                this->durataConvorbirii[i] = durataConvorbiriiNou[i];
            
            delete[] durataConvorbiriiNou;
            durataConvorbiriiNou=nullptr;

            return *this;
        }

        AgendaTelefon& operator-(int minuteNoi) {
            int* durataConvorbiriiNou = new int[this->nrApeluri+1];
            for(int i=0; i<this->nrApeluri + 1; i++)
                durataConvorbiriiNou[i] = this->durataConvorbirii[i];
            durataConvorbiriiNou[this->nrApeluri] = minuteNoi*-1;

            delete[] this->durataConvorbirii;
            this->durataConvorbirii=nullptr;

            this->nrApeluri++;
            this->durataConvorbirii= new int[this->nrApeluri];
            for(int i=0; i<this->nrApeluri; i++)
                this->durataConvorbirii[i] = durataConvorbiriiNou[i];
            
            delete[] durataConvorbiriiNou;
            durataConvorbiriiNou=nullptr;

            return *this;
        }

        bool operator==(AgendaTelefon& sursa) {
            if(strcmp(this->consumator, sursa.consumator)!=0 || strcmp(this->provider, sursa.provider)!=0 || this->nrApeluri!=sursa.nrApeluri || this->esteFix!=sursa.esteFix) {
                return 0;
            }
            else {
                for(int i=0; i<this->nrApeluri; i++)
                    if(this->durataConvorbirii[i] != sursa.durataConvorbirii[i])   
                        return 0; 
                return 1;
            }
        }

        friend ostream& operator<<(ostream& ost, AgendaTelefon& sursa) {
            cout<<"==================================="<<endl;
            cout<<"id consumator: "<<sursa.id<<endl;
            if(sursa.consumator!=nullptr)
                cout<<"consumator: "<<sursa.consumator<<endl;
            else
                cout<<"consumatorul nu a fost introdus"<<endl;
            if(sursa.provider!=nullptr)
                cout<<"provider: "<<sursa.provider<<endl;
            cout<<"numar apeluri: "<<sursa.nrApeluri<<endl;
            if(sursa.nrApeluri>0 && sursa.durataConvorbirii!=nullptr) {
                cout<<"cu urmatoarele minute: ";
                for(int i=0; i<sursa.nrApeluri; i++)
                    cout<<sursa.durataConvorbirii[i]<<" | ";
                cout<<endl;
            } 
            if(sursa.esteFix)
                cout<<"este telefon fix"<<endl;
            else
                cout<<"nu este telefon fix"<<endl;
            cout<<"==================================="<<endl;
            return ost;
        }

        friend istream& operator>>(istream& in, AgendaTelefon& sursa) {
            delete[] sursa.durataConvorbirii;
            sursa.durataConvorbirii=nullptr;

            delete[] sursa.provider;
            sursa.provider=nullptr;

            delete[] sursa.consumator;
            sursa.consumator=nullptr;

            string buffer;

            cout<<"denumirea consumatorului: ";
            in>>buffer;
            if(!buffer.empty()) {
                sursa.consumator = new char[buffer.size() + 1];
                strcpy(sursa.consumator, buffer.data());
            }
            else {
                sursa.consumator = new char[strlen("ANON") + 1];
                strcpy(sursa.consumator, "ANON");
            }
            cout<<"denumirea providerului: ";
            in>>buffer;
            if(!buffer.empty()) {
                sursa.provider = new char[buffer.size() + 1];
                strcpy(sursa.provider, buffer.data());
            }
            else {
                sursa.provider = new char[strlen("ANON") + 1];
                strcpy(sursa.consumator, "ANON");
            }
            cout<<"numarul de apeluri: ";
            in>>sursa.nrApeluri;
            if(sursa.nrApeluri<=0)
                sursa.nrApeluri=0;
            
            if(sursa.nrApeluri>0) {
                cout<<"apelurile avand minutele: ";
                sursa.durataConvorbirii = new int[sursa.nrApeluri];
                for(int i=0; i<sursa.nrApeluri; i++)
                in>>sursa.durataConvorbirii[i];
            }
            cout<<"este telefon fix?(1/0)";
            in>>sursa.esteFix;

            return in;
        }

        int calculTotalMinute() {
            int nrTotalMin=0;
            for(int i=0; i<this->nrApeluri; i++) {
                if(this->durataConvorbirii[i]<0) {
                    this->durataConvorbirii[i]*=-1;
                    nrTotalMin+=this->durataConvorbirii[i];
                    //pentru a nu modifica vectorul initial;
                    this->durataConvorbirii[i]*=-1;
                }
                else
                    nrTotalMin+=this->durataConvorbirii[i];
            }
            return nrTotalMin;
        }

        int getCostTotal(int minuteDisponibile) {
            int totalMinuteInitiate=0;
            if(this->durataConvorbirii !=nullptr && this->nrApeluri>0) {
                for(int i=0; i<this->nrApeluri; i++) {
                    if(this->durataConvorbirii[i]>0)
                        totalMinuteInitiate+=durataConvorbirii[i];
                }
                if(totalMinuteInitiate>minuteDisponibile)
                    return (totalMinuteInitiate-minuteDisponibile)*AgendaTelefon::costMinut;
            }
            return -1;
        }

        void setProvider(const char* provider) {
            if(provider!=nullptr) {
                delete[] this->provider;
                this->provider=nullptr;

                this->provider=new char[strlen(provider) + 1];
                strcpy(this->provider, provider);
                } 
                else {
                cerr<<"provider invalid"<<endl;
            }
        }

        char* getProvider() {
            return this->provider;
        }

        void setEsteFix(const bool esteFix) {
            this->esteFix=esteFix;
        }

        bool getEsteFix() {
            return this->esteFix;
        }

        ~AgendaTelefon() {
            delete[] this->durataConvorbirii;
            this->durataConvorbirii=nullptr;

            delete[] this->provider;
            this->provider=nullptr;

            delete[] this->consumator;
            this->consumator=nullptr;
        }

};

int AgendaTelefon::costMinut = 2;

int main() {
    char* cons = new char[strlen("ana") + 1];
    strcpy(cons, "ana");
    char* provider = new char[strlen("vodafone") + 1];
    strcpy(provider, "vodafone");
    int* timpApeluri = new int[4];
    timpApeluri[0] = 15;
    timpApeluri[1] = -32;
    timpApeluri[2] = 40;
    timpApeluri[3] = -5;

    AgendaTelefon a1(1, cons, 4, timpApeluri, provider, false);
    cout<<a1;

    AgendaTelefon a2 = a1;
    cout<<a2;

    AgendaTelefon a3(2);
    a3 = a1;
    cout<<a3;

    //--------------------
    cout<<"apel set/get provider: "<<endl;
    a1.setProvider("orange");
    //cout<<a1;
    char* providerNou = a1.getProvider();
    cout<<providerNou<<endl;

    cout<<"apel set/get bool: "<<endl; 
    //cout<<a1;
    a1.setEsteFix(true);   
    bool test = a1.getEsteFix();
    cout<<test<<endl;

    cout<<"calcul total minute: "<<endl;
    cout<<a1.calculTotalMinute()<<endl;

    cout<<"calcul pret minute depasite: "<<endl;
    cout<<a1.getCostTotal(14)<<endl;

    cout<<"operator++: "<<endl;
    a1++;
    cout<<a1;

    cout<<"operator+ "<<endl;
    a2 = a2 + 17;
    cout<<a2;

    cout<<"operator- "<<endl;
    a2 = a2 - 13;
    cout<<a2;

     AgendaTelefon a10(15, cons, 4, timpApeluri, provider, false);
     AgendaTelefon a11=a10;
     a11.setEsteFix(true);
     

     if(a11==a10)
        cout<<"OPERATOR == TRUE"<<endl;
    else
        cout<<"OPERATOR == FALSE"<<endl;

    int* timpApeluriNoi = new int[4];
    timpApeluriNoi[0] = 15;
    timpApeluriNoi[1] = -32;
    //diferit de 40 din timpApeluri
    timpApeluriNoi[2] = 41;
    timpApeluriNoi[3] = -5;

    AgendaTelefon a12(16, cons, 4, timpApeluriNoi, provider, false);

     if(a10==a12)
        cout<<"OPERATOR == TRUE"<<endl;
    else
        cout<<"OPERATOR == FALSE"<<endl;

     
    AgendaTelefon a20(5);
    cin>>a20;
    cout<<a20;
    
}