#include <iostream>
using namespace std;

void Product(int **A, int rows1, int cols1, int **B, int rows2, int cols2, int **product)
{
    static int i = 0, j = 0, k = 0;
    if (i >= rows1)
    {
        return;
    }
    if (j < cols2)
    {
        if (k < cols1)
        {
            product[i][j] = product[i][j] + (A[i][k] * B[k][j]);
            k++;
            Product(A, rows1, cols1, B, rows2, cols2, product);
        }
        k = 0;
        j++;
        Product(A, rows1, cols1, B, rows2, cols2, product);
    }
    j = 0;
    i++;
    Product(A, rows1, cols1, B, rows2, cols2, product);
}

int main()
{

    int **product, **A, **B, rows1 = 0, cols1 = 0, rows2 = 0, cols2 = 0;
    cout << "Enter rows for matrix 1 : "; cin >> rows1;
    cout << "Enter columns for matrix 1 : "; cin >> cols1;
    A = new int*[rows1];
    cout << "Enter data for matrix 1 : ";
    for (int i = 0; i < rows1; i++)
    {
        A[i] = new int[cols1];
        for (int j = 0; j < cols1; j++)
        {
            cin >> A[i][j];
        }
    }
    cout << "Enter rows for matrix 2 : "; cin >> rows2;
    cout << "Enter columns for matrix 2 : "; cin >> cols2;
    B = new int*[rows2];
    cout << "Enter data for matrix 2 : ";
    for (int i = 0; i < rows2; i++)
    {
        B[i] = new int[cols2];
        for (int j = 0; j < cols2; j++)
        {
            cin >> B[i][j];
        }
    }
    product = new int*[rows1];
    for (int i = 0; i < rows1; i++)
    {
        product[i] = new int[cols2];
        for (int j = 0; j < cols1; j++)
        {
            product[i][j] = 0;
        }
    }
    cout << "\nMatrix 1 :" << endl;
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "\nMatrix 2 :" << endl;
    for (int i = 0; i < rows2; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            cout << B[i][j] << "\t";
        }
        cout << endl;
    }
    if (cols1 == rows2)
    {
        Product(A, rows1, cols1, B, rows2, cols2, product);
        cout << "\nProduct of matrices :" << endl;
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols2; j++)
            {
                cout << product[i][j] << endl;
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Not Possible" << endl;
    }
    return 0;
}
