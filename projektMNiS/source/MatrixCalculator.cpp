#include <iostream>
using namespace std;


class Matrix
{
private:
    int m_matrixSize = 0;
    //float m_matrixResult[][];
public:
    void getMatrixSize() {
        cout << "Please enter the size of square matrices: ";
        cin >> m_matrixSize;
        cout << endl;
    }
    
    void fillMatrix(char matrixName) {
        cout << "Enter data for matrix " << matrixName << endl;
        
        for (int i = 0; i < m_matrixSize; i++) {
          for (int j = 0; j < m_matrixSize; j++) {
            cout << "row " << i + 1 << ", column " << j + 1 << ":" << endl;
            //cin >> [i][j];
          }
        }
        cout << endl;
    }
};

int main() {
  Matrix resultMatrix;
  resultMatrix.getMatrixSize();
  resultMatrix.fillMatrix('A');

  cin.get();
}