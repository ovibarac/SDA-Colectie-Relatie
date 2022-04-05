#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    //Θ(1)
	curent = c.prim;
}

TElem IteratorColectie::element() const{
    //Θ(1)
	if(valid())
        return curent->elem();
    throw 1;
}

bool IteratorColectie::valid() const {
    //Θ(1)
	return curent != nullptr;
}

void IteratorColectie::urmator() {
    //Θ(1)
    if(valid())
        curent = curent->urmator();
    else
        throw 1;
}

void IteratorColectie::precedent() {
    //Θ(1)
    if(valid())
        curent = curent->precedent();
    else
        throw 1;
}

void IteratorColectie::prim() {
    //Θ(1)
	curent = col.prim;
}
