/*
 * 6.TAD Colecție cu elemente de tip comparabil (TElement=TComparabil)–reprezentare folosind o LDI cu elementele ordonate în raport cu relația de ordine <=.
 */

#include <iostream>

#include "TestExtins.h"
#include "TestScurt.h"
#include "Colectie.h"
#include <assert.h>

using namespace std;

void testEliminaAparitii(){
    Colectie c;
    c.adauga(5);
    c.adauga(5);
    c.adauga(5);
    c.adauga(6);
    c.adauga(0);
    c.adauga(5);
    c.adauga(10);
    c.adauga(8);

    c.eliminaAparitii(2,5);
    assert(c.nrAparitii(5)==2);
    c.eliminaAparitii(10, 6);
    assert(c.cauta(6)==false);

    try{
        c.eliminaAparitii(-1, 5);
        assert(false);
    }
    catch(std::exception){
        assert(true);
    }

}

int main() {
	testAllExtins();
	testAll();
    testEliminaAparitii();
}
