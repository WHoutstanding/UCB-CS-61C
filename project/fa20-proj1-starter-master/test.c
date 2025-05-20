#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main()
{
    uint32_t rule = 0x1808;
    uint32_t shift_number = 3;
    rule >>= shift_number;
    int state = rule & 1;
    printf("%d\n", rule);
    printf("%d", state);

    return 0;
}