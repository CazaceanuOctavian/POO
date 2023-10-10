#include <iostream>

using namespace std;

class ShallowStudClass{
    private:
        string nume;
        int varsta;
    public:
        ShallowStudClass(){

        }

        ShallowStudClass(string numeVar, int varstaVar) {
            nume=numeVar;
            varsta=varstaVar;
        }

        void afiseazaInfo(){
            cout << nume << " | " << varsta << endl;
        }
    
    ~ShallowStudClass() {
        cout<<"destructorul pentru studentul " << nume << " a fost apelat" << endl;
    }
};

//=========================================//
class DeepStudClassExp {
    public:
        string nume;
        int *varsta;
    public:
        DeepStudClassExp(){
            varsta = NULL;
        }

        DeepStudClassExp(string numeVar, int *varstaVar) {
            nume=numeVar;
            varsta=varstaVar;
        }

        void afiseazaInfo(){
            cout << nume << " | " << varsta << " | " << *varsta << endl;
        }
    
    ~DeepStudClassExp() {
        cout<<"destructorul pentru studentul " << nume << " a fost apelat" << endl;
    }
};
//===========================================//

class DeepStudClass {
    public:
        string nume;
        int *varsta;
    public:
        DeepStudClass(){
            varsta = NULL;
        }

        DeepStudClass(string numeVar, int* varstaVar) {
            nume=numeVar;
            varsta = varstaVar;

        }

        void afiseazaInfo(){
            cout << nume << " | " << varsta << " | " << *varsta << endl;
        }

        //cpy constructor
        DeepStudClass(DeepStudClass &obj) {
            nume = obj.nume;
            varsta = new int;
            *varsta = *(obj.varsta);
        }
    
    ~DeepStudClass() {
        cout<<"destructorul pentru studentul " << nume << " a fost apelat" << endl;
    }
};

int main() {
    ShallowStudClass student1("bobita", 21), student2("bob", 20);
    student1.afiseazaInfo();
    cout<<endl;
    student2.afiseazaInfo();
    cout<<endl;

    //shallow copy
    student1=student2;

    cout<<"dupa shallow copy: "<< endl;

    student1.afiseazaInfo();
    cout<<endl;
    student2.afiseazaInfo();
    cout<<endl;

    cout<<"[==================================] "<<endl;

    int varsta1=21, varsta2=20;
    int* ptrVarsta1=&varsta1, *ptrVarsta2=&varsta2;

    DeepStudClassExp dpStudentExp1("bobita", ptrVarsta1), dpStudentExp2("bob", ptrVarsta2);

    dpStudentExp1.afiseazaInfo();
    cout<<endl;
    dpStudentExp2.afiseazaInfo();
    cout<<endl;

    //shallow copy
    dpStudentExp1=dpStudentExp2;
    
    cout<<"dupa shallow copy: "<< endl;

    varsta2=15;

    dpStudentExp1.afiseazaInfo();
    cout<<endl;
    dpStudentExp2.afiseazaInfo();
    cout<<endl;
    cout<<"[==================================]"<<endl;

    DeepStudClass dpStudent1("bobita", ptrVarsta1);
    DeepStudClass dpStudent2 = dpStudent1;

    dpStudent1.afiseazaInfo();
    cout<<endl;
    dpStudent2.afiseazaInfo();
    cout<<endl;

    //varsta1 = 10;


}