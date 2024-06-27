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
    insertado = A.Insertar(c2);
    insertado = A.InsertarExamen(c1,resultado);
    cout << resultado << endl;
    cout << A << endl;
	return 0;
}
