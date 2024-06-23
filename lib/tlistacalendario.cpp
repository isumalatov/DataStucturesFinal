#include "tlistacalendario.h"

TNodoCalendario::TNodoCalendario()
{
    siguiente = NULL;
}

TNodoCalendario::TNodoCalendario(const TNodoCalendario &nodo)
{
    this->c = nodo.c;
    this->siguiente = nodo.siguiente;
}

TNodoCalendario::~TNodoCalendario()
{
    this->c.~TCalendario();

    if (siguiente != NULL)
    {
        siguiente = NULL;
    }
}

TNodoCalendario &TNodoCalendario::operator=(const TNodoCalendario &nodo)
{
    if (this != &nodo)
    {

        (*this).~TNodoCalendario();
        this->c = nodo.c;
        this->siguiente = nodo.siguiente;
    }

    return *this;
}

TListaPos::TListaPos()
{
    pos = NULL;
}

TListaPos::TListaPos(const TListaPos &listaPos)
{
    this->pos = listaPos.pos;
}

TListaPos::~TListaPos()
{
    if (pos != NULL)
    {
        pos = NULL;
    }
}

TListaPos &TListaPos::operator=(const TListaPos &listaPos)
{
    if (this != &listaPos)
    {
        (*this).~TListaPos();
        this->pos = listaPos.pos;
    }

    return *this;
}

bool TListaPos::operator==(const TListaPos &listaPos) const
{
    return (this->pos == listaPos.pos);
}

bool TListaPos::operator!=(const TListaPos &listaPos) const
{
    return (this->pos != listaPos.pos);
}

TListaPos TListaPos::Siguiente() const
{
    TListaPos listaPos;

    if (this->pos->siguiente != NULL)
    {
        listaPos.pos = this->pos->siguiente;
    }

    return listaPos;
}

bool TListaPos::EsVacia() const
{
    return (this->pos == NULL);
}

TListaCalendario::TListaCalendario()
{
    primero = NULL;
}

TListaCalendario::TListaCalendario(const TListaCalendario &lista)
{
    this->primero = NULL;
    for (TListaPos i = lista.Primera(); !i.EsVacia(); i = i.Siguiente())
    {
        Insertar(i.pos->c);
    }
}

TListaCalendario::~TListaCalendario()
{
    TNodoCalendario *actual = this->primero;

    while (actual != NULL)
    {
        actual = this->primero->siguiente;
        delete this->primero;
        this->primero = actual;
    }
}

TListaCalendario &TListaCalendario::operator=(const TListaCalendario &lista)
{
    if (this != &lista)
    {
        (*this).~TListaCalendario();
        for (TListaPos i = lista.Primera(); !i.EsVacia(); i = i.Siguiente())
        {
            Insertar(i.pos->c);
        }
    }
    else
    {
        return *this;
    }

    return *this;
}

bool TListaCalendario::operator==(TListaCalendario &lista)
{
    if (Longitud() == lista.Longitud())
    {
        TListaPos pos1 = Primera();
        TListaPos pos2 = lista.Primera();
        int i = 1;
        while (i < Longitud())
        {
            if (Obtener(pos1) != lista.Obtener(pos2))
            {
                return false;
            }
            pos1 = pos1.Siguiente();
            pos2 = pos2.Siguiente();
            i++;
        }
    }
    else
    {
        return false;
    }
    return true;
}

TListaCalendario TListaCalendario::operator+(TListaCalendario &lista)
{
    TListaCalendario suma;
    TListaPos pos = Primera();

    int i = 0;
    while (i < Longitud())
    {
        suma.Insertar(Obtener(pos));
        pos = pos.Siguiente();
        i++;
    }

    pos = lista.Primera();
    i = 0;
    while (i < lista.Longitud())
    {
        suma.Insertar(lista.Obtener(pos));
        pos = pos.Siguiente();
        i++;
    }

    return suma;
}

TListaCalendario TListaCalendario::operator-(TListaCalendario &lista)
{
    TListaCalendario resta;
    TListaPos pos = Primera();

    int i = 0;
    while (i < Longitud())
    {
        if (!lista.Buscar(Obtener(pos)))
        {
            resta.Insertar(Obtener(pos));
        }
        pos = pos.Siguiente();
        i++;
    }

    return resta;
}

bool TListaCalendario::Insertar(const TCalendario &cal)
{
    TNodoCalendario *nodoInsertar = new TNodoCalendario();
    nodoInsertar->c = cal;

    if (EsVacia())
    {
        this->primero = nodoInsertar;
        return true;
    }

    if (Buscar(cal))
    {
        return false;
    }
    else
    {
        if (nodoInsertar->c < primero->c)
        {
            nodoInsertar->siguiente = primero;
            primero = nodoInsertar;
            return true;
        }
        TNodoCalendario *aux = new TNodoCalendario();
        aux = primero;
        while (aux->siguiente != NULL)
        {

            if (nodoInsertar->c < aux->siguiente->c)
            {
                nodoInsertar->siguiente = aux->siguiente;
                aux->siguiente = nodoInsertar;
                return true;
            }
            aux = aux->siguiente;
        }

        aux->siguiente = nodoInsertar;
        return true;
    }
}

