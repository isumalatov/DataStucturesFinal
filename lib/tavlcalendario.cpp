#include "tavlcalendario.h"

TNodoAVL::TNodoAVL() : iz(), de(), item(), fe() {}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo)
{
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
    fe = nodo.fe;
}

TNodoAVL::~TNodoAVL()
{
}

TNodoAVL &TNodoAVL::operator=(const TNodoAVL &nodo)
{
    if (this != &nodo)
    {
        item = nodo.item;
        iz = nodo.iz;
        de = nodo.de;
        fe = nodo.fe;
    }

    return *this;
}

TAVLCalendario::TAVLCalendario()
{
    raiz = NULL;
}

TAVLCalendario::TAVLCalendario(const TAVLCalendario &arbol)
{
    Copia(arbol);
}

TAVLCalendario::~TAVLCalendario()
{
    if (raiz != NULL)
    {
        delete raiz;
        raiz = NULL;
    }
}

TAVLCalendario &TAVLCalendario::operator=(const TAVLCalendario &arbol)
{
    if (this != &arbol)
    {
        (*this).~TAVLCalendario();
        Copia(arbol);
    }

    return *this;
}

void TAVLCalendario::Copia(const TAVLCalendario &arbol)
{
    if (arbol.raiz != NULL)
    {
        TNodoAVL *aux = new TNodoAVL();
        aux->item = arbol.raiz->item;
        this->raiz = aux;
        this->raiz->iz.Copia(arbol.raiz->iz);
        this->raiz->de.Copia(arbol.raiz->de);
    }
    else
    {
        this->raiz = NULL;
    }
}

bool TAVLCalendario::operator==(const TAVLCalendario &arbol) const
{
    return (Inorden() == arbol.Inorden());
}

bool TAVLCalendario::operator!=(const TAVLCalendario &arbol) const
{
    return !(*this == arbol);
}

int TAVLCalendario::ObtenerNodoFE() const
{
    return (raiz->de.Altura() - raiz->iz.Altura());
}

void TAVLCalendario::ObtenerArbolFE()
{
    if (raiz != NULL)
    {
        raiz->iz.ObtenerArbolFE();
        raiz->de.ObtenerArbolFE();
        raiz->fe = ObtenerNodoFE();
    }
}

void TAVLCalendario::RotacionII()
{
    TNodoAVL *j;
    j = raiz->iz.raiz;
    raiz->iz.raiz = raiz->iz.raiz->de.raiz;
    j->de.raiz = raiz;
    raiz = j;

    ObtenerArbolFE();
}

void TAVLCalendario::RotacionID()
{
    TNodoAVL *j;
    j = raiz->iz.raiz;
    raiz->iz.raiz = j->de.raiz->de.raiz;
    j->de.raiz->de.raiz = raiz;
    raiz = j->de.raiz;
    j->de.raiz = raiz->iz.raiz;
    raiz->iz.raiz = j;

    ObtenerArbolFE();
}

void TAVLCalendario::RotacionDD()
{
    TNodoAVL *j;
    j = raiz->de.raiz;
    raiz->de.raiz = raiz->de.raiz->iz.raiz;
    j->iz.raiz = raiz;
    raiz = j;

    ObtenerArbolFE();
}

void TAVLCalendario::RotacionDI()
{
    TNodoAVL *j;
    j = raiz->de.raiz;
    raiz->de.raiz = j->iz.raiz->iz.raiz;
    j->iz.raiz->iz.raiz = raiz;
    raiz = j->iz.raiz;
    j->iz.raiz = raiz->de.raiz;
    raiz->de.raiz = j;

    ObtenerArbolFE();
}

void TAVLCalendario::ComprobarFE()
{
    raiz->fe = ObtenerNodoFE();

    if (raiz->fe < -1)
    {
        if (raiz->iz.raiz->fe <= 0)
        {
            RotacionII();
        }
        else
        {
            RotacionID();
        }
    }
    else if (raiz->fe > 1)
    {
        if (raiz->de.raiz->fe >= 0)
        {
            RotacionDD();
        }
        else
        {
            RotacionDI();
        }
    }
}

bool TAVLCalendario::Insertar(const TCalendario &cal)
{
    bool insertado = false;

    if (!this->Buscar(cal))
    {
        if (this->EsVacio())
        {
            TNodoAVL *nodoInsertar = new TNodoAVL();
            nodoInsertar->item = cal;
            raiz = nodoInsertar;
            insertado = true;
        }
        else
        {
            if (raiz->item > cal)
            {
                insertado = raiz->iz.Insertar(cal);
            }
            else
            {
                insertado = raiz->de.Insertar(cal);
            }
        }
    }

    if (insertado)
    {
        ComprobarFE();
    }

    return insertado;
}

