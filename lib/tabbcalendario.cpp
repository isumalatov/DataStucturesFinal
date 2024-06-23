#include "tabbcalendario.h"
#include <queue>

TNodoABB::TNodoABB() : iz(), de(), item() {}

TNodoABB::TNodoABB(const TNodoABB &nodo)
{
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
}

TNodoABB::~TNodoABB()
{
}

TNodoABB &TNodoABB::operator=(const TNodoABB &nodo)
{
    if (this != &nodo)
    {
        item = nodo.item;
        iz = nodo.iz;
        de = nodo.de;
    }

    return *this;
}

TABBCalendario::TABBCalendario()
{
    raiz = NULL;
}

TABBCalendario::TABBCalendario(const TABBCalendario &arbol)
{
    Copia(arbol);
}

TABBCalendario::~TABBCalendario()
{
    if (raiz != NULL)
    {
        delete raiz;
        raiz = NULL;
    }
}

TABBCalendario &TABBCalendario::operator=(const TABBCalendario &arbol)
{
    if (this != &arbol)
    {
        (*this).~TABBCalendario();
        Copia(arbol);
    }

    return *this;
}

void TABBCalendario::Copia(const TABBCalendario &arbol)
{
    if (arbol.raiz != NULL)
    {
        TNodoABB *aux = new TNodoABB();
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

bool TABBCalendario::operator==(const TABBCalendario &arbol) const
{
    return (Inorden() == arbol.Inorden());
}

bool TABBCalendario::Insertar(const TCalendario &cal)
{
    if (Buscar(cal))
    {
        return false;
    }
    else
    {
        TNodoABB *nodoInsertar = new TNodoABB();
        nodoInsertar->item = cal;

        if (EsVacio())
        {
            raiz = nodoInsertar;
            return true;
        }

        TNodoABB *padre = NULL;
        TNodoABB *aux = raiz;

        while (aux != NULL)
        {
            padre = aux;

            if (aux->item > cal)
            {
                aux = aux->iz.raiz;
            }
            else
            {
                aux = aux->de.raiz;
            }
        }

        if (padre->item > cal)
        {
            padre->iz.raiz = nodoInsertar;
        }
        else
        {
            padre->de.raiz = nodoInsertar;
        }

        return true;
    }
}

bool TABBCalendario::Borrar(const TCalendario &cal)
{
    if (Buscar(cal))
    {
        if (Raiz() > cal)
        {
            return raiz->iz.Borrar(cal);
        }
        else if (Raiz() < cal)
        {
            return raiz->de.Borrar(cal);
        }
        else if (raiz->iz.EsVacio() && raiz->de.EsVacio())
        {
            raiz = NULL;
            return true;
        }
        else if (raiz->iz.EsVacio())
        {
            raiz = raiz->de.raiz;
            return true;
        }
        else if (raiz->de.EsVacio())
        {
            raiz = raiz->iz.raiz;
            return true;
        }
        else
        {
            TNodoABB *aux = raiz->iz.raiz;
            TCalendario sustituto = raiz->iz.raiz->item;

            while (!aux->de.EsVacio())
            {
                sustituto = aux->de.raiz->item;
                aux = aux->de.raiz;
            }

            raiz->item = sustituto;
            return raiz->iz.Borrar(sustituto);
        }
    }
    else
    {
        return false;
    }
}

bool TABBCalendario::Buscar(const TCalendario &cal) const
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

bool TABBCalendario::EsVacio() const
{
    return (raiz == NULL);
}

TCalendario TABBCalendario::Raiz() const
{
    TCalendario vacio;

    if (raiz != NULL)
    {
        return raiz->item;
    }

    return vacio;
}

int TABBCalendario::Altura() const
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

int TABBCalendario::Nodos() const
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

int TABBCalendario::NodosHoja() const
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

void TABBCalendario::InordenAux(TVectorCalendario &vector, int &pos) const
{
    if (!EsVacio())
    {
        raiz->iz.InordenAux(vector, pos);
        vector[pos] = raiz->item;
        pos++;
        raiz->de.InordenAux(vector, pos);
    }
}

TVectorCalendario TABBCalendario::Inorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    InordenAux(vector, pos);
    return vector;
}

void TABBCalendario::PreordenAux(TVectorCalendario &vector, int &pos) const
{
    if (!EsVacio())
    {
        vector[pos] = raiz->item;
        pos++;
        raiz->iz.PreordenAux(vector, pos);
        raiz->de.PreordenAux(vector, pos);
    }
}

TVectorCalendario TABBCalendario::Preorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    PreordenAux(vector, pos);
    return vector;
}

void TABBCalendario::PostordenAux(TVectorCalendario &vector, int &pos) const
{
    if (!EsVacio())
    {
        raiz->iz.PostordenAux(vector, pos);
        raiz->de.PostordenAux(vector, pos);
        vector[pos] = raiz->item;
        pos++;
    }
}

TVectorCalendario TABBCalendario::Postorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    PostordenAux(vector, pos);
    return vector;
}

TVectorCalendario TABBCalendario::Niveles() const
{
    TVectorCalendario vector(Nodos());
    int pos = 1;
    if (!EsVacio())
    {
        queue<TNodoABB *> nodosQueue;
        nodosQueue.push(raiz);

        while (!nodosQueue.empty())
        {
            TNodoABB *nodoActual = nodosQueue.front();
            nodosQueue.pop();
            vector[pos] = nodoActual->item;
            pos++;
            if (nodoActual->iz.raiz != NULL)
            {
                nodosQueue.push(nodoActual->iz.raiz);
            }
            if (nodoActual->de.raiz != NULL)
            {
                nodosQueue.push(nodoActual->de.raiz);
            }
        }
    }

    return vector;
}

TABBCalendario TABBCalendario::operator+(const TABBCalendario &arbolD)
{
    TABBCalendario sumaArbol = *this;
    TVectorCalendario vector(arbolD.Nodos());
    vector = arbolD.Inorden();

    for (int i = 1; i <= vector.Tamano(); i++)
    {
        sumaArbol.Insertar(vector[i]);
    }

    return sumaArbol;
}

TABBCalendario TABBCalendario::operator-(const TABBCalendario &arbolD)
{
    TABBCalendario restaArbol;
    TVectorCalendario vector(Nodos());
    vector = Inorden();

    for (int i = 1; i <= vector.Tamano(); i++)
    {
        if (!arbolD.Buscar(vector[i]))
        {
            restaArbol.Insertar(vector[i]);
        }
    }

    return restaArbol;
}

ostream &operator<<(ostream &s, const TABBCalendario &arbol)
{
    s << arbol.Niveles();

    return s;
}
