#include <iostream>
#include "matrix.h"
#include "vector.h"
#include <fstream>

using namespace std;


int main()
{
    ifstream fin;
    fin.open("test_5x5.txt");
    int n;

    fin >> n;
    mapra::Matrix A = mapra::Matrix(n, n);
    fin >> A;


    cout << "Die gegebene Matrix A:" << endl << A << endl;
    cout << "Die  Matrix A^2:" << endl << A*A << endl;

}
