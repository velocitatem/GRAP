# String Operations Module
This module is used for string operations. It has only 1 key action for now, that being `concat`.

## `concat` + `concadd`
Another stack based function, `concat` is used to concatenate strings. It takes one argument: a string. This function returns nothing.

```grap
str | concadd | "Hello"
str | concadd | "World"
```

This would save `Hello` and `World` to the stack. Then, when `concat` is called, it would concatenate the two strings and return `HelloWorld`.

```grap
io | say | (str | concat | ())
```

This would print `HelloWorld` to the console.

You will see it often being used to generate arguments to be passed to other functions such as in [math](./math.md).

# Example Code
+ [Basic String](../demos/str.grap)
+ [Math](../demos/math.grap)
+ [Circle Area](../demos/circle.grap)

