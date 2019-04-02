//Fecha.cpp (Implementación de las operaciones de la clase).

#include "fecha.hpp"
#include <ctime>
#include <cstdio>
#include <iostream>
#include <cstring>

// Inicialización de las constantes estáticas de la clase.
const int Fecha::AnnoMinimo(1902);
const int Fecha::AnnoMaximo(2037);

void Fecha::comprobar()
{
    int diaDelMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y < AnnoMinimo)
        throw Invalida{"Año inválido, menor que el año mínimo."};
    if (y > AnnoMaximo)
        throw Invalida{"Año inválido, mayor que el año máximo."};
    bool bisiesto = y % 4 == 0 && (y % 400 == 0 || y % 100 != 0);
    if (m <= 0 || m > 12)
        throw Invalida{"Mes inválido, no cumple el formato."};
    if (bisiesto)
        diaDelMes[1]++;
    if (d <= 0 || d > diaDelMes[m - 1])
        throw Invalida{"Dia inválido, no cumple el formato."};
}

Fecha::Fecha(int dia, int mes, int anno) : d(dia),
                                           m(mes),
                                           y(anno)
{
    std::time_t calendario = std::time(nullptr);
    std::tm *tiempo_descompuesto = std::localtime(&calendario);
    if (d == 0)
        d = tiempo_descompuesto->tm_mday;
    if (m == 0)
        m = tiempo_descompuesto->tm_mon + 1;
    if (y == 0)
        y = tiempo_descompuesto->tm_year + 1900;
    comprobar();
}

Fecha::Fecha(const char *cadena)
{
    int conversiones = std::sscanf(cadena, "%d/%d/%d", &d, &m, &y);
    if (conversiones != 3)
    {
        throw Invalida{"La fecha no sigue el formato dd/mm/aaaa"};
    }
    else
    {
        std::time_t calendario = std::time(nullptr);
        std::tm *tiempo_descompuesto = std::localtime(&calendario);
        if (d == 0)
            d = tiempo_descompuesto->tm_mday;
        if (m == 0)
            m = tiempo_descompuesto->tm_mon + 1;
        if (y == 0)
            y = tiempo_descompuesto->tm_year + 1900;
        comprobar();
    }
}

int Fecha::dia() const
{
    return d;
}

int Fecha::mes() const
{
    return m;
}

int Fecha::anno() const
{
    return y;
}

Fecha &Fecha::operator+=(int dia)
{
    std::tm estructura{0, 0, 0, d + dia, m - 1, y - 1900};
    estructura.tm_isdst=0;
    std::mktime(&estructura);
    d = estructura.tm_mday;
    m = estructura.tm_mon + 1;
    y = estructura.tm_year + 1900;
    comprobar();
    return *this;
}

Fecha &Fecha::operator-=(int dia)
{
    *this += (-dia);
    return *this;
}

Fecha Fecha::operator+(int dia) const
{
    Fecha aux{*this};
    aux += dia;
    return aux;
}

Fecha Fecha::operator-(int dia) const
{
    Fecha aux{*this};
    aux += (-dia);
    return aux;
}

Fecha Fecha::operator++(int)
{
    Fecha aux{*this};
    *this += 1;
    return aux;
}

Fecha &Fecha::operator++()
{
    *this += 1;
    return *this;
}

Fecha Fecha::operator--(int)
{
    Fecha aux{*this};
    *this += (-1);
    return aux;
}

Fecha &Fecha::operator--()
{
    *this += (-1);
    return *this;
}

bool operator<(const Fecha &fecha1, const Fecha &fecha2)
{
    bool valor = false;
    if (fecha1.anno() < fecha2.anno())
        valor = true;
    else if (fecha1.anno() == fecha2.anno())
    {
        if (fecha1.mes() < fecha2.mes())
            valor = true;
        else if (fecha1.mes() == fecha2.mes())
        {
            if (fecha1.dia() < fecha2.dia())
                valor = true;
        }
    }
    return valor;
}

bool operator!=(const Fecha &fecha1, const Fecha &fecha2)
{
    return !(fecha1 == fecha2);
}

bool operator<=(const Fecha &fecha1, const Fecha &fecha2)
{
    return !(fecha2 < fecha1);
}

bool operator>(const Fecha &fecha1, const Fecha &fecha2)
{
    return fecha2 < fecha1;
}

bool operator>=(const Fecha &fecha1, const Fecha &fecha2)
{
    return !(fecha1 < fecha2);
}

//Operador de conversión a const char *.
Fecha::operator const char *() const
{
    setlocale(LC_ALL, ""); //Cambiamos toda la región local a la del ordenador.
    static char *cadenita = new char[80];
    std::tm descompuesto{0, 0, 0, d, m - 1, y - 1900};
    mktime(&descompuesto);
    strftime(cadenita, 80, "%A %e de %B de %Y", &descompuesto);
    return cadenita;
}

// Clase anidada Invalida que es la excepción lanzada cuando la fecha es inválida.
Fecha::Invalida::Invalida(const char *cadena) : info(new char[std::strlen(cadena) + 1])
{
    std::strcpy(info, cadena);
}

const char *Fecha::Invalida::por_que() const
{
    return info;
}