bool TAVLCalendario::Borrar(const TCalendario &cal)
{
    bool borrado = false;

    if (Buscar(cal))
    {
        if (Raiz() > cal)
        {
            borrado = raiz->iz.Borrar(cal);
        }
        else if (Raiz() < cal)
        {
            borrado = raiz->de.Borrar(cal);
        }
        else if (raiz->iz.EsVacio() && raiz->de.EsVacio())
        {
            raiz = NULL;
            borrado = true;
        }
        else if (raiz->iz.EsVacio())
        {
            raiz = raiz->de.raiz;
            borrado = true;
        }
        else if (raiz->de.EsVacio())
        {
            raiz = raiz->iz.raiz;
            borrado = true;
        }
        else if (!raiz->iz.EsVacio() && !raiz->de.EsVacio())
        {
            TNodoAVL *aux = raiz->iz.raiz;
            TCalendario sustituto = raiz->iz.raiz->item;

            while (!aux->de.EsVacio())
            {
                sustituto = aux->de.raiz->item;
                aux = aux->de.raiz;
            }

            raiz->item = sustituto;
            raiz->iz.Borrar(sustituto);
        }
        else
        {
            borrado = false;
        }
    }
    if (raiz != NULL)
    {
        ComprobarFE();
    }

    return borrado;
}

bool TAVLCalendario::Buscar(const TCalendario &cal) const
{
    if (raiz != NULL)
    {
        if (raiz->item == cal)
        {
            return true;
        }
        if (raiz->item > cal)
        {
            return raiz->iz.Buscar(cal);
        }
        else
        {
            return raiz->de.Buscar(cal);
        }
    }

    return false;
}

bool TAVLCalendario::EsVacio() const
{
    return (raiz == NULL);
}

TCalendario TAVLCalendario::Raiz() const
{
    TCalendario vacio;

    if (raiz != NULL)
    {
        return raiz->item;
    }

    return vacio;
}

int TAVLCalendario::Altura() const
{
    int alturaIZ, alturaDE;

    if (EsVacio())
    {
        return 0;
    }
    else
    {
        alturaIZ = raiz->iz.Altura();
        alturaDE = raiz->de.Altura();

        return (1 + max(alturaIZ, alturaDE));
    }
}

int TAVLCalendario::Nodos() const
{
    int nodosIZ, nodosDE;

    if (EsVacio())
    {
        return 0;
    }
    else
    {
        nodosIZ = raiz->iz.Nodos();
        nodosDE = raiz->de.Nodos();

        return (1 + nodosIZ + nodosDE);
    }
}

int TAVLCalendario::NodosHoja() const
{
    int nodosHoja;

    if (EsVacio())
    {
        return 0;
    }
    else
    {
        nodosHoja = raiz->iz.NodosHoja() + raiz->de.NodosHoja();

        if (raiz->iz.EsVacio() && raiz->de.EsVacio())
        {
            return (1 + nodosHoja);
        }
        else
        {
            return nodosHoja;
        }
    }
}

void TAVLCalendario::InordenAux(TVectorCalendario &vector, int &pos) const
{
    if (!EsVacio())
    {
        raiz->iz.InordenAux(vector, pos);
        vector[pos] = raiz->item;
        pos++;
        raiz->de.InordenAux(vector, pos);
    }
}

TVectorCalendario TAVLCalendario::Inorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    InordenAux(vector, pos);
    return vector;
}

void TAVLCalendario::PreordenAux(TVectorCalendario &vector, int &pos) const
{
    if (!EsVacio())
    {
        vector[pos] = raiz->item;
        pos++;
        raiz->iz.PreordenAux(vector, pos);
        raiz->de.PreordenAux(vector, pos);
    }
}

TVectorCalendario TAVLCalendario::Preorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    PreordenAux(vector, pos);
    return vector;
}

void TAVLCalendario::PostordenAux(TVectorCalendario &vector, int &pos) const
{
    if (!EsVacio())
    {
        raiz->iz.PostordenAux(vector, pos);
        raiz->de.PostordenAux(vector, pos);
        vector[pos] = raiz->item;
        pos++;
    }
}

TVectorCalendario TAVLCalendario::Postorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    PostordenAux(vector, pos);
    return vector;
}

ostream &operator<<(ostream &s, const TAVLCalendario &arbol)
{
    s << arbol.Inorden();

    return s;
}
