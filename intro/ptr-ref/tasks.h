#pragma once



namespace NPointers {
    void Increment(int *x);
    int Multiply(int first, int second, bool *isOverflow);
    int ScalarProduct(const int a[], const int b[], int size);
    int SizeOfMaximumSquareOfCrosses(const char *a, int width, int height);
    long long int* MultiplyToLongLong(int first, int second);
    /* To implement:
    Increment
    Multiply
    ScalarProduct
    SizeOfMaximumSquareOfCrosses
    MultiplyToLongLong
    */
}

namespace NReferences {
    void MultiplyInplace(int &a, int b);
    int CompareArraysByAverage(const int a[], int size, int b[5]);
    /* To implement:
    MultiplyInplace
    CompareArraysByAverage
    */
}
