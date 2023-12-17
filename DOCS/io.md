# IO Module

This module is used for input and output. It has two actions: `say` and `ask`.

## `say`

The `say` function is used to print a value to the console. It takes one argument: a value. This function does not return any value.

To make use of new lines, use `<n>` in your string. For example, `io | say | "Hello<n>World"` will print:

```
Hello
World
```

## `ask`

The `ask` function is used to get input from the user. It takes one argument: a prompt. This function returns the user's input.

## Usage

The module must be used with the following syntax:

```grap
io | say/ask | value
```

where:
- `value` is the value to be printed to the console or the prompt to be displayed to the user.

# Example Code
+ [Basic IO](../demos/helloworld.grap)
+ [Input](../demos/input.grap)