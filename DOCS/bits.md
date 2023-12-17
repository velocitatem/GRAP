# Bits Module
This module is used for bitwise operations. It has only 2 key operators for now, those being `rshift` and `lshift`.

Under this module is also a `bin` function, which converts a given value to binary. It takes one argument: a value. This function returns the binary representation of the given value.

## `rshift` / `>`
The `rshift` function is used to shift a value to the right by a given number of bits. It takes two arguments: a value and a number of bits. The value can be of any type. The number of bits must be an integer. This function returns the shifted value.

```grap
mem | save | (bin | "a" | "101")
(bits | > | (mem | get | "a"))
```

This would return 2, as 101 shifted to the right by 1 bit is 10, which is 2 in decimal.


## `lshift` / `<`
The `lshift` function is used to shift a value to the left by a given number of bits. It takes two arguments: a value and a number of bits. The value can be of any type. The number of bits must be an integer. This function returns the shifted value.

```grap
mem | save | (bin | "a" | "101")
(bits | < | (mem | get | "a"))
```

This would return 10, as 101 shifted to the left by 1 bit is 1010, which is 10 in decimal.

## `bin`
The `bin` function is used to convert a value to binary. It takes one argument: a value. This function returns the binary representation of the given value.

```grap
mem | save | (bin | "a" | "101")
```

This would save 101 to memory as a binary value.

# Example Code
+ [Basic Bits](../demos/bits.grap)