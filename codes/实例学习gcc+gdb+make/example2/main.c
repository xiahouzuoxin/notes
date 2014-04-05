#include <stdio.h>
#include "add.h"
#include "sub.h"

int main(void)
{
    int a = 2;
    int b = 3;
    int c = add(a,b);
    int d = sub(a,b);

#ifdef _DEBUG
    printf("c=%d\n", c);
    printf("d=%d\n", d);
#endif
    return 0;
}
