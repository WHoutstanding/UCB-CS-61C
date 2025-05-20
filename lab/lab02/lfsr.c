#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg)
{
    /* YOUR CODE HERE */
    uint16_t x = *reg;
    uint16_t x0 = 0, x2 = 2, x3 = 3, x5 = 5, x15 = 15;

    uint16_t y0 = (x & (1 << x0)) >> x0;
    uint16_t y2 = (x & (1 << x2)) >> x2;
    uint16_t y3 = (x & (1 << x3)) >> x3;
    uint16_t y5 = (x & (1 << x5)) >> x5;

    uint16_t v = y0 ^ y2 ^ y3 ^ y5;

    *reg >>= 1;
    *reg = (*reg & ~(1 << x15)) | v << x15;
}
