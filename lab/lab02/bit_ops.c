#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n)
{
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns
    // 0 or 1)
    // int mask = 1 << n;
    // int result = (x & mask) >> n;
    return (x & (1 << n)) >> n;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned *x,
             unsigned n,
             unsigned v)
{
    // YOUR CODE HERE
    // int cleared = x & ~(1 << n);
    // 构造要设置的值，v 左移 n 位
    // int value_to_set = v << n;
    // 通过或操作将清零后的数和要设置的值合并
    // return cleared | value_to_set;
    *x = (*x & ~(1 << n)) | v << n;
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned *x,
              unsigned n)
{
    // YOUR CODE HERE
    // int mask = 1 << n;
    // 使用按位异或操作翻转第 n 位
    // return x ^ mask;
    *x = *x ^ (1 << n);
}
