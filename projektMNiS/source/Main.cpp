#include <iostream>
using namespace std;

int liczba;

class matrix
{
public:
  int kolumny = 0;
  int wiersze = 0;
  double** tablica = nullptr;

  matrix(int wiersz, int kolumna) : wiersze(wiersz), kolumny(kolumna) {
    tablica = new double* [wiersz];
    for (int j = 0; j < wiersz; j++) {
      tablica[j] = new double[kolumny];
    }

    for (int i = 0; i < wiersz; i++) {
      for (int j = 0; j < kolumna; j++) {
        tablica[i][j] = 0;
      }
    }
  }
  
  matrix() : wiersze(liczba), kolumny(liczba) {
    tablica = new double* [wiersze];
    for (int j = 0; j < wiersze; j++) {
      tablica[j] = new double[kolumny];
    }

    for (int i = 0; i < wiersze; i++) {
      for (int j = 0; j < kolumny; j++) {
        tablica[i][j] = 0;
      }
    }
  }
  
  void wprowadz_dane(char matrixName)
  {
    cout << "Wprowadz dane macierzy " << matrixName << endl;
    for (int i = 0; i < wiersze; i++) {
      for (int j = 0; j < kolumny; j++) {
        cout << "wiersz " << i + 1 << ", kolumna " << j + 1 << ":" << endl;
        cin >> tablica[i][j];
      }
    }
    cout << endl;
  }

  friend void operator+=(matrix& obj, matrix obj2);
  friend void operator-=(matrix& obj, matrix obj2);
  friend void operator*=(matrix& obj, matrix obj2);
  friend void operator/=(matrix& obj, matrix obj2);

  friend void operator+(matrix& obj, double wartosc);
  friend void operator-(matrix& obj, double wartosc);
  friend void operator/(matrix& obj, double wartosc);
  friend void operator*(matrix& obj, double wartosc);

  friend void operator++(matrix& obj);
  friend void operator++(matrix& obj, int);
  friend void operator--(matrix& obj);
  friend void operator--(matrix& obj, int);

};


void operator+=(matrix& obj, matrix obj2)
{

  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j] += obj2.tablica[i][j];
    }
  }
}
void operator-=(matrix& obj, matrix obj2)
{

  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j] -= obj2.tablica[i][j];
    }
  }
}
void operator*=(matrix& obj, matrix obj2)
{

  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j] *= obj2.tablica[i][j];
    }
  }
}
void operator/=(matrix& obj, matrix obj2)
{

  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j] /= obj2.tablica[i][j];
    }
  }
}

matrix operator+(matrix obj, matrix obj2)
{
  matrix Z;
  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      Z.tablica[i][j] = obj.tablica[i][j] + obj2.tablica[i][j];
    }
  }

  return Z;
}
matrix operator-(matrix obj, matrix obj2)
{
  matrix Z;
  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      Z.tablica[i][j] = obj.tablica[i][j] - obj2.tablica[i][j];
    }
  }

  return Z;
}
matrix operator*(matrix obj, matrix obj2)
{
  matrix Z;
  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      Z.tablica[i][j] = obj.tablica[i][j] * obj2.tablica[i][j];
    }
  }

  return Z;
}
matrix operator/(matrix obj, matrix obj2)
{
  matrix Z;
  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      Z.tablica[i][j] = obj.tablica[i][j] / obj2.tablica[i][j];
    }
  }

  return Z;
}


void operator+(matrix& obj, double wartosc)
{

  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j] += wartosc;
    }
  }
}
void operator-(matrix& obj, double wartosc)
{

  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j] -= wartosc;
    }
  }
}
void operator/(matrix& obj, double wartosc)
{

  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j] /= wartosc;
    }
  }
}
void operator*(matrix& obj, double wartosc)
{

  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j] *= wartosc;
    }
  }
}

void operator++(matrix& obj, int)
{
  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j]++;
    }
  }
}
void operator--(matrix& obj, int)
{
  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      obj.tablica[i][j]--;
    }
  }
}
void operator++(matrix& obj)
{
  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      ++obj.tablica[i][j];
    }
  }
}
void operator--(matrix& obj)
{
  for (int i = 0; i < liczba; i++) {
    for (int j = 0; j < liczba; j++) {
      --obj.tablica[i][j];
    }
  }
}

ostream& operator<< (ostream& out, matrix& obj)
{
  out << endl;
  for (int i = 0; i < (obj.kolumny) + 2; i++) {
    out << "_ ";
  }

  for (int i = 0; i < obj.wiersze; i++) {
    out << endl << "| ";
    for (int j = 0; j < obj.kolumny; j++) {
      out << obj.tablica[i][j] << " ";
    }
    out << "|";
  }
  out << endl;
  for (int i = 0; i < (obj.kolumny) + 2; i++) {
    out << "- ";
  }
  out << endl;
  return out;
}


int main()
{
  cout << "Wprowadz liczbe wierszy i kolumn: ";
  cin >> liczba;
  cout << endl;
  matrix a{ liczba, liczba };
  matrix b{ liczba, liczba };
  a.wprowadz_dane('A');
  b.wprowadz_dane('B');

  matrix z;
  z = a + b;
  cout << z;
  a + 2;
  cout << a;

  return 0;
}