#include "calc.h"

static int mul(int a, int b)
{
    return a * b;
}

int fact(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result = mul(result, i);
    }
    return result;
}