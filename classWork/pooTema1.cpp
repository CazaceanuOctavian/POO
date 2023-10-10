#include <iostream>

using namespace std;

//am dat referinta unui pointer ca sa ii schimb valoarea
void citireVector(int *&vecCurent, int &n) {
    scanf("%d", &n);
    vecCurent = (int*)malloc(n*sizeof(int));
    for(int i=0; i<n; i++)
        scanf("%d", &vecCurent[i]);

}

void stergeMinMax(int *&vecCurent, int &nrElemVecCurent, const int &nrIteratii) {
    for(int iterCurenta=0; iterCurenta<nrIteratii; iterCurenta++) {
        int max=vecCurent[0], min=vecCurent[0];
        for(int i=0; i<nrElemVecCurent; i++) {
            if(max<vecCurent[i])
                max=vecCurent[i];
            if(min>vecCurent[i])
                min=vecCurent[i];
        }
        
        for(int i=0; i<nrElemVecCurent; i++) {
            if(vecCurent[i]==max || vecCurent[i]==min) {
                for(int k=i; k<nrElemVecCurent; k++) 
                    vecCurent[k]=vecCurent[k+1];
            nrElemVecCurent--;
            i--;
            }
        }
    }
}

void inlocuiesteMax(int *vecCurent, const int &nrElemVecCurent) {
    int max=vecCurent[0], min=vecCurent[0];
        for(int i=0; i<nrElemVecCurent; i++) {
            if(max<vecCurent[i])
                max=vecCurent[i];
        }
        for(int i=0; i<nrElemVecCurent; i++)
            if(max==vecCurent[i])
                vecCurent[i]=0;
}

int main() {
    
    int nrElemVec, nrIteratii;
    cout << "nr elem vector: "; 
    cin >> nrElemVec; 
    cout << endl << "nr iteratii: ";
    cin >> nrIteratii;
    cout << endl;

    int *vec = (int*)malloc(nrElemVec*sizeof(int));
    //int vec[100];               
                                
    cout << "elementele vectorului: ";
    for(int i=0; i<nrElemVec; i++)
        cin >> vec[i];
    
    stergeMinMax(vec, nrElemVec, nrIteratii);
    //inlocuiesteMax(vec, nrElemVec);
    
    if(nrElemVec==0)
        cout << "in urma prelucarilor, vectorul initial a fost distrus";
    else {
        cout << "in urma prelucarilor, vectorul a devenit: ";
        for(int i=0; i<nrElemVec; i++)
            cout<< vec[i]<< " ";
    }

    //free(vec);

}
