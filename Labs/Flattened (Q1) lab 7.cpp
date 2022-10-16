#include <iostream>
using namespace std;

void Flattened(int a [5][5], int r[25], int i, int j, int k)
{
    if (i < 5)
    {
        if (a[i][j] != 0)
        {
            r[k] = a[i][j];
            k++;
            j++;
        }
        else
        {
            j = 0;
            i++;
        }
        Flattened(a, r, i, j, k);
    }
}

int main()
{
    int array[5][5] = {{1, 2,  0,  0, 0},
                       {1, 2,  3,  4, 0},
                       {5, 67, 21, 0, 0},
                       {0, 0,  0,  0, 0},
                       {4, 3,  1,  0, 0} };
    int array2[25];
    for (int i = 0; i < 25; i++)
        array2[i] = 0;
    Flattened(array, array2, 0, 0, 0);
    for (int i = 0; array2[i] != 0; i++)
    {
        cout << array2[i] << " ";
    }
    cout << endl << endl;

    return 0;
}
