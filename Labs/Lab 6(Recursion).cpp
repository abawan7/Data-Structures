#include "iostream"

using namespace std;

int isMember(int arr[], int size, int x) {

    size--;
    if (size < 0) {
        return -1;
    }
    if (arr[size] == x) {
        return size;
    }
    return isMember(arr, size, x);

}

int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * (factorial(n - 1));
}

int sumOfDigit(int n) {
    if (n == 0)
        return 0;
    return (n % 10 + sumOfDigit(n / 10));
}

int reverse(float arr[], int start, int end) {
    int temp;


    if (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        reverse(arr, start + 1, end - 1);

    }
    return 0;
}

void print(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}

bool strcmp(char ArrayA[], int SizeA, char ArrayB[], int SizeB) {

    if (SizeA <= 1 && SizeB <= 1)
        return true;
    else if (ArrayA[0] != ArrayA[1] && ArrayB[0] != ArrayB[1])
        return false;

    return strcmp(ArrayA + 1, SizeA - 1, ArrayB + 1, SizeB - 1);

}

int main() {
    int x, f, p;
    int arr[] = {17, 15, 11, 8, 13, 19};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Enter Number: ";
    cin >> x;
    int s = isMember(arr, size, x);
    if (s != -1) {
        cout << x << " is at " << s << " index" << endl;
    } else {
        cout << x << " is not in array" << endl;
    }
    cout << "Enter Number for Factorial: ";
    cin >> f;
    int fac = factorial(f);
    cout << "Factorial of 5 is = " << fac << endl;

    cout << "Enter Number for Sum of Digits: ";
    cin >> p;
    int sod = sumOfDigit(p);
    cout << "Sum of Digit of 795 is = " << sod << endl;

    float arr1[] = {1.0, 5.4, 0.85, 91.2, 6.5};
    size = sizeof(arr1) / sizeof(arr1[0]);
    reverse(arr1, 0, size - 1);
    print(arr1, size);

    char str1[100];
    char str2[100];
    cout << " String 1: ";
    cin >> str1;
    cout << " String 2: ";
    cin >> str2;
    cin.ignore();
    if (!strcmp(str1, sizeof(str1), str2, sizeof(str2))){
        cout << "String 1 is equal to String 2" << endl;
    }
    else{
        cout << "Not Equal" <<endl;
    }
}
