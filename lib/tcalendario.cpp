#include "tcalendario.h"

bool TCalendario::daysInMonth(int dia, int mes, int anyo)
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

void TCalendario::copia(const TCalendario &c)
{
    dia = c.dia;
    mes = c.mes;
    anyo = c.anyo;
    if (c.mensaje != NULL)
    {
        mensaje = new char[strlen(c.mensaje) + 1];
        strcpy(this->mensaje, c.mensaje);
    }
    else
    {
        mensaje = NULL;
    }
}

TCalendario::TCalendario()
{
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

TCalendario::TCalendario(int dia, int mes, int anyo, char *mens)
{
    if (!daysInMonth(dia, mes, anyo))
    {
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
    else
    {
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;
        if (mens != NULL)
        {
            mensaje = new char[strlen(mens) + 1];
            strcpy(mensaje, mens);
        }
        else
        {
            mensaje = NULL;
        }
    }
}

TCalendario::TCalendario(const TCalendario &c)
{
    copia(c);
}

TCalendario::~TCalendario()
{
    dia = 1;
    mes = 1;
    anyo = 1900;
    if (mensaje != NULL)
    {
        delete[] mensaje;
    }
    mensaje = NULL;
}

TCalendario &TCalendario::operator=(const TCalendario &c)
{
    if (this != &c)
    {
        (*this).~TCalendario();
        copia(c);
    }
    return *this;
}

TCalendario TCalendario::operator+(int n)
{
    TCalendario c(*this);
    for (int i = 0; i < n; i++)
    {
        c++;
    }
    return c;
}

TCalendario TCalendario::operator-(int n)
{
    TCalendario c(*this);
    for (int i = 0; i < n; i++)
    {
        c--;
    }
    if (!daysInMonth(c.dia, c.mes, c.anyo))
    {
        c.~TCalendario();
    }
    return c;
}

TCalendario TCalendario::operator++(int dias)
{
    TCalendario c(*this);

    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10)
    {
        if (dia == 31)
        {
            dia = 1;
            mes++;
        }
        else
        {
            dia++;
        }
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        if (dia == 30)
        {
            dia = 1;
            mes++;
        }
        else
        {
            dia++;
        }
    }
    else if (mes == 12)
    {
        if (dia == 31)
        {
            dia = 1;
            mes = 1;
            anyo++;
        }
        else
        {
            dia++;
        }
    }
    else if (mes == 2)
    {
        if (dia == 29)
        {
            dia = 1;
            mes++;
        }
        else if (dia == 28)
        {
            int bisiesto = 0;

            if (anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
            {
                bisiesto = 1;
            }

            if (bisiesto == 0)
            {
                dia = 1;
                mes++;
            }
            else
            {
                dia++;
            }
        }
        else
        {
            dia++;
        }
    }

    return c;
}

TCalendario &TCalendario::operator++()
{
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10)
    {
        if (dia == 31)
        {
            dia = 1;
            mes++;
        }
        else
        {
            dia++;
        }
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        if (dia == 30)
        {
            dia = 1;
            mes++;
        }
        else
        {
            dia++;
        }
    }
    else if (mes == 12)
    {
        if (dia == 31)
        {
            dia = 1;
            mes = 1;
            anyo++;
        }
        else
        {
            dia++;
        }
    }
    else if (mes == 2)
    {
        if (dia == 29)
        {
            dia = 1;
            mes++;
        }
        else if (dia == 28)
        {
            int bisiesto = 0;

            if (anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
            {
                bisiesto = 1;
            }

            if (bisiesto == 0)
            {
                dia = 1;
                mes++;
            }
            else
            {
                dia++;
            }
        }
        else
        {
            dia++;
        }
    }

    return *this;
}

TCalendario TCalendario::operator--(int dias)
{
    TCalendario temp(*this);

    if (dia == 1)
    {
        if (mes > 1)
        {
            mes--;
            if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10)
            {
                dia = 31;
            }
            else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
            {
                dia = 30;
            }
            else if (mes == 2)
            {
                int bisiesto = 0;
                if (anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
                {
                    bisiesto = 1;
                }
                if (bisiesto == 0)
                {
                    dia = 28;
                }
                else
                {
                    dia = 29;
                }
            }
        }
        else if (mes == 1)
        {
            dia = 31;
            mes = 12;
            anyo--;
        }
    }
    else
    {
        dia--;
    }

    if (!daysInMonth(dia, mes, anyo))
    {
        this->~TCalendario();
    }

    return temp;
}

TCalendario &TCalendario::operator--()
{
    if (dia == 1)
    {
        if (mes > 1)
        {
            mes--;
            if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10)
            {
                dia = 31;
            }
            else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
            {
                dia = 30;
            }
            else if (mes == 2)
            {
                int bisiesto = 0;
                if (anyo % 4 == 0 && (anyo % 100 != 0 || anyo % 400 == 0))
                {
                    bisiesto = 1;
                }
                if (bisiesto == 0)
                {
                    dia = 28;
                }
                else
                {
                    dia = 29;
                }
            }
        }
        else if (mes == 1)
        {
            dia = 31;
            mes = 12;
            anyo--;
        }
    }
    else
    {
        dia--;
    }

    if (!daysInMonth(dia, mes, anyo))
    {
        this->~TCalendario();
    }

    return *this;
}

bool TCalendario::ModFecha(int d, int m, int a)
{
    if (daysInMonth(d, m, a))
    {
        dia = d;
        mes = m;
        anyo = a;
        return true;
    }

    return false;
}

bool TCalendario::ModMensaje(char *mens)
{
    if (mens == NULL)
    {
        delete[] mensaje;
        mensaje = NULL;
        return true;
    }
    else
    {
        delete[] mensaje;
        mensaje = new char[strlen(mens) + 1];
        strcpy(this->mensaje, mens);
        return true;
    }

    return false;
}

bool TCalendario::operator==(const TCalendario &c)
{
    bool iguales;

    iguales = dia == c.dia && mes == c.mes && anyo == c.anyo;

    if (iguales)
    {
        if (mensaje == NULL && c.mensaje == NULL)
        {
            iguales = true;
        }
        else if (mensaje == NULL || c.mensaje == NULL)
        {
            iguales = false;
        }
        else
        {
            iguales = strcmp(mensaje, c.mensaje) == 0;
        }
    }

    return iguales;
}

bool TCalendario::operator!=(const TCalendario &c)
{
    return !(*this == c);
}

bool TCalendario::operator>(const TCalendario &c)
{
    if (anyo > c.anyo)
    {
        return true;
    }
    else if (anyo == c.anyo && mes > c.mes)
    {
        return true;
    }
    else if (anyo == c.anyo && mes == c.mes && dia > c.dia)
    {
        return true;
    }
    else if (anyo == c.anyo && mes == c.mes && dia == c.dia)
    {
        if (mensaje != c.mensaje)
        {
            if (mensaje == NULL)
            {
                return false;
            }
            else if (c.mensaje == NULL)
            {
                return true;
            }
            else
            {
                if (strcmp(mensaje, c.mensaje) == 0)
                {
                    return false;
                }
                else if (strcmp(mensaje, c.mensaje) > 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    return false;
}

bool TCalendario::operator<(const TCalendario &c)
{
    if ((*this) == c)
    {
        return false;
    }
    else
    {
        return !(*this > c);
    }
}

bool TCalendario::EsVacio()
{
    if (dia == 1 && mes == 1 && anyo == 1900 && mensaje == NULL)
    {
        return true;
    }

    return false;
}

int TCalendario::Dia() const
{
    return dia;
}

int TCalendario::Mes() const
{
    return mes;
}

int TCalendario::Anyo() const
{
    return anyo;
}

char *TCalendario::Mensaje() const
{
    return mensaje;
}

ostream &operator<<(ostream &s, const TCalendario &c)
{
    if (c.Dia() < 10)
    {
        s << 0 << c.Dia();
    }
    else
    {
        s << c.Dia();
    }

    s << "/";

    if (c.Mes() < 10)
    {
        s << 0 << c.Mes();
    }
    else
    {
        s << c.Mes();
    }

    s << "/";

    s << c.Anyo() << " ";

    if (c.Mensaje() == NULL)
    {
        s << "\"\"";
    }
    else
    {
        s << "\"" << c.Mensaje() << "\"";
    }

    return s;
}
