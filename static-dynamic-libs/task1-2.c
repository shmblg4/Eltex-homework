#include "calc.h"
#include "io.h"
#include "helper.h"

int main()
{
    int a = 6;
    int b = 5;

    if (validate_input(a, b))
    {
        int result = fact(a);
        print_result(result);
        result = fact(b);
        print_result(result);
    }
    else
    {
        printf("Invalid input\n");
    }

    return 0;
}