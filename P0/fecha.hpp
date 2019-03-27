#ifndef FECHA_HPP
#define FECHA_HPP


/*
  Fecha.hpp
  Autor: José Miguel Aragón Jurado
  Descripción: Fichero de cabecera que contiene la clase Fecha, que modula una fecha en español y sus correspondientes métodos para manejarla.
*/

class Fecha
{
public:

  //Constructores de la clase Fecha.
  explicit Fecha(int dia=0, int mes=0, int anno=0);
  Fecha(const char *cadena);

  //Métodos observadores de la clase.
  int dia() const;
  int mes() const;
  int anno() const;

  //Operadores de asignación con suma y resta.
  Fecha &operator+=(int dia);
  Fecha &operator-=(int dia);

  //Preincremento y postincremento respectivamente.
  Fecha& operator++();
  Fecha& operator++(int);

  //Predecremento y postdecremento respectivamente.
  Fecha& operator--();
  Fecha& operator--(int);
  
  //Operador de conversión implícita a const char*.
  operator const char*()const;

  //Operador suma de una Fecha con un entero.
  Fecha operator +(int dia)const;

  //Operador resta de una Fecha con un entero.
  Fecha operator -(int dia)const;

  
  //Operadores lógicos.

  friend bool operator==(const Fecha &fecha1, const Fecha &fecha2);
  friend bool operator<(const Fecha &fecha1, const Fecha &fecha2);
  

  //Constantes estáticas de la clase.
  static const int AnnoMinimo;
  static const int AnnoMaximo;

  //Clase anidada Invalida que es el tipo de las excepciones.
  class Invalida
  {
  public:
    Invalida(const char *cadena);
    const char *por_que() const;

  private:
    char *info;
  };

private:
  int d,m,y;
  void comprobar();
};

bool operator>(const Fecha &fecha1, const Fecha &fecha2);
bool operator!=(const Fecha &fecha1, const Fecha &fecha2);
bool operator<=(const Fecha &fecha1, const Fecha &fecha2);
bool operator>=(const Fecha &fecha1, const Fecha &fecha2);


inline bool operator==(const Fecha &fecha1, const Fecha &fecha2)
{
  return (fecha1.d == fecha2.d && fecha1.m == fecha2.m && fecha1.y == fecha2.y);
}



#endif //FECHA_HPP