#include <iostream>

using namespace std;

int* testFunc() {
    int var=10;
    return &var;
}

int main() { 
    int* ptr=testFunc();
    //cout << ptr << endl;

    //===================//

    int nrElem;
    cin >> nrElem;
    int* vec = (int*)malloc(sizeof(int)*nrElem);
    
    for(int i=0; i<nrElem; i++)
        vec[i]=i;

    for(int i=0; i<nrElem; i++) {
        cout << vec[i] << "  |  " << &vec[i] << endl;
    }

    cout<<"======================" << endl;

    free(vec);
    cout << *vec  << "  |  "<< vec << endl;
    vec = NULL;
    getchar();
}