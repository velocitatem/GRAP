# Math Module

This module is used for saving and retrieving values in memory. It has all basic arithmetic actions: `add` for addition, `sub` for subtraction, `mul` for multiplication, `div` for division, `mod` for modulo (remainder), and `pow` for exponents.

These commands can be used with hardcoded numerical inputs, or can directly read from saved memory if provided with variable names.

## Usage

The module must be used with the following syntax:

```grap
math | operator | "a b"
```

where:
- `operator` is one of the arithmetical functions mentioned above (`add`, `sub`, `mul`, `div`, `mod`, `pow`)
- `a`, `b` are arguments of numerical value or variable names

For example, `math | add | "1 2"` will add together `1` and `2`.
`math | sub | "5 my_variable"` will search memory saved with the [memory](mem.md) module for a variable called `"my_variable"` and subtract its value from `5`. None, either, or both of these arguments can be passed in as variables.


These functions can all be combined together, as seen below:

```grap
mem | save | (var | "num" | (math | add | "2 3"))
io | say | ( math | mul | "10 num")
```

This program will print `50` to the console and save `5` to memory.

## Error handling
Please note, if the mathematical operation cannot be completed for whatever reason, including references to unassigned variables or incorrect syntax, the functional will terminate and return `0`.


# Example Code
+ [Basic Math](../demos/math.grap)