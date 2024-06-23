#ifndef TVECTORCALENDARIO_H
#define TVECTORCALENDARIO_H
#include "tcalendario.h"
#include <iostream>
#include <string.h>

using namespace std;

class TVectorCalendario{

    friend ostream & operator <<(ostream &, const TVectorCalendario &);

    private:
        TCalendario *c;
        int tamano;
        TCalendario error;
        void Copia(const TVectorCalendario &);
        bool ComprobarFecha(int, int, int);

    public:
        TVectorCalendario();
        TVectorCalendario(int);
        TVectorCalendario(const TVectorCalendario &);
        ~TVectorCalendario();
        TVectorCalendario & operator=(const TVectorCalendario &);
        bool operator==(const TVectorCalendario &);
        bool operator!=(const TVectorCalendario &);
        TCalendario & operator[](int);
        TCalendario operator[](int) const;
        int Tamano();
        int Ocupadas();
        bool ExisteCal(const TCalendario &);
        void MostrarMensajes(int, int, int);
        bool Redimensionar(int);
};

#endif 