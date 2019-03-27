#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena
{
  public:
    explicit Cadena(unsigned n=0,char relleno=' ');
    Cadena(const Cadena& copia);
    Cadena(const char* caracteres);

    Cadena& operator = (const Cadena& copia);
    operator  const char*()const;

    Cadena& operator +=(const Cadena& copia);
    
    friend Cadena operator +(const Cadena& cad1, const Cadena& cad2);
    
    char& operator[](int i);
    char operator[](int i)const;

    char at(int i)const;
    char& at(int i);

    Cadena substr(int i,unsigned tam)const;


    friend bool operator==(const Cadena& cad1, const Cadena& cad2);
    friend bool operator<(const Cadena& cad1, const Cadena& cad2);
    

    unsigned length()const;
    
    ~Cadena();

  private:
    char *s_;
    unsigned tam_;
};

bool operator>(const Cadena& cad1, const Cadena& cad2);
bool operator!=(const Cadena& cad1, const Cadena& cad2);
bool operator<=(const Cadena& cad1, const Cadena& cad2);
bool operator>=(const Cadena& cad1, const Cadena& cad2);

#endif //CADENA_HPP_