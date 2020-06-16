#include <iostream>
#include <cmath>
using namespace std;

int rozmiarMacierzy = 0;
int matrixNum = 0;
double userNum = 0.0;
char operationSymbol;

class matrix
{
private:
    int kolumny = 0;
    int wiersze = 0;
    double** tablica;
    double wyznacznik = 0;
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
        cout << "[ Wprowadz dane macierzy " << matrixName << " ]" << endl;

        for (int i = 0; i < wiersze; i++) {
            for (int j = 0; j < kolumny; j++) {
                cout << "wiersz " << i + 1 << ", kolumna " << j + 1 << ":" << endl;
                cin >> tablica[i][j];
            }
        }
    }
    
    // funkcja wyliczajaca wyznacznik macierzy ( dziala tylko dla macierzy max 3x3 :( )
    double determinant() {

        if (rozmiarMacierzy == 2) {
            wyznacznik = tablica[0][0];
        }
        else if (rozmiarMacierzy == 2) {
            wyznacznik = ((tablica[0][0] * tablica[1][1]) - (tablica[1][0] * tablica[0][1]));
        }
        else if (rozmiarMacierzy == 3) {
            wyznacznik = (tablica[0][0] * (tablica[1][1] * tablica[2][2] - tablica[1][2] * tablica[2][1])) - (tablica[0][1] * (tablica[1][0] * tablica[2][2] - tablica[1][2] * tablica[2][0])) + (tablica[0][2] * (tablica[1][0] * tablica[2][1] - tablica[1][1] * tablica[2][0]));
        }
        else {
            cout << "[det(A) ERROR]" << endl;
        }
        return wyznacznik;
    };

    
/*
    void transpozycja() {
        double Z[rozmiarMacierzy][rozmiarMacierzy];
        for (int i = 0; i < rozmiarMacierzy; ++i) {
            for (int j = 0; j < rozmiarMacierzy; ++j) {
                Z[j][i] = tablica[i][j];
            }
        }
        for (int i = 0; i < rozmiarMacierzy; ++i) {
            for (int j = 0; j < rozmiarMacierzy; ++j) {
                tablica[i][j] = Z[i][j];
            }
        }
    }

    
    double determinant(int matrix[10][10], int n) {
        double det = 0;
        int submatrix[10][10];
        if (n == 2)
            return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
        else {
            for (int x = 0; x < n; x++) {
                int subi = 0;
                for (int i = 1; i < n; i++) {
                    int subj = 0;
                    for (int j = 0; j < n; j++) {
                        if (j == x)
                            continue;
                        submatrix[subi][subj] = matrix[i][j];
                        subj++;
                    }
                    subi++;
                }
                det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
            }
        }
        return det;
    };
*/
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

// dzialania na macierzach ze skalarami np. A + 2; A * 5;
void operator+(matrix& obj, double wartosc) {
    for (int i = 0; i < rozmiarMacierzy; i++) {
        obj.tablica[i][i] += wartosc;
    }
}
void operator-(matrix& obj, double wartosc) {
    for (int i = 0; i < rozmiarMacierzy; i++) {
        obj.tablica[i][i] -= wartosc;
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
    bool symbolError = true;
    while (symbolError == true)
    {
        cout << ">>> Na ilu macierzach chcesz wykonywac dzialania? [1/2]: ";
        cin >> matrixNum;

        if (matrixNum == 1 || matrixNum == 2) {
            symbolError = false;
            break;
        } 
        else {
            cout << "[NIEPRAWIDLOWA WARTOSC!]";
            cout << endl;
        }     
    }

    symbolError = true;
    while (symbolError == true)
    {
        cout << ">>> Wprowadz rozmiar macierzy kwadratowej/ych (1, 10): ";
        cin >> rozmiarMacierzy;

        if (rozmiarMacierzy >= 1 && rozmiarMacierzy <= 10) {
            symbolError = false;
            break;
        }
        else {
            cout << "[NIEPRAWIDLOWA WARTOSC!]";
            cout << endl;
        }
    }
   
    symbolError = true;
    while (symbolError == true) {
        if (matrixNum == 1) {
            cout << ">>> Wprowadz symbol operacji matematycznej ( +, -, *, w ): ";
            cin >> operationSymbol;

            if (operationSymbol == '+' || operationSymbol == '-' || operationSymbol == '*' || operationSymbol == 'w') {
                
                // funkcja pobierajaca od uzytkownika liczbe do operacji na macierzy A
                cout << ">>> Wprowadz liczbe uzywana do operacji na macierzy: ";
                cin >> userNum;
                
                symbolError = false;
                break;
            }
            else {
                cout << "[NIEPRAWIDLOWY SYMBOL!]";
                cout << endl;
            }
        } 
        else if (matrixNum == 2) {
            {
                cout << ">>> Wprowadz symbol operacji matematycznej ( +, -, * ): ";
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
    }
};

 // funkcja pozwalajaca na obliczenia na dwoch macierzach
void operationOnTwoMatrices() {
    matrix A;
    A.fillMatrix('A');

    matrix B;
    B.fillMatrix('B');

    matrix C;

    // funkcja wyswietlajaca wyniki operacji matematycznej zgodnie z zadanym symbolem
    switch (operationSymbol)
    {
        default:
            cout << endl;
            cout << "[NIEPRAWIDLOWY SYMBOL!]";
            break;
        case '+':
            cout << endl;
            cout << "A =" << A;
            cout << "B = " << B;
            cout << "A + B =" << A + B;
            break;
        case '-':
            cout << endl;
            cout << "A =" << A;
            cout << "B = " << B;
            cout << endl;
            cout << "A - B =" << A - B;
            cout << "B - A =" << B - A;
            break;
        case '*':
            cout << endl;
            cout << "A =" << A;
            cout << "B = " << B;
            cout << endl;
            C = A * B;
            cout << "A * B =" << C;
            C = B * A;
            cout << "B * A =" << C;
            break;
    }
};

 // funkcja pozwalajac na operacje na jednej macierzy
void operationOnOneMatrix() {
    matrix A;
    A.fillMatrix('A');

    matrix C;

    switch (operationSymbol)
    {
    default:
        cout << endl;
        cout << "[NIEPRAWIDLOWY SYMBOL!]";
        break;
    case '+':
        cout << endl;
        cout << "A =" << A << endl;
        cout << "Liczba = " << userNum << endl << endl;
        A + userNum;
        cout << "A + " << userNum << " =" << A << endl;
        break;
    case '-':
        cout << endl;
        cout << "A =" << A << endl;
        cout << "Liczba = " << userNum << endl << endl;
        A - userNum;
        cout << "A - " << userNum << " =" << A << endl;
        break;
    case '*':
        cout << endl;
        cout << "A =" << A << endl;
        cout << "Liczba = " << userNum << endl << endl;
        A * userNum;
        cout << "A * " << userNum << " =" << A << endl;
        break;
/*
    case '^':
        
        break;
*/
    case 'w':
        cout << endl;
        cout << "A =" << A << endl;
        cout << "Wyznacznik A = " << A.determinant();
        cout << endl;

        break;
    }
}

int main()
{
    // petla glownego programu

    char continueProgram = 'Y';
    while (continueProgram == 'Y' || continueProgram == 'y') {
        getMatrixData();
        
        if (matrixNum == 1) {
            operationOnOneMatrix();
        }
        else if (matrixNum == 2) {
            operationOnTwoMatrices();
        }

        cout << endl;

        cout << "Czy chcesz ponownie uzyc kalkulatora? [Y/N]: ";
        cin >> continueProgram;

        cout << endl;
    }
};