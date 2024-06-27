#include "tlistacalendario.h"

TNodoCalendario::TNodoCalendario()
{
    siguiente = NULL;
}

TNodoCalendario::TNodoCalendario(const TNodoCalendario &n)
{
    c = n.c;
    siguiente = n.siguiente;
}

TNodoCalendario::~TNodoCalendario()
{
    c.~TCalendario();
    siguiente = NULL;
}

TNodoCalendario &TNodoCalendario::operator=(const TNodoCalendario &n)
{
    if (this != &n)
    {
        (*this).~TNodoCalendario();
        c = n.c;
        siguiente = n.siguiente;
    }
    return *this;
}

TListaPos::TListaPos()
{
    pos = NULL;
}

TListaPos::TListaPos(const TListaPos &l)
{
    this->pos = l.pos;
}

TListaPos::~TListaPos()
{
    pos = NULL;
}

TListaPos &TListaPos::operator=(const TListaPos &l)
{
    if (this != &l)
    {
        (*this).~TListaPos();
        pos = l.pos;
    }

    return *this;
}

bool TListaPos::operator==(const TListaPos &l) const
{
    return (pos == l.pos);
}

bool TListaPos::operator!=(const TListaPos &listaPos) const
{
    return (this->pos != listaPos.pos);
}

TListaPos TListaPos::Siguiente() const
{
    TListaPos l;

    if (pos->siguiente != NULL)
    {
        l.pos = pos->siguiente;
    }

    return l;
}

bool TListaPos::EsVacia() const
{
    return (pos == NULL);
}

TListaCalendario::TListaCalendario()
{
    primero = NULL;
}

TListaCalendario::TListaCalendario(const TListaCalendario &l)
{
    primero = NULL;
    for (TListaPos i = l.Primera(); !i.EsVacia(); i = i.Siguiente())
    {
        Insertar(i.pos->c);
    }
}

TListaCalendario::~TListaCalendario()
{
    TNodoCalendario *n = primero;

    while (n != NULL)
    {
        n = primero->siguiente;
        delete primero;
        primero = n;
    }
}

TListaCalendario &TListaCalendario::operator=(const TListaCalendario &l)
{
    if (this != &l)
    {
        (*this).~TListaCalendario();
        for (TListaPos i = l.Primera(); !i.EsVacia(); i = i.Siguiente())
        {
            Insertar(i.pos->c);
        }
    }

    return *this;
}

bool TListaCalendario::operator==(TListaCalendario &l)
{
    if (Longitud() == l.Longitud())
    {
        TListaPos n = Primera();
        TListaPos m = l.Primera();
        int i = 1;
        while (i < Longitud())
        {
            if (Obtener(n) != l.Obtener(m))
            {
                return false;
            }
            n = n.Siguiente();
            m = m.Siguiente();
            i++;
        }
    }
    else
    {
        return false;
    }
    return true;
}

TListaCalendario TListaCalendario::operator+(TListaCalendario &l)
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

    pos = l.Primera();
    i = 0;
    while (i < l.Longitud())
    {
        suma.Insertar(l.Obtener(pos));
        pos = pos.Siguiente();
        i++;
    }

    return suma;
}

TListaCalendario TListaCalendario::operator-(TListaCalendario &l)
{
    TListaCalendario resta;
    TListaPos pos = Primera();

    int i = 0;
    while (i < Longitud())
    {
        if (!l.Buscar(Obtener(pos)))
        {
            resta.Insertar(Obtener(pos));
        }
        pos = pos.Siguiente();
        i++;
    }

    return resta;
}

bool TListaCalendario::Insertar(const TCalendario &calendario)
{
    TNodoCalendario *nodoInsertar = new TNodoCalendario();
    nodoInsertar->c = calendario;

    if (EsVacia())
    {
        this->primero = nodoInsertar;
        return true;
    }

    if (Buscar(calendario))
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

bool TListaCalendario::Borrar(TCalendario &calendario)
{
    if (Buscar(calendario))
    {
        TNodoCalendario *aux = new TNodoCalendario();
        aux = primero;

        if (aux->c == calendario)
        {
            primero = aux->siguiente;
            aux->~TNodoCalendario();
            return true;
        }

        TNodoCalendario *nodoBorrar = new TNodoCalendario();

        int i = 0;
        while (i < Longitud())
        {

            if (aux->siguiente->c == calendario)
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
    TCalendario calendario;

    if (pos.EsVacia())
    {
        return calendario;
    }
    else
    {
        return pos.pos->c;
    }
}

bool TListaCalendario::Buscar(const TCalendario &calendario) const
{
    for (TListaPos i = Primera(); !i.EsVacia(); i = i.Siguiente())
    {
        if (Obtener(i) == calendario)
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
    return (primero == NULL);
}

TListaPos TListaCalendario::Primera() const
{
    TListaPos primero;

    if (!EsVacia())
    {
        primero.pos = this->primero;
        return primero;
    }
    else
    {
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

TListaCalendario TListaCalendario::SumarSubl(int i, int j, TListaCalendario &lista, int k, int m)
{
    TListaCalendario l1, l2, l3;

    l1 = ExtraerRango(i, j);
    l2 = lista.ExtraerRango(k, m);

    l3 = l1 + l2;

    return l3;
}

TListaCalendario TListaCalendario::ExtraerRango(int l1, int l2)
{
    TListaCalendario l3;

    if (l1 > l2)
    {
        return l3;
    }

    if (l1 <= 0)
    {
        l1 = 1;
    }

    if (l2 > Longitud())
    {
        l2 = Longitud();
    }

    TNodoCalendario *cal = primero;
    TNodoCalendario *nodoExtraer;

    for (int i = 1; i < l1; i++)
    {
        cal = cal->siguiente;
    }

    for (int i = l1; i <= l2; i++)
    {
        l3.Insertar(cal->c);
        nodoExtraer = cal;
        cal = cal->siguiente;
        Borrar(nodoExtraer->c);
    }

    return l3;
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
