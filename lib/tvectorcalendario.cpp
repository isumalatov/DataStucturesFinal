#include "tvectorcalendario.h"

TVectorCalendario::TVectorCalendario()
{
    this->c = NULL;
    this->tamano = 0;
}

TVectorCalendario::TVectorCalendario(int tam)
{
    if (tam <= 0)
    {
        this->c = NULL;
        this->tamano = 0;
    }
    else
    {
        this->c = new TCalendario[tam];
        this->tamano = tam;
    }
}

TVectorCalendario::TVectorCalendario(const TVectorCalendario &vec)
{
    Copia(vec);
}

TVectorCalendario::~TVectorCalendario()
{
    if (this->c != NULL)
    {
        delete[] this->c;
        this->c = NULL;
    }
}

TVectorCalendario &TVectorCalendario::operator=(const TVectorCalendario &vec)
{
    if (this != &vec)
    {
        (*this).~TVectorCalendario();
        Copia(vec);
    }
    else
    {
        return *this;
    }

    return *this;
}

void TVectorCalendario::Copia(const TVectorCalendario &vec)
{
    this->tamano = vec.tamano;
    this->c = new TCalendario[tamano];

    for (int i = 0; i < tamano; i++)
    {
        c[i] = vec.c[i];
    }
}

bool TVectorCalendario::ComprobarFecha(int dia, int mes, int anyo)
{
    bool valido = true;

    if (anyo < 1900 || mes < 1 || mes > 12)
    {

        valido = false;
    }
    else
    {
        int bisiesto = 0;

        if (anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
        {
            bisiesto = 1;
        }

        int dias_por_mes[] = {31, 28 + bisiesto, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (dia < 1 || dia > dias_por_mes[mes - 1])
        {

            valido = false;
        }
    }

    return valido;
}

bool TVectorCalendario::operator==(const TVectorCalendario &vec)
{
    if (tamano == vec.tamano)
    {
        for (int i = 0; i < tamano; i++)
        {
            if (this->c[i] != vec.c[i])
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool TVectorCalendario::operator!=(const TVectorCalendario &vec)
{
    return !(*this == vec);
}

TCalendario &TVectorCalendario::operator[](int num)
{
    if (num > 0 && num <= this->tamano)
    {
        return this->c[num - 1];
    }

    return error;
}

TCalendario TVectorCalendario::operator[](int num) const
{
    if (num > 0 && num <= this->tamano)
    {
        return this->c[num - 1];
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

bool TVectorCalendario::ExisteCal(const TCalendario &cal)
{
    for (int i = 0; i < tamano; i++)
    {
        if (this->c[i] == cal)
        {
            return true;
        }
    }

    return false;
}

void TVectorCalendario::MostrarMensajes(int dia, int mes, int anyo)
{
    cout << "[";

    if (ComprobarFecha(dia, mes, anyo))
    {
        for (int i = 0; i < tamano; i++)
        {
            if (this->c[i].Anyo() < anyo)
            {
                continue;
            }
            else if (this->c[i].Anyo() == anyo && this->c[i].Mes() < mes)
            {
                continue;
            }
            else if (this->c[i].Anyo() == anyo && this->c[i].Mes() == mes && this->c[i].Dia() < dia)
            {
                continue;
            }
            else
            {
                cout << this->c[i];

                if (i < this->tamano - 1)
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
    if (tam <= 0 || tam == this->tamano)
    {
        return false;
    }

    TCalendario *nuevo = new TCalendario[tam];

    if (tam < this->tamano)
    {
        for (int i = 0; i < tam; i++)
        {
            nuevo[i] = this->c[i];
        }
        (*this).~TVectorCalendario();
        this->c = nuevo;
        this->tamano = tam;

        return true;
    }
    else
    {
        TCalendario *vacio = new TCalendario();

        for (int i = 0; i < this->tamano; i++)
        {
            nuevo[i] = this->c[i];
        }

        for (int i = this->tamano; i < tam; i++)
        {
            nuevo[i] = *vacio;
        }

        delete vacio;

        (*this).~TVectorCalendario();
        this->c = nuevo;
        this->tamano = tam;

        return true;
    }
}

ostream &operator<<(ostream &s, const TVectorCalendario &vec)
{
    s << "[";
    for (int i = 0; i < vec.tamano; i++)
    {
        s << "(" << i + 1 << ") " << vec.c[i];

        if (i < vec.tamano - 1)
        {
            s << ", ";
        }
    }
    s << "]";

    return s;
}
