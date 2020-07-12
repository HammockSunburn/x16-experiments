#include <stdio.h>
#include <stdlib.h>

extern const char text[];

int main()
{
    printf("%s\n", text);
    return EXIT_SUCCESS;
}