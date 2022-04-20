#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
    //Θ(1)
    return e1 <= e2;
}

int Colectie::aloca(){
    //Θ(1)
    int i = primLiber;
    primLiber = urm[primLiber];
    prec[primLiber]=0;
    return i;
}

void Colectie::dealoca(int i) {
    //Θ(1)
    prec[primLiber]=i;
    urm[i] = primLiber;
    primLiber = i;
    prec[primLiber]=0;

    e[primLiber]=-1;
}

void Colectie::initSpatiuLiber() {
    for(int i = 1; i<=cp-1; i++){
        urm[i] = i+1;
    }
    urm[cp]=0;
    primLiber=1;
}

Colectie::Colectie() {
    //Θ(1)
    cp=1;
    primLiber=0;

    e=new TElem[cp];
    urm=new int[cp];
    prec=new int[cp];
    lg=0;

    initSpatiuLiber();
    prim=0;
    ultim=0;
}

void Colectie::redim() {
    //Θ(n)
    TElem* enou = new TElem[2*cp];
    int* unou = new int[2*cp];
    int* pnou = new int[2*cp];

    for(int i = 1; i <= lg; i++){
        enou[i] = e[i];
        unou[i] = urm[i];
        pnou[i] = prec[i];
    }

    cp*=2;
    delete[] e;
    delete[] urm;
    delete[] prec;

    e=enou;
    urm=unou;
    prec=pnou;
    primLiber = lg+1;
    for(int i = lg+1; i<cp; i++){
        urm[i] = i+1;
        prec[i]=i-1;
    }
    urm[cp]=0;

    prec[cp]=cp-1;
    prec[primLiber]=0;
}

int Colectie::creeazaNod(TElem v) {
    //Θ(n)
    if(primLiber==0){
        redim();
    }
    int i = aloca();
    e[i]=v;
    urm[i]=0;
    prec[i]=0;
    return i;
}

int Colectie::eliminaAparitii(int nr, TElem elem){
    /*
     * Favorabil: O(1)
     * Defavorabil: O(nr*n)
     * Total: Theta(nr*n)
     *
     * Pseudocod:
     * subalgoritm eliminaAparitii(nr, elem)
     * daca nr<0 atunci
     *      arunca exceptie
     * sf_daca
     *
     * daca nr > numarAparitii(elem) atunci
     *      n <- numarAparitii(elem)
     * sf_daca
     *
     * pentru i <- 0, nr executa
     *      sterge(elem)
     * sf_pentru
     *
     * returneaza nr
     * sf_subalgoritm
     */
    if(nr < 0){
        throw std::exception();
    }

    int nrAp = nrAparitii(elem);

    if(nr > nrAp){
        nr = nrAp;
    }

    for(int i = 0; i< nr; i++){
        sterge(elem);
    }

    return nr;
}

void Colectie::adauga(TElem elem) {
    //O(n)
    int nou = creeazaNod(elem);
    urm[nou]=prim;
    prec[nou]=0;
    prec[prim]=nou;
    prim=nou;

    lg++;
}


bool Colectie::sterge(TElem elem) {
    //O(n)
    if(vida()){
        return false;
    }
    if(cauta(elem)==false){
        return false;
    }

    //aflam pozitia elementului de sters
    int p = prim;
    while (p != 0) {
        if (e[p] == elem) {
            break;
        }
        p = urm[p];
    }

    if(e[p] != elem)
        return false;

    if(p==prim){
        prim = urm[p];
        prec[prim]=0;
    }else{
        int q = prec[p];

        urm[q] = urm[p];
        prec[urm[p]] = q;
    }
    dealoca(p);
    lg--;
    return true;
}


bool Colectie::cauta(TElem elem) const {
    //O(n)
    int crt = prim;
    while (crt != 0) {
        if (e[crt] == elem) {
            return true;
        }
        if (!rel(e[crt], elem)) {
            break;
        }
        crt = urm[crt];
    }

    return false;
}


int Colectie::nrAparitii(TElem elem) const {
    //Θ(n)
    int n = 0;
    int crt = prim;
    while (crt != 0) {
        if (e[crt] == elem) {
            n++;
        }
        if (!rel(e[crt], elem)) {
            break;
        }
        crt = urm[crt];
    }
    return n;
}


int Colectie::dim() const {
    //Θ(1)
    return lg;
}


bool Colectie::vida() const {
    //Θ(1)
    return prim == 0;
}


IteratorColectie Colectie::iterator() const {
    //Θ(1)
    return IteratorColectie(*this);
}


Colectie::~Colectie() {
    //Θ(n)
    delete[] e;
    delete[] urm;
    delete[] prec;
}
