#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

TElem Node::elem() {
    //Θ(1)
    return this->val;
}

PNod Node::urmator() {
    //Θ(1)
    return this->urm;
}

PNod Node::precedent() {
    //Θ(1)
    return this->prec;
}

Node::Node(TElem val, PNod precedent,PNod urmator) {
    //Θ(1)
    this->val = val;
    this->urm = urmator;
    this->prec = precedent;
}


bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

Colectie::Colectie() {
	this->prim = nullptr;
}

void Colectie::adauga(TElem e) {
    //O(n)
    PNod crt = prim;
    if(rel(e, crt->elem())){
        //daca e primul nod
        PNod nou = new Node(e, nullptr, crt);
        crt->prec=nou;
        prim = nou;
    }else{
        //cauta pozitia unde sa adauge
        while(crt->urmator() != nullptr && rel(crt->urmator()->elem(), e)){
            crt = crt->urmator();
        }
        PNod nou = new Node(e, crt, crt->urmator());
        crt->urm = nou;
        if(crt->urmator() != nullptr){
            //daca nu e ultimul seteaza si precedentul urmatorului
            nou->urm->prec = nou;
        }
    }
}


bool Colectie::sterge(TElem e) {
    //O(n)
    PNod crt = prim;
    while(crt != nullptr){
        if(crt->elem() == e){
            crt->prec->urm = crt->urmator();
            crt->urm->prec = crt->precedent();
            return true;
        }
        crt = crt->urmator();
    }

    return false;
}


bool Colectie::cauta(TElem elem) const {
    //O(n)
    PNod crt = prim;
    while(crt != nullptr){
        if(crt->elem() == elem){
            return true;
        }
        crt = crt->urmator();
    }

    return false;
}


int Colectie::nrAparitii(TElem elem) const {
    //Θ(n)
    int n = 0;
    PNod crt = prim;
    while(crt != nullptr){
        if(crt->elem() == elem){
            n++;

        }
        if(!rel(crt->elem(), elem)){
            break;
        }
        crt = crt->urmator();
    }

    return n;
}



int Colectie::dim() const {
    //Θ(n)
	int n = 0;

    PNod crt = prim;
    while(crt != nullptr){
        n++;
        crt = crt->urmator();
    }

    return n;
}


bool Colectie::vida() const {
    //Θ(1)
	return prim == nullptr;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
    while (prim != nullptr) {
        PNod p = prim;
        prim = prim->urm;
        delete p;
    }
}
