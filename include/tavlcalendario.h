#ifndef TAVLCALENDARIO_H
#define TAVLCALENDARIO_H
#include "tvectorcalendario.h"
#include "tcalendario.h"
#include "tlistacalendario.h"
#include <iostream>

using namespace std;

class TNodoAVL;

class TAVLCalendario{

    friend class TNodoAVL;
    friend ostream & operator<<(ostream &, const TAVLCalendario &);

    private:
        TNodoAVL *raiz;
        void InordenAux(TVectorCalendario &, int &) const;
        void PreordenAux(TVectorCalendario &, int &) const;
        void PostordenAux(TVectorCalendario &, int &) const;
        void Copia(const TAVLCalendario &);
        int ObtenerNodoFE() const;
        void ObtenerArbolFE();
        void RotacionII();
        void RotacionID();
        void RotacionDD();
        void RotacionDI();
        void ComprobarFE();

    public:
        TAVLCalendario();
        TAVLCalendario(const TAVLCalendario &);
        ~TAVLCalendario();
        TAVLCalendario & operator=(const TAVLCalendario &);
        bool operator==(const TAVLCalendario &) const;
        bool operator!=(const TAVLCalendario &) const;
        bool EsVacio() const;
        bool Insertar(const TCalendario &);
        bool Buscar(const TCalendario &) const;
        int Altura() const;
        int Nodos() const;
        int NodosHoja() const;
        TVectorCalendario Inorden() const;
        TVectorCalendario Preorden() const;
        TVectorCalendario Postorden() const;
        bool Borrar(const TCalendario &);
        TCalendario Raiz() const;
};


class TNodoAVL{

    friend class TAVLCalendario;

    private:
        TCalendario item;
        TAVLCalendario iz, de;
        int fe;
        void ObtenerFE();

    public:
        TNodoAVL();
        TNodoAVL(const TNodoAVL &);
        ~TNodoAVL();
        TNodoAVL & operator=(const TNodoAVL &);
};

#endif 