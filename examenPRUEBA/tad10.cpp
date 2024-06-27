#include <iostream>
#include "tabbcalendario.h"
#include "tlistacalendario.h"
#include "tcalendario.h"


using namespace std;

int main(void)
{
	TABBCalendario A;
	TListaCalendario L1, L2, L3;
	TVectorCalendario V(4);

    TCalendario c1(1, 2, 2000, NULL);
    TCalendario c2(2, 3, 2000, NULL);
    TCalendario c3(3, 4, 2000, NULL);
    TCalendario c4(4, 5, 2000, NULL);
    TCalendario c5(5, 6, 2000, NULL);
    TCalendario c6(6, 7, 2000, NULL);
    TCalendario c7(7, 7, 2000, NULL);
    TCalendario c8(8, 8, 2000, NULL);
    TCalendario c9(9, 9, 2000, NULL);

    A.Insertar(c4);
    A.Insertar(c1);
    A.Insertar(c6);
    A.Insertar(c3);
    A.Insertar(c5);

    V[1]=c9;
    V[2]=c2;
    V[3]=c7;
    V[4]=c8;

	A.Clasificar(V,L1,L2,L3);
	cout << L1 << endl;
	cout << L2 << endl;
	cout << L3 << endl;
	return 0;
}
