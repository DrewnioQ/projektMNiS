#include <iostream>
#include <cmath>
using namespace std;

int rozmiarMacierzy = 0;
char operationSymbol;

class matrix
{
private:
    int kolumny = 0;
    int wiersze = 0;
    double** tablica;
public:
    // konstruktor macierzy
    matrix() : wiersze(rozmiarMacierzy), kolumny(rozmiarMacierzy) {
        tablica = new double* [wiersze]; // tworzy liczbe wierszy
        for (int j = 0; j < wiersze; j++) { // tworzy do kazdego wiersza liczbe kolumn
            tablica[j] = new double [kolumny];
        }
        // petla ktora domyslnie przypisuje wartosc 0 do kazej komorki tablicy
        for (int i = 0; i < wiersze; i++) {
            for (int j = 0; j < kolumny; j++) {
                tablica[i][j] = 0;
            }
        }
    }
    
    // funkcja wpisujaca zadane wartosci macierzy do tablic
    void fillMatrix(char matrixName) {
        cout << endl;
        cout << "Wprowadz dane macierzy " << matrixName << endl;

        for (int i = 0; i < wiersze; i++) {
            for (int j = 0; j < kolumny; j++) {
                cout << "wiersz " << i + 1 << ", kolumna " << j + 1 << ":" << endl;
                cin >> tablica[i][j];
            }
        }
    }

    friend ostream& operator<< (ostream& out, matrix obj);

    friend void operator+=(matrix& obj, const matrix& obj2);
    friend void operator-=(matrix& obj, const matrix& obj2);
    friend void operator*=(matrix& obj, const matrix& obj2);

    friend matrix operator+(const matrix& obj, const matrix& obj2);
    friend matrix operator-(const matrix& obj, const matrix& obj2);
    friend matrix operator*(const matrix& obj, const matrix& obj2);

    friend void operator+(matrix& obj, double wartosc);
    friend void operator-(matrix& obj, double wartosc);
    friend void operator*(matrix& obj, double wartosc);
    //friend void operator/(matrix& obj, double wartosc);

    friend void getMatrixData();
    friend void displayMatrixResult(matrix& A, matrix& B, matrix& C);
};

 // operatory przeladowania; do macierzy po lewej stronie jest dodawana macierz po prawej
 // macierz po prawej sie nie zmienia, np. A -= B;
void operator-=(matrix& obj, const matrix& obj2)
{
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            obj.tablica[i][j] -= obj2.tablica[i][j];
        }
    }
}
void operator+=(matrix& obj, const matrix& obj2)
{
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            obj.tablica[i][j] += obj2.tablica[i][j];
        }
    }
}
void operator*=(matrix& obj, const matrix& obj2)
{
    matrix Z;
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            for (int k = 0; k < rozmiarMacierzy; k++) {
                Z.tablica[i][j] += obj.tablica[i][k] * obj2.tablica[k][j];
            }
        }
    }
    obj = Z;
}

// przeladowane operatory z returnem wiec musi byc trzecia macierz do ktorej cos jest zwracane jak C = A + B;
matrix operator+(const matrix& obj, const matrix& obj2)
{
    matrix Z;
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            Z.tablica[i][j] += obj.tablica[i][j] + obj2.tablica[i][j];
        }
    }
    return Z;
}
matrix operator-(const matrix& obj, const matrix& obj2)
{
    matrix Z;
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            Z.tablica[i][j] += obj.tablica[i][j] - obj2.tablica[i][j];
        }
    }
    return Z;
}
matrix operator*(const matrix& obj, const matrix& obj2)
{
    matrix Z;
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            for (int k = 0; k < rozmiarMacierzy; k++) {
                Z.tablica[i][j] += obj.tablica[i][k] * obj2.tablica[k][j];
            }
        }
    }
    return Z;
}

// dzialania na macierzach z skalarami np. A + 2; B * 5;
void operator+(matrix& obj, double wartosc) {
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            obj.tablica[i][j] += wartosc;
        }
    }
}
void operator-(matrix& obj, double wartosc) {
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            obj.tablica[i][j] -= wartosc;
        }
    }
}
void operator*(matrix& obj, double wartosc) {
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            obj.tablica[i][j] *= wartosc;
        }
    }
}
/*                                                          // nigdzie nie wystepuje pojecie dzielenia macierzy
void operator/(matrix& obj, double wartosc) {
    for (int i = 0; i < rozmiarMacierzy; i++) {
        for (int j = 0; j < rozmiarMacierzy; j++) {
            obj.tablica[i][j] /= wartosc;
        }
    }
}
*/

ostream& operator<< (ostream& out, matrix obj)
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

 // funkcja pozyskujaca dane o macierzach od uzytkownika oraz zadane operacje na macierzach
void getMatrixData() {
    cout << ">>> Wprowadz rozmiar macierzy kwadratowych (1, 2, 3, ...): ";
    cin >> rozmiarMacierzy;

    bool symbolError = true;
    while (symbolError == true) {
        cout << ">>> Wprowadz symbol operacji matematycznej (+, -, *): ";
        cin >> operationSymbol;
        
        if (operationSymbol == '+' || operationSymbol == '-' || operationSymbol == '*') {
            symbolError = false;
            break;
        }
        else {
            cout << "[NIEPRAWIDLOWY SYMBOL!]";
            cout << endl;
        }
    }
}

 // funkcja wyswietlajaca wyniki operacji matematycznej zgodnie z zadanym symbolem
void displayMatrixResult( matrix& A, matrix& B, matrix& C ) {
    switch (operationSymbol)
    {
    default:
        cout << endl;
        cout << "[NIEPRAWIDLOWY SYMBOL!]";
        break;
    case '+':
        C = A + B;
        cout << endl;
        cout << "A + B =" << A + B;
        break;
    case '-':
        cout << endl;
        cout << "A - B =" << A - B;
        cout << endl;
        cout << "B - A =" << B - A;
        break;
    case '*':
        C = A * B;
        cout << endl;
        cout << "A * B =" << C;
        C = B * A;
        cout << endl;
        cout << "B * A =" << C;
        break;
    }
}

int main()
{
     // petla glownego programu

    char continueProgram = 'Y';
    while (continueProgram == 'Y' || continueProgram == 'y') {
        getMatrixData();

        matrix A;
        A.fillMatrix('A');

        matrix B;
        B.fillMatrix('B');

        matrix C;

        displayMatrixResult(A, B, C);

        cout << "Do you want to calculate again? [Y/N]: ";
        cin >> continueProgram;
        cout << endl;
    }
};