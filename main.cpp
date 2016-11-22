#include "matrix.h"
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

NumMatrix getMatrix()
{
    string s, sum;
    getline(cin, s);
    unsigned width = 0, height = 0;
    while(s.length())
    {
        istringstream is;
        is.str(s);
        unsigned cwidth = 0, dummy;
        while(is >> dummy)
            ++cwidth;
        if(!cwidth)
            break;
        if(width && width != cwidth)
        {
            cout << "Incorrect matrix\n";
            terminate();
        }
        width = cwidth;
        ++height;
        sum += s + ' ';
        getline(cin, s);
    }
    NumMatrix m(height, width);
    istringstream is;
    is.str(sum);
    is >> m;
    return m;
}

void f_rank()
{
    NumMatrix a = getMatrix();
    cout << "Rank: " << a.rank() << endl;
}

void f_det()
{
    NumMatrix a = getMatrix();
    cout << "Determinant: " << a.det() << endl;
}

void f_inv()
{
    NumMatrix a = getMatrix();
    cout << "Inverted matrix:\n" << a.inverted();
}

void f_mul()
{
    NumMatrix a = getMatrix();
    NumMatrix b = getMatrix();
    cout << "Product:\n" << (a * b);
}

void f_solve()
{
    NumMatrix a = getMatrix();
    unsigned sz = a.height();
    if(!sz || a.width() != sz + 1)
    {
        cout << "Invalid matrix\n";
        return;
    }
    NumMatrix sys = a.submatrix(0, 0, sz - 1, sz - 1);
    NumMatrix right = a.submatrix(0, sz, sz - 1, sz);
    sys.inverseExt(right);
    cout << "Solution:";
    for (unsigned i = 0; i < sz; ++i)
    {
        cout << ' ' << right[i][0];
    }
    cout << endl;

}

void f_pow()
{
    NumMatrix a = getMatrix();
    if(a.width() != a.height())
    {
        cout << "This can be done only for square matrices" << endl;
        return;
    }
    cout << "Power: ";
    unsigned p;
    cin >> p;
    NumMatrix t = NumMatrix::identity(a.width());
    while(p)
    {
        if(p & 1)
            t *= a;
        p >>= 1;
        a *= a;
    }
    cout << "Result:\n" << t;
}

map<string, void (*)()> ops = {{"rank",  f_rank},
                               {"det",   f_det},
                               {"inv",   f_inv},
                               {"mul",   f_mul},
                               {"solve", f_solve},
                               {"pow",   f_pow}};

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        cout << "Usage: matrix OPERATION\n\n";
        cout << "Operations: ";
        int t = 0;
        for (auto &i : ops)
        {
            cout << (t++ ? ", " : "") << i.first;
        }
        cout << endl << endl;
        return 0;
    }
    if (ops[argv[1]])
    {
        ops[argv[1]]();
    }
    else
    {
        cout << "Invalid operation" << endl;
        return 1;
    }

    return 0;
}