#ifndef TCALENDARIO_H
#define TCALENDARIO_H
#include <iostream>
#include <string.h>

using namespace std;

class TCalendario{

    friend ostream & operator <<(ostream &, const TCalendario &);

    private:
        int dia, mes, anyo;
        char *mensaje;
        void Copia(const TCalendario &);
        bool ComprobarFecha(int, int, int);


    public:
        TCalendario();
        TCalendario(int, int, int, char *);
        TCalendario(const TCalendario &);
        ~TCalendario();
        TCalendario & operator=(const TCalendario &);
        TCalendario operator+(int);
        TCalendario operator-(int);
        TCalendario operator++(int);
        TCalendario & operator++();
        TCalendario operator--(int);
        TCalendario & operator--();
        bool ModFecha(int, int, int);
        bool ModMensaje(char *);
        bool operator ==(const TCalendario &);
        bool operator !=(const TCalendario &);
        bool operator >(const TCalendario &);
        bool operator <(const TCalendario &);
        bool EsVacio();
        int Dia() const;
        int Mes() const;
        int Anyo() const;
        char *Mensaje() const;
};

#endif 