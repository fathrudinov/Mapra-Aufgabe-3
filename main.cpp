#include <iostream>
#include "matrix.h"
#include "vector.h"
#include "unit_test.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        if (std::stoi(argv[1]) == 1)
        {
            vector_tests Test = vector_tests();
            Test.Summary();
        }
        if (std::stoi(argv[1]) == 2)
        {
            matrix_tests Test = matrix_tests();
            Test.Summary();
        }
        if (std::stoi(argv[1]) == 3)
        {
            power_series_tests();
        }
    }
    return 0;
}
