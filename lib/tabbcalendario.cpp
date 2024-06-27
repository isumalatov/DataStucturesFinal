#include "tabbcalendario.h"
#include <queue>

TNodoABB::TNodoABB()
{
    item = TCalendario();
    iz = TABBCalendario();
    de = TABBCalendario();
}

TNodoABB::TNodoABB(const TNodoABB &n)
{
    item = n.item;
    iz = n.iz;
    de = n.de;
}

TNodoABB::~TNodoABB()
{
    item.~TCalendario();
    iz.~TABBCalendario();
    de.~TABBCalendario();
}

TNodoABB &TNodoABB::operator=(const TNodoABB &n)
{
    if (this != &n)
    {
        item = n.item;
        iz = n.iz;
        de = n.de;
    }

    return *this;
}

TABBCalendario::TABBCalendario()
{
    raiz = NULL;
}

TABBCalendario::TABBCalendario(const TABBCalendario &arbol)
{
    if (arbol.raiz != NULL)
    {
        TNodoABB *aux = new TNodoABB();
        aux->item = arbol.raiz->item;
        this->raiz = aux;
        this->raiz->iz = TABBCalendario(arbol.raiz->iz);
        this->raiz->de = TABBCalendario(arbol.raiz->de);
    }
    else
        raiz = NULL;
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
        if (arbol.raiz != NULL)
        {
            TNodoABB *aux = new TNodoABB();
            aux->item = arbol.raiz->item;
            this->raiz = aux;
            this->raiz->iz = TABBCalendario(arbol.raiz->iz);
            this->raiz->de = TABBCalendario(arbol.raiz->de);
        }
    }
    return *this;
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
        if (raiz->item > cal)
            return raiz->iz.Borrar(cal);
        else if (raiz->item < cal)
            return raiz->de.Borrar(cal);
        else if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
        {
            delete raiz;
            raiz = NULL;
            return true;
        }
        else if (raiz->iz.raiz == NULL)
        {
            raiz = raiz->de.raiz;
            return true;
        }
        else if (raiz->de.raiz == NULL)
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
                sustituto = raiz->de.raiz->item;
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
    if (raiz != NULL)
    {
        return raiz->item;
    }

    return TCalendario();
}

int TABBCalendario::Altura() const
{
    if (raiz != NULL)
    {
        int iz = raiz->iz.Altura();
        int de = raiz->de.Altura();
        return 1 + (iz > de ? iz : de);
    }
    return 0;
}

int TABBCalendario::Nodos() const
{
    if (raiz != NULL)
        return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    return 0;
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
    if (raiz != NULL)
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
    if (raiz != NULL)
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
    if (raiz != NULL)
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
    if (raiz != NULL)
    {
        queue<TNodoABB *> cola;
        cola.push(raiz);
        while (!cola.empty())
        {
            TNodoABB *aux = cola.front();
            cola.pop();
            vector[pos] = aux->item;
            pos++;
            if (aux->iz.raiz != NULL)
                cola.push(aux->iz.raiz);
            if (aux->de.raiz != NULL)
                cola.push(aux->de.raiz);
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

bool TABBCalendario::InsertarExamen(const TCalendario &cal, int &resultado)
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
            resultado = 0;
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
            resultado = -1;
        }
        else
        {
            padre->de.raiz = nodoInsertar;
            resultado = 1;
        }
        return true;
    }
}

void TABBCalendario::Clasificar(TVectorCalendario &v,TListaCalendario &l1, TListaCalendario &l2, TListaCalendario &l3)
{
    for(int i = 1; i <= v.Tamano(); i++)
    {
        int resultado = 2;
        this->InsertarExamen(v[i], resultado);
        if(resultado == 0)
        {
            l1.Insertar(v[i]);
        }
        else if(resultado == -1)
        {
            l2.Insertar(v[i]);
        }
        else if(resultado == 1)
        {
            l3.Insertar(v[i]);
        }
    }
}