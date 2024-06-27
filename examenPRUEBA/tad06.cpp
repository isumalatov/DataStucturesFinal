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
    insertado = A.InsertarExamen(c1, resultado);
    insertado = A.InsertarExamen(c1, resultado);

    cout << insertado << endl;
    cout << A << endl;
	return 0;
}
