# Memory Module

This module is used for saving and retrieving values in memory. It has two actions: `save` and `get`.

## `save`

The `save` function is used to store a value in memory. It takes two arguments: a key and a value. The key is a string that represents the name of the value to be stored. The value can be of any type. This function does not return any value.

## `get`

The `get` function is used to retrieve a value from memory. It takes one argument: a key. The key is a string that represents the name of the value to be retrieved. This function returns the value associated with the given key.

It takes as an argument the variable name `"varname"` and returns the value associated with that variable name. This return value can be used in other commands.

## Usage

The module must be used with the following syntax:

```grap
mem | save/get | variable_object
```

where:
- `variable_object` is a variable object that contains the key and value to be saved in memory.

Here's an example of how to use the `save` and `get` functions:

```grap
mem | save | (int | "num1" | "2")
mem | save | (int | "num2" | "3")
io | say | ( mem | get | "num1")
```

This program will print `2` to the console.
