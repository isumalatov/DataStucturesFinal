#include "tcalendario.h"

TCalendario::TCalendario()
{
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

TCalendario::TCalendario(int dia, int mes, int anyo, char *mens)
{
    if (ComprobarFecha(dia, mes, anyo))
    {
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;

        if (mens == NULL)
        {
            this->mensaje = NULL;
        }
        else
        {
            this->mensaje = new char[strlen(mens) + 1];
            strcpy(this->mensaje, mens);
        }
    }
    else
    {
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
}

bool TCalendario::ComprobarFecha(int dia, int mes, int anyo)
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

TCalendario::TCalendario(const TCalendario &cal)
{
    Copia(cal);
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

TCalendario &TCalendario::operator=(const TCalendario &cal)
{
    if (this != &cal)
    {
        (*this).~TCalendario();
        Copia(cal);
    }

    return *this;
}

void TCalendario::Copia(const TCalendario &cal)
{
    dia = cal.dia;
    mes = cal.mes;
    anyo = cal.anyo;

    if (cal.mensaje != NULL)
    {
        mensaje = new char[strlen(cal.mensaje) + 1];
        strcpy(this->mensaje, cal.mensaje);
    }
    else
    {
        mensaje = NULL;
    }
}

TCalendario TCalendario::operator+(int dias)
{
    TCalendario temp(*this);

    for (int i = 0; i < dias; i++)
    {
        temp++;
    }

    return temp;
}

TCalendario TCalendario::operator-(int dias)
{
    TCalendario temp(*this);

    for (int i = 0; i < dias; i++)
    {
        temp--;
    }

    if (!ComprobarFecha(temp.dia, temp.mes, temp.anyo))
    {
        temp.~TCalendario();
    }

    return temp;
}

TCalendario TCalendario::operator++(int dias)
{
    TCalendario temp(*this);

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

    return temp;
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

    if (!ComprobarFecha(dia, mes, anyo))
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

    if (!ComprobarFecha(dia, mes, anyo))
    {
        this->~TCalendario();
    }

    return *this;
}

bool TCalendario::ModFecha(int dia, int mes, int anyo)
{
    bool valido = false;

    if (ComprobarFecha(dia, mes, anyo))
    {
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;
        valido = true;
    }

    return valido;
}

bool TCalendario::ModMensaje(char *mens)
{

    if (mens == NULL)
    {
        delete[] this->mensaje;
        this->mensaje = NULL;
        return true;
    }
    else
    {
        delete[] this->mensaje;
        this->mensaje = new char[strlen(mens) + 1];
        strcpy(this->mensaje, mens);
        return true;
    }

    return false;
}

bool TCalendario::operator==(const TCalendario &cal)
{

    if (dia == cal.dia && mes == cal.mes && anyo == cal.anyo)
    {
        if (mensaje == NULL || cal.mensaje == NULL)
        {
            if (mensaje == NULL && cal.mensaje == NULL)
            {
                return true;
            }
        }
        else if (strcmp(mensaje, cal.mensaje) == 0)
        {
            return true;
        }
    }

    return false;
}

bool TCalendario::operator!=(const TCalendario &cal)
{
    return !(*this == cal);
}

bool TCalendario::operator>(const TCalendario &cal)
{
    if (this->anyo > cal.anyo)
    {
        return true;
    }
    else if (this->anyo == cal.anyo && this->mes > cal.mes)
    {
        return true;
    }
    else if (this->anyo == cal.anyo && this->mes == cal.mes && this->dia > cal.dia)
    {
        return true;
    }
    else if (this->anyo == cal.anyo && this->mes == cal.mes && this->dia == cal.dia)
    {
        if (this->mensaje != cal.mensaje)
        {
            if (this->mensaje == NULL)
            {
                return false;
            }
            else if (cal.mensaje == NULL)
            {
                return true;
            }
            else
            {
                if (strcmp(this->mensaje, cal.mensaje) == 0)
                {
                    return false;
                }
                else if (strcmp(this->mensaje, cal.mensaje) > 0)
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

bool TCalendario::operator<(const TCalendario &cal)
{
    if ((*this) == cal)
    {
        return false;
    }
    else
    {
        return !(*this > cal);
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

ostream &operator<<(ostream &s, const TCalendario &calendario)
{
    if (calendario.Dia() < 10)
    {
        s << 0 << calendario.Dia();
    }
    else
    {
        s << calendario.Dia();
    }

    s << "/";

    if (calendario.Mes() < 10)
    {
        s << 0 << calendario.Mes();
    }
    else
    {
        s << calendario.Mes();
    }

    s << "/";

    s << calendario.Anyo() << " ";

    if (calendario.Mensaje() == NULL)
    {
        s << "\"\"";
    }
    else
    {
        s << "\"" << calendario.Mensaje() << "\"";
    }

    return s;
}
