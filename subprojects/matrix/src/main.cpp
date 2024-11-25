#include "matrix.h"
#include "unlmatrix.h"

#include <iostream>
#include <cassert>
#include <unordered_map>

using std::unordered_map;

using std::cout;
using std::endl;

void textExampleFunc()
{
    proxymatrix::Matrix<int, -1, 3> matrix;
    assert(matrix.size() == 0);

    auto a = matrix[0][0][0];
    assert(a == -1);
    assert(matrix.size() == 0);

    matrix[100][100][20] = 314;
    assert(matrix.size() == 1);
    assert(matrix[100][100][20] == 314);

    for(const auto &c : matrix)
    {
        size_t x = 0, y = 0, z = 0;
        int v = 0;
        std::tie(x, y, z, v) = c;
        cout << "x = " << x << "; y = " << y << "; v = " << v;
    }
}

void testControlFunc()
{
    proxymatrix::Matrix<int, 0> matrix;
    for(uint8_t i = 0; i < 10; i++)
    {
        matrix[i][i] = i;
        matrix[i][9-i] = 9 - i;
    }

    for(uint8_t i = 1; i < 9; i++)
    {
        auto row = matrix[i];
        for(uint8_t j = 1; j < 9; j++)
        {
            cout << std::dec << matrix[i][j] << " ";
        }

        cout << endl;
    }

    cout << "Matrix size " << matrix.size() << endl;

    std::size_t x = 0, y = 0, v = 0;
    for( const auto &c : matrix)
    {
        std::tie(x, y, v) = c;
        cout << x << " | " << y << " | " << v << endl;
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    testControlFunc();

    return 0;
}

// int main(int argc, char **argv)
// {
//     cout << "Hello world from Matrix task" << endl;

//     matrix::Matrix<int, -1> matrix;
//     assert(matrix.size() == 0);
//     auto a = matrix[0][0];
//     assert(a == -1);
//     assert(matrix.size() == 0);

//     matrix[100][100] = 314;
//     assert(matrix.size() == 1);
//     assert(matrix[100][100] == 314);

//     for(auto &c : matrix)
//     {
//         int x = 0, y = 0, v = 0;
//         //std::tie(x, y, v) = c;
//         cout << x << y << v << endl;
//     }

//     matrix::Matrix<int, -1, 1> vec;
//     vec[1] = 5;
//     vec[2] = 6;
//     int ret = 0;
//     for(auto &item : vec)
//     {
//         int x = 0, v = 0;
//         std::tie(x, v) = item;
//     }

//     cout << "ret = " << ret;

//     return 0;
// }
