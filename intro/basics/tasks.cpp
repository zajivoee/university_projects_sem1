#include "tasks.h"

#include <cmath>

int NOuter::NInner::DoSomething(int lhs, int rhs) {
    return lhs + rhs;
}

int NOuter::DoSomething(int lhs, int rhs) {
    return lhs - rhs;
}

int NOverload::ProcessTwoArgs(int lhs, int rhs) {
    return lhs + rhs;
}

char NOverload::ProcessTwoArgs(char lhs, char rhs) {
    if (lhs-rhs >= 0) {
        return lhs;
    } 
    else {
        return rhs;
    }
}

int NOverload::ProcessTwoArgs(int lhs, char rhs) {
    return lhs - rhs;
}

unsigned int NOverflow::WithOverflow(int lhs, int rhs) {
    return lhs + rhs;
}

uint64_t NOverflow::WithOverflow(int64_t lhs, int64_t rhs) {
    return lhs - rhs;
}

int NLoop::SumInRange(const int lhs, const int rhs) {
    int current = lhs;
    int result = 0;
    while (current!=rhs) {
        result += current;
        ++current;
    }
    return result;
}

int NLoop::CountFixedBitsInRange(const int from, const int to, const int bitsCnt) {
    int count = 0;
    for (int current = from + 1; current < to; ++current) {
        int sum_of_digits = 0, x = current;

        while (x > 0) {
            sum_of_digits += x & 1;
            x >>= 1;
        }
        if (sum_of_digits == bitsCnt) {
            ++count;
        }
    }
    return count;      
}

double NMath::ComputeMathFormula(const double arg) {
    return fabs((sin(arg) / 2 + cos(arg)) * (sin(arg) / 2 + cos(arg)) + tan(arg) * atan(arg));
}

bool NMath::IsPositive(int arg) {
    return arg > 0;
}

int NRecursion::CalculateFibonacci(const int arg) {
    if (arg <= 2)  {
        return 1;
    }
    return NRecursion::CalculateFibonacci(arg - 1) + NRecursion::CalculateFibonacci(arg - 2);
}
