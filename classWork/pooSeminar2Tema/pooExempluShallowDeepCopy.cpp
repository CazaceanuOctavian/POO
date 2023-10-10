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

class DeepStudClassExp {
    public:
        string nume;
        int *varsta;
    public:
        DeepStudClassExp(){

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

int main() {
    ShallowStudClass student1("bobita", 21), student2("bob", 20);
    student1.afiseazaInfo();
    cout<<"================"<<endl;
    student2.afiseazaInfo();
    cout<<"================"<<endl;

    //shallow copy
    student1=student2;

    cout<<"dupa shallow copy: "<< endl;

    student1.afiseazaInfo();
    cout<<"================"<<endl;
    student2.afiseazaInfo();
    cout<<"================"<<endl;

    cout<<"=================================="<<endl;
    int varsta1=21, varsta2=20;
    int* ptrVarsta1=&varsta1, *ptrVarsta2=&varsta2;
    //int* ptrTest = new int;
    //ptrTest=&varsta1;

    DeepStudClassExp DpStudent1("bobita", ptrVarsta1), DpStudent2("bob", ptrVarsta2);

    DpStudent1.afiseazaInfo();
    cout<<"================"<<endl;
    DpStudent2.afiseazaInfo();
    cout<<"================"<<endl;

    //shallow copy
    DpStudent1=DpStudent2;

    varsta2=30;

    DpStudent1.afiseazaInfo();
    cout<<"================"<<endl;
    DpStudent2.afiseazaInfo();
    cout<<"================"<<endl;
}