#include <iostream>

using namespace std;

void staticDublareValoriPare(int *v, int& n) {
    int aux[100];
    int k=0;
    for(int i=0; i<n; i++) {
        aux[k++] = v[i];
        if(v[i]%2==0)
            aux[k++] = v[i];
    }
    n=k;
    for(int i=0; i<n; i++)
        v[i] = aux[i];
}

bool eliminaUltimele2Valori(int*& v, int& n) {
    int nouaDim=n-2;
    if(nouaDim==0){
        n=0;
        delete[] v;
        return 0;
    }
    int *aux = new int[nouaDim];
    int k=0;
    for(int i=0; i<n-2; i++)
        aux[k++]=v[i];    
    delete[] v;
    v=aux;
    n=nouaDim;
    return 1;
}

//vector dinamic din cauza la & din int*& v
void dublareValoriPare(int*& v, int& n) {
    //p1 se calc noua dimensiune 
    int nrPare = 0;
    for(int i=0; i<n; i++)
        if(v[i]%2==0)
            nrPare++;
    int dimensiuneNoua=n+nrPare;
    //p2 se aloca zona memorie pt nou vec cu noua dimensiune
    int* aux = new int[dimensiuneNoua];
    //p3 se copiaza in noul vector ceea ce trebuie
    int k=0;
    for(int i=0; i<n; i++){
        aux[k++]=v[i];
        if(v[i]%2==0)
            aux[k++] = v[i];
    }
    //p4 se dezaloca vectorul vechi (daca nu il dezaloc am memory leaks)
    delete[] v;
    //p5 pointer vechi pointeaza spre vector nou
    v = aux;
    n= dimensiuneNoua;
}

//dublam val pare din vector
//tema: de studiat variabile constante, pointer constanti si toate comb 
//cu const pus in fata, in spate la o var. 
//static 
//+ dangling pointers
//shallow copy
//deep copy
int main() {
    int n = 5;
    //daca alocarea se face cu [], si dezalocarea se face cu []
    int *v = new int[n];
    //se aloca pe stiva NU la runtime 
    //int v2[100];
    cout<<"vector inainte stergere: ";
    for(int i=0; i<n; i++) {
        v[i]= i+10;
        cout<< v[i] << " ";
    }
    cout<<"vector dupa: ";
    eliminaUltimele2Valori(v, n);
    for(int i=0; i<n; i++)
        cout<<v[i]<<" ";
    delete[] v;
    //pointeaza spre o zm care contine deja un int initializat cu 10
    //constructorul aloca si intializeaza 
    //int* pInt = new int(10); 
    //dezaloc fara delete[]
    //delete pInt; 
    return 0;
}