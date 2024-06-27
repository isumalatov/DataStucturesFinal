#include <iostream>
#include "tabbcalendario.h"
#include "tlistacalendario.h"
#include "tcalendario.h"


using namespace std;

int main(void)
{
	TABBCalendario A;
	TListaCalendario L1, L2, L3;
	TVectorCalendario V(1);
    TCalendario c1(1, 1, 2000, NULL);
    A.Insertar(c1);
    V[1]=c1;
	A.Clasificar(V,L1,L2,L3);
	cout << L1 << endl;
	cout << L2 << endl;
	cout << L3 << endl;
	return 0;
}
