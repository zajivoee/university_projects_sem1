#include "tasks.h"
#include <algorithm>

void NPointers::Increment(int *x) {
    ++(*x);
}
int NPointers::Multiply(int a, int b, bool *isOverflow) {
    *isOverflow = (double)a > (double)(2147483647 / b);
    return a * b;
}
int NPointers::ScalarProduct(const int a[], const int b[], int size) {

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}
int NPointers::SizeOfMaximumSquareOfCrosses(const char *matrix, int rows, int cols) {
    int max_square_size = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i * cols + j] == '+') {
                bool flag = true;
                int size = 0;
                while (flag && size < std::min(rows - i, cols - j)) {
                    for (int k = 0; k <= size; k++) {
                        for (int m = 0; m <= size; m++) {
                            if (matrix[(k + i) * cols + m + j] != '+') {
                                flag = false;
                                break;
                            }
                        }
                    }
                    size++;
                }
                max_square_size = std::max(max_square_size, size);
            }
        }
    }
    return max_square_size;
//    return 2;
}
long long int* NPointers::MultiplyToLongLong(int a, int b) {
    long long int *product = new long long int ((long long) a * (long long) b);
    return product;
}
void NReferences::MultiplyInplace(int &a, int b) {
    a *= b;
}
int NReferences::CompareArraysByAverage(const int a[], int size, int b[5]) {
    int secondSize = 5;
    int sumFirst = 0;
    for (int i = 0; i < size; i++) {
        sumFirst += a[i];
    }
    int sumSecond = 0;
    for (int j = 0; j < secondSize; j++) {
        sumSecond += b[j];
    }
    float avFirst = (float)sumFirst/size;
    float avSecond = (float)sumSecond/secondSize;
    if (avFirst > avSecond) {
        return 1;
    }
    else if (avFirst == avSecond) {
        return 0;
    }
    else {
        return -1;
    }
}