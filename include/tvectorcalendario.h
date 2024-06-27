#ifndef TVECTORCALENDARIO_H
#define TVECTORCALENDARIO_H

#include <iostream>
#include <string.h>
#include "tcalendario.h"

using namespace std;

class TVectorCalendario
{

    friend ostream &operator<<(ostream &, const TVectorCalendario &);

private:
    TCalendario *c;
    int tamano;
    TCalendario error;
    bool daysInMonth(int, int, int);
    void copia(const TVectorCalendario &);

public:
    TVectorCalendario();
    TVectorCalendario(int);
    TVectorCalendario(const TVectorCalendario &);
    ~TVectorCalendario();
    TVectorCalendario &operator=(const TVectorCalendario &);
    bool operator==(const TVectorCalendario &);
    bool operator!=(const TVectorCalendario &);
    TCalendario &operator[](int);
    TCalendario operator[](int) const;
    int Tamano();
    int Ocupadas();
    bool ExisteCal(const TCalendario &);
    void MostrarMensajes(int, int, int);
    bool Redimensionar(int);
};

#endif