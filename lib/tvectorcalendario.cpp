#include "tvectorcalendario.h"

bool TVectorCalendario::daysInMonth(int dia, int mes, int anyo)
{
    if (mes < 1 || mes > 12 || anyo < 1900)
    {
        return false;
    }
    else
    {
        int sum = 0;
        if ((anyo % 100 != 0 || anyo % 400 == 0) && anyo % 4 == 0)
        {
            sum = 1;
        }
        int days[] = {31, 28 + sum, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (dia < 1 || dia > days[mes - 1])
        {
            return false;
        }
    }

    return true;
}

void TVectorCalendario::copia(const TVectorCalendario &v)
{
    tamano = v.tamano;
    c = new TCalendario[tamano];

    for (int i = 0; i < tamano; i++)
    {
        c[i] = v.c[i];
    }
}

TVectorCalendario::TVectorCalendario()
{
    tamano = 0;
    c = NULL;
}

TVectorCalendario::TVectorCalendario(int tam)
{
    if (tam <= 0)
    {
        c = NULL;
        tamano = 0;
    }
    else
    {
        c = new TCalendario[tam];
        tamano = tam;
    }
}

TVectorCalendario::TVectorCalendario(const TVectorCalendario &v)
{
    copia(v);
}

TVectorCalendario::~TVectorCalendario()
{
    if (c != NULL)
    {
        delete[] c;
        c = NULL;
    }
}

TVectorCalendario &TVectorCalendario::operator=(const TVectorCalendario &v)
{
    if (this != &v)
    {
        (*this).~TVectorCalendario();
        copia(v);
    }
    else
    {
        return *this;
    }

    return *this;
}

bool TVectorCalendario::operator==(const TVectorCalendario &v)
{
    if (tamano != v.tamano)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < tamano; i++)
        {
            if (this->c[i] != v.c[i])
            {
                return false;
            }
        }
    }

    return true;
}

bool TVectorCalendario::operator!=(const TVectorCalendario &vec)
{
    return !(*this == vec);
}

TCalendario &TVectorCalendario::operator[](int i)
{
    if (i > 0 && i <= tamano)
    {
        return c[i - 1];
    }

    return error;
}

TCalendario TVectorCalendario::operator[](int i) const
{
    if (i > 0 && i <= tamano)
    {
        return c[i - 1];
    }

    return error;
}

int TVectorCalendario::Tamano()
{
    return tamano;
}

int TVectorCalendario::Ocupadas()
{
    int ocupadas = 0;

    for (int i = 0; i < tamano; i++)
    {
        if (this->c[i] != this->error)
        {
            ocupadas++;
        }
    }

    return ocupadas;
}

bool TVectorCalendario::ExisteCal(const TCalendario &casillas)
{
    for (int i = 0; i < tamano; i++)
    {
        if (c[i] == casillas)
        {
            return true;
        }
    }

    return false;
}

void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo)
{
    cout << "[";

    if (daysInMonth(dia, mes, anyo))
    {
        for (int i = 0; i < tamano; i++)
        {
            if (c[i].Anyo() < anyo)
            {
                continue;
            }
            else if (c[i].Anyo() == anyo && c[i].Mes() < mes)
            {
                continue;
            }
            else if (c[i].Anyo() == anyo && c[i].Mes() == mes && c[i].Dia() < dia)
            {
                continue;
            }
            else
            {
                cout << c[i];

                if (i < tamano - 1)
                {
                    cout << ", ";
                }
            }
        }
    }

    cout << "]";
}

bool TVectorCalendario::Redimensionar(int tam)
{
    if (tam <= 0)
    {
        return false;
    }
    if (tam == tamano)
    {
        return false;
    }
    TCalendario *nuevo = new TCalendario[tam];

    if (tam >= tamano)
    {
        TCalendario *vacio = new TCalendario();

        for (int i = 0; i < tamano; i++)
        {
            nuevo[i] = c[i];
        }

        for (int i = tamano; i < tam; i++)
        {
            nuevo[i] = *vacio;
        }

        delete vacio;

        (*this).~TVectorCalendario();
        c = nuevo;
        tamano = tam;

        return true;
    }
    else
    {
        for (int i = 0; i < tam; i++)
        {
            nuevo[i] = c[i];
        }
        (*this).~TVectorCalendario();
        c = nuevo;
        tamano = tam;

        return true;
    }
}

ostream &operator<<(ostream &s, const TVectorCalendario &imprimir)
{
    s << "[";
    for (int i = 0; i < imprimir.tamano; i++)
    {
        s << "(" << i + 1 << ") " << imprimir.c[i];

        if (i < imprimir.tamano - 1)
        {
            s << ", ";
        }
    }
    s << "]";

    return s;
}
