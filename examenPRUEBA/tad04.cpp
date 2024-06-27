#include <iostream>
#include "tabbcalendario.h"
#include "tcalendario.h"


using namespace std;

int main(void)
{
    bool insertado;
	int resultado;

	TABBCalendario A;
    TCalendario c1(1, 1, 2000, NULL);
    TCalendario c2(2, 1, 2000, NULL);
    TCalendario c3(3, 1, 2000, NULL);
    TCalendario c4(4, 1, 2000, NULL);
    TCalendario c5(5, 1, 2000, NULL);
    TCalendario c6(6, 1, 2000, NULL);
    TCalendario c7(7, 1, 2000, NULL);
    TCalendario c8(8, 1, 2000, NULL);
    TCalendario c9(9, 1, 2000, NULL);
    insertado = A.Insertar(c5);
    insertado = A.Insertar(c2);
    insertado = A.Insertar(c7);
    insertado = A.Insertar(c1);
    insertado = A.Insertar(c3);
    insertado = A.Insertar(c6);
    insertado = A.Insertar(c9);
    insertado = A.Insertar(c8);
    insertado = A.InsertarExamen(c4,resultado);
    cout << resultado << endl;
    cout << A << endl;
	return 0;
}
