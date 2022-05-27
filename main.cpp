#include <iostream>
#include "matrix.h"
#include "vector.h"
#include <fstream>

using namespace std;


int main()
{
    cout << "Erste Stelle!";
    ifstream fin, fin2;
    cout << "Stelle erreicht!" ;
    fin.open("test_5x5.txt");
    cout << "Stelle 2 erreicht!";
    size_t n1, n2;

    fin >> n1 >> n2;
    mapra::Matrix A(n1, n2);
    fin >> A;

    fin2.open("test_5x1.txt");

    fin2 >> n1 >> n2;
    mapra::Vector B = mapra::Vector(n1);
    fin2 >> B;


    cout << "Die gegebene Matrix A:" << endl << A << endl;
    cout << "Die gegebene Matrix A:" << endl << B << endl;
    cout << "Die  Matrix A*B" << endl << A*B << endl;

}
