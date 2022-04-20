#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    //Θ(1)
	curent = c.prim;
}

TElem IteratorColectie::element() const{
    //Θ(1)
	if(valid())
        return col.e[curent];
    throw 1;
}

bool IteratorColectie::valid() const {
    //Θ(n)
	int i = col.prim;
    while(i!=0){
        if(i==curent){
            return true;
        }
        i=col.urm[i];
    }
    return false;
}

void IteratorColectie::urmator() {
    //Θ(1)
    if(valid())
        curent = col.urm[curent];
    else
        throw 1;
}

void IteratorColectie::precedent() {
    //Θ(1)
    if(valid())
        curent = col.prec[curent];
    else
        throw 1;
}

void IteratorColectie::prim() {
    //Θ(1)
	curent = col.prim;
}
