#include <iostream>
#include "tabbcalendario.h"
#include "tlistacalendario.h"
#include "tcalendario.h"


using namespace std;

int main(void)
{
	TABBCalendario A;
	TListaCalendario L1, L2, L3;
	TVectorCalendario V(9);

    TCalendario c1(1, 1, 2000, NULL);
    TCalendario c2(2, 1, 2000, NULL);
    TCalendario c3(3, 1, 2000, NULL);
    TCalendario c4(4, 1, 2000, NULL);
    TCalendario c5(5, 1, 2000, NULL);
    TCalendario c6(6, 1, 2000, NULL);
    TCalendario c7(7, 1, 2000, NULL);
    TCalendario c8(8, 1, 2000, NULL);
    TCalendario c9(9, 1, 2000, NULL);

    V[1]=c5;
    V[2]=c2;
    V[3]=c7;
    V[4]=c1;
    V[5]=c3;
    V[6]=c6;
    V[7]=c9;
    V[8]=c4;
    V[9]=c8;

	A.Clasificar(V,L1,L2,L3);
	cout << L1 << endl;
	cout << L2 << endl;
	cout << L3 << endl;
	return 0;
}