bool TListaCalendario::Borrar(TCalendario &cal)
{
    if (Buscar(cal))
    {
        TNodoCalendario *aux = new TNodoCalendario();
        aux = primero;

        if (aux->c == cal)
        {
            primero = aux->siguiente;
            aux->~TNodoCalendario();
            return true;
        }

        TNodoCalendario *nodoBorrar = new TNodoCalendario();

        int i = 0;
        while (i < Longitud())
        {

            if (aux->siguiente->c == cal)
            {
                nodoBorrar = aux->siguiente;
                aux->siguiente = aux->siguiente->siguiente;
                nodoBorrar->~TNodoCalendario();
                return true;
            }

            aux = aux->siguiente;
            i++;
        }
    }
    else
    {
        return false;
    }

    return false;
}

bool TListaCalendario::Borrar(const TListaPos &pos)
{
    if (pos.EsVacia())
    {
        return false;
    }
    else
    {
        TListaPos primer = Primera();

        if (primer == pos)
        {
            primero = primero->siguiente;
            primer.pos->~TNodoCalendario();
            primer.~TListaPos();
            return true;
        }

        for (TListaPos i = Primera(); !i.EsVacia(); i = i.Siguiente())
        {
            if (i.Siguiente() == Ultima() && i.Siguiente() == pos)
            {
                i.pos->siguiente = NULL;
                i.Siguiente().~TListaPos();
                return true;
            }
            else if (i.Siguiente() == pos)
            {
                i.pos->siguiente = i.pos->siguiente->siguiente;
                i.Siguiente().~TListaPos();
                return true;
            }
        }
    }

    return false;
}

bool TListaCalendario::Borrar(int dia, int mes, int anyo)
{
    TNodoCalendario *aux = new TNodoCalendario();
    aux = primero;

    TCalendario calendarioBorrar;

    bool borrar = false;
    bool borrado = false;

    int longitud = Longitud();
    int i = 0;
    while (i < longitud)
    {
        borrar = false;

        if (aux->c.Anyo() < anyo)
        {
            borrar = true;
        }
        else if (aux->c.Anyo() == anyo && aux->c.Mes() < mes)
        {
            borrar = true;
        }
        else if (aux->c.Anyo() == anyo && aux->c.Mes() == mes && aux->c.Dia() < dia)
        {
            borrar = true;
        }
        else
        {
            break;
        }

        if (borrar)
        {
            calendarioBorrar = aux->c;
            aux = aux->siguiente;
            if (Borrar(calendarioBorrar))
            {
                borrado = true;
            }
        }
        i++;
    }

    return borrado;
}

TCalendario TListaCalendario::Obtener(const TListaPos &pos) const
{
    TCalendario cal;

    if (pos.EsVacia())
    {
        return cal;
    }
    else
    {
        return pos.pos->c;
    }
}

bool TListaCalendario::Buscar(const TCalendario &cal) const
{
    for (TListaPos i = Primera(); !i.EsVacia(); i = i.Siguiente())
    {
        if (Obtener(i) == cal)
        {
            return true;
        }
    }

    return false;
}

int TListaCalendario::Longitud() const
{
    TNodoCalendario *aux = primero;
    int longitud = 0;

    while (aux != NULL)
    {
        aux = aux->siguiente;
        longitud++;
    }

    return longitud;
}

bool TListaCalendario::EsVacia() const
{
    return (this->primero == NULL);
}

TListaPos TListaCalendario::Primera() const
{
    TListaPos primero;

    if (EsVacia())
    {
        return primero;
    }
    else
    {
        primero.pos = this->primero;
        return primero;
    }
}

TListaPos TListaCalendario::Ultima() const
{
    TListaPos ultimo = Primera();

    int i = 1;
    while (i < Longitud())
    {
        ultimo = ultimo.Siguiente();
        i++;
    }
    return ultimo;
}

TListaCalendario TListaCalendario::SumarSubl(int l1_i, int l1_d, TListaCalendario &lista, int l2_i, int l2_d)
{
    TListaCalendario l1;
    TListaCalendario l2;
    TListaCalendario resultado;

    l1 = ExtraerRango(l1_i, l1_d);
    l2 = lista.ExtraerRango(l2_i, l2_d);

    resultado = l1 + l2;

    return resultado;
}

TListaCalendario TListaCalendario::ExtraerRango(int limite_Izq, int limite_Der)
{
    TListaCalendario resultado;

    if (limite_Izq > limite_Der)
    {
        return resultado;
    }

    if (limite_Izq <= 0)
    {
        limite_Izq = 1;
    }

    if (limite_Der > Longitud())
    {
        limite_Der = Longitud();
    }

    TNodoCalendario *cal = primero;
    TNodoCalendario *nodoExtraer;

    for (int i = 1; i < limite_Izq; i++)
    {
        cal = cal->siguiente;
    }

    for (int i = limite_Izq; i <= limite_Der; i++)
    {
        resultado.Insertar(cal->c);
        nodoExtraer = cal;
        cal = cal->siguiente;
        Borrar(nodoExtraer->c);
    }

    return resultado;
}

ostream &operator<<(ostream &s, const TListaCalendario &lista)
{
    s << "<";
    for (TListaPos i = lista.Primera(); !i.EsVacia(); i = i.Siguiente())
    {
        if (i == lista.Ultima())
        {
            s << lista.Obtener(i);
        }
        else
        {
            s << lista.Obtener(i) << " ";
        }
    }
    s << ">";

    return s;
}
